#include <string.h> //strcpy

#include <unistd.h> //Execv
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include <sys/stat.h> //file exists
#include <sys/types.h> //pid
#include <sys/wait.h> //wait()

#include <fstream> //read&write to files

using namespace std;
#define CommandLength  128
#define HISTORY_COUNT 128

std::vector<std::string> splitString(std::string text, char d);
std::string getFullPath(std::string cmd, const std::vector<std::string>& os_path_list);
bool fileExists(std::string full_path, bool *executable);
char* const* convert(const std::vector< std::string > &v);
std::vector<std::string> parsecmd(std::string cmd);

//std::vector<std::string> clear_history(std::vector<std::string> removeHistory)
std::vector<std::string> history(string hist[HISTORY_COUNT], int current, string input);

int main (int argc, char **argv)
{
  //hello comment added
  bool exit_flag = false;
  char* os_path = getenv("PATH");
  std::string cmd;
  std::string input;
  std::string full_path;
  std::vector<std::string> os_path_list = splitString(os_path, ':');//split path
  std::vector<std::string> arguments;

  //--Displays pared PATH list
  //std::vector<std::string>::iterator path_it = os_path_list.begin();
  //    for(path_it = os_path_list.begin(); path_it != os_path_list.end(); path_it++){
  //  std::cout << *path_it << std::endl;
  //}
  //std::cout << std::endl;

  std::cout << "Welcome to OSShell! Please enter your commands ('exit' to quit)." << std::endl;
  
  //Load in history
  string hist[HISTORY_COUNT];
  int i = 0;
  int current = 0;
  for (i = 0; i < HISTORY_COUNT; i++)
    {
        hist[i] = "";
    }//create empty array to hold history commands
    
  /*
    vector of history
    open file (figure out where to put file. Probably bin/)
    read file and store the LAST 128 (if applicable) into vector
  */

  while(!(exit_flag))
    {
      std::cout << "osshell> ";
      //  Get user input for next command
      std::getline(std::cin,input);

    hist[current] = input;
    current = (current + 1) % HISTORY_COUNT;

      if(!input.empty()){
      // std::cout <<"Input: " << input<<std::endl;
      arguments = parsecmd(input);
      cmd = arguments.front();


      //--Displays pared command arguments list
      std::vector<std::string>::iterator arg_it = arguments.begin();
      for(arg_it = arguments.begin(); arg_it != arguments.end(); arg_it++){
	//	std::cout << *arg_it << std::endl;
      }
	  
	if(cmd.compare("exit") == 0)
	{
	    std::vector<string> finalList;
	    finalList = history(hist, current, "end"); 
	  
	    ofstream myfile ("history.txt");
        if (myfile.is_open())
        {
            for(int j = 0; j < finalList.size(); j++)
            {
                myfile << finalList.at(j) << "\n";
            }
            myfile.close();
        }
	  
	  exit_flag = true;
	}
	  
	// If just \n next
	  
	  
	else if(cmd.compare("history") == 0)
	{
	  //std::cout <<"Got a call for history. Need to implement it though" <<std::endl;
	  //  else If command is `exit` exit loop / quit program
	   history(hist, current, input);
	  /*
	    Add exit to history
	    exit_flag = true;
	  */
	    
	  //  If command is `history` print previous N commands
	    
	  /*
	    Check if additional arguments apply
	    then play with history vector
	    add history into history
	  */
	}
	else{
	  //  For all other commands, check if an executable by that name is in one of the PATH directories

	  full_path = getFullPath(cmd, os_path_list);

	  if(!full_path.empty())
	    {
	      pid_t child_pid;
	      child_pid = fork();

	      if(child_pid == 0) {
		/* CHILD PROCESS */
		/*------TEST-----------
		char* const args[] = {"wc","-l","src/osshell.cpp"};
		execv("/usr/bin/wc",args);
		//*/
		//char* const* reading = convert(arguments);
		execv(full_path.c_str(),convert(arguments));
		/* If execv returns, it must have failed. */

		printf("Error when executing %s: %s\n",full_path.c_str(),strerror(errno));
		exit(3);
	      }
	      else
		{
		  /* PARENT PROCESS */
		  wait(NULL);
		}

	    }
	  else
	    {
	      std::cout<<"<"<< cmd <<">: Error running command"<<std::endl;
	    }
	}//else not exit or history
      }//if input not empty
    }//while exit_flag
  return 0;
}

// Returns vector of strings created by splitting `text` on every occurance of `d`
std::vector<std::string> splitString(std::string text, char d)
{ //FINISHED
  std::string path;
  std::string::iterator it;
  std::vector<std::string> result;

  for(it = text.begin(); it != text.end(); it++){
    if(*it == d){
      result.push_back(path);
      path.clear();
    }
    else{
      path.push_back(*it);
    }
  }
  //One last time
  result.push_back(path);
  return result;
}

// Returns a string for the full path of a command if it is found in PATH, otherwise simply return ""
std::string getFullPath(std::string cmd, const std::vector<std::string>& os_path_list)
{
  //FINISHED
  bool found = false;
  bool relative = false;
  bool executable = false;
  std::string path;
  std::vector<std::string>::const_iterator path_it = os_path_list.begin();
  for(path_it = os_path_list.begin(); path_it != os_path_list.end() && !found; path_it++)
    {
      path = *path_it + '/' + cmd;
      //    std::cout << path << std::endl;
      found = fileExists(path,&executable);
      if(found && executable)
        {
	  std::cout <<"Getting path: "<< path << std::endl;
	  return path;
        }
    }
  relative = fileExists(cmd,&executable);
  if(relative && executable)
    {
      std::cout <<"Checking relative: "<< cmd << std::endl;
      return cmd;
    }
  
  return "";

}

// Returns whether a file exists or not; should also set *executable to true/false 
// depending on if the user has permission to execute the file
bool fileExists(std::string full_path, bool *executable)
{//FINISHED
  //Solution found using stack overflow
  struct stat st;
  if(stat(full_path.c_str(), &st) < 0)
    {
      *executable = false;
      return false;

    }
  if((st.st_mode & S_IEXEC) != 0)
    {
      *executable = true;
      return true;
    }
  *executable = false;
  return false;

}


char* const* convert(const std::vector< std::string > &v)
{
  char** cc = new char*[v.size()+1]; //if you make the pointers const here allready, you won't be able to fill them

  for(unsigned int i = 0; i < v.size(); ++i)
    {
      cc[i] = new char[v[ i ].size()+1]; //make it fit
      strcpy(cc[i], v[ i ].c_str());     //copy string
      //      printf("%s, ",cc[i]);
    }
  cc[v.size()] = NULL;
  //  printf("\n");

  return cc; //pointers to the strings will be const to whoever receives this data.
}


// Returns vector of strings created by splitting `cmd"
std::vector<std::string> parsecmd(std::string cmd)
{

  std::string path;
  std::string::iterator it;
  std::vector<std::string> result;
  bool inquote = false;

  for(it = cmd.begin(); it != cmd.end(); it++){
    if(*it == '"' && !(inquote)){
      //Begin quote space
      inquote = true;
    }
    else if(*it == '"'){
      //Ending quote
      inquote = false;
    }
    else if(*it == ' ' && !(inquote)){
      //parse
      if(path.size() > 0){
	//Add if there is something ot add
	result.push_back(path);
	path.clear();
      }
    }
    else{
      path.push_back(*it);
    }
  }
  
  //One last time
  if(path.size() > 0){
    result.push_back(path);
  }
  if(result.size() == 0){
    result.push_back("");
  }
  return result;
}

  
std::vector<std::string> history(string hist[HISTORY_COUNT], int current, string input)
{
    int i = 0; 
    int hist_num = 0; 
    int numberOfLines = 0;
    std::vector<string> oldHistory;

    //get all elements from the shell if it was already run once
    ifstream file("history.txt");
    if(file.is_open())
    {
        string line;
        while(!file.eof())
        {
            getline(file,line);
            oldHistory.push_back(line);
            //cout<< line << endl;
            numberOfLines++;
            //cout << numberOfLines << " " << oldHistory.at(numberOfLines-1) << "\n";
        }
    }
    file.close();
    
    int overCount = 0;
    if((current + oldHistory.size()) > 128)
    {
        //cout << "overload! \n";
        overCount = ((current + oldHistory.size())-128); 
        //cout << overCount << "elements over, going to erase \n";
        oldHistory.erase(oldHistory.begin(), oldHistory.begin() + overCount); 
    }
   
   if(input != "end")
   {
    for(int j = 0; j < oldHistory.size(); j++)
    {
        cout << j+1 << " " << oldHistory.at(j) << "\n";
    }
   }
    
    hist_num = oldHistory.size();
    if(hist_num == 0)
    {
        hist_num = 1;
    }
    else
    {
        hist_num++;
    }
    
    while(i<current-1)
    {
        oldHistory.push_back(hist[i]);
        if(input == "end")
        {
            //do not print history
            i++;
        }
        else
        {
            oldHistory.push_back(hist[i]);
            cout << i+hist_num << " " << hist[i] << "\n"; 
            i++;
        }
    } 
    
    if(input == "end")
    {
        oldHistory.push_back("exit");
    }
    
    return oldHistory; 
}

/*std::vector<std::string> clear_history(std::vector<std::string> removeHistory)
{
    removeHistory.clear();
    /*
    int i;
    for (i = 0; i < HISTORY_COUNT; i++) 
    {
        free(hist[i]);
        hist[i] = NULL;
    }
    return removeHistory;
}*/

