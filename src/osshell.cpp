#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/stat.h>


std::vector<std::string> splitString(std::string text, char d);
std::string getFullPath(std::string cmd, const std::vector<std::string>& os_path_list);
bool fileExists(std::string full_path, bool *executable);

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
    /*
      vector of history
      open file (figure out where to put file. Probably bin/)
      read file and store the LAST 128 (if applicable) into vector
      
     */

    //    bool* executable;
    //*executable = false;
    //    std::string full_path ("");
    // Repeat:
    //  Print prompt for user input: "osshell> " (no newline)
    while(!(exit_flag))
    {
      std::cout << "osshell> ";
    //  Get user input for next command
      std::getline(std::cin,input);
      //      std::cout <<"Input: " << input<<std::endl;
      arguments = splitString(input, ' ');
      cmd = arguments.front();
      
      //NEED TO PROCESS commandline to command and argument
      if(cmd.compare("exit") == 0){
	exit_flag = true;
      }

      // If just \n next


      else if(cmd.compare("history") == 0){
	std::cout <<"Got a call for history. Need to implement it though" <<std::endl;
      //  else If command is `exit` exit loop / quit program
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
      
      //For each thing in path vector
      //
	full_path = getFullPath(cmd, os_path_list);
	//
	//QUESTION: WHat is executable???
	
	//if(fileExists(full_path, executable))
	if(!full_path.empty())
	  {
	    std::cout<<"We should execute "<<full_path<<std::endl;
	    //   If yes, execute it
	    // fork
	    //output = execv()
	    //Execute program (path,cmd,additionalarguments)
	    //std::cout < output <std::endl;
	  }
	else
	  {
	    std::cout<<"<"<< cmd <<">: Error running command"<<std::endl;
	    //   If no, print error statement: "<command_name>: Error running command" (do include newline)
	  }
      }//else not exit or history
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
  bool executable = false;
  std::string path;
  std::vector<std::string>::const_iterator path_it = os_path_list.begin();
  for(path_it = os_path_list.begin(); path_it != os_path_list.end() && !found; path_it++){
    path = *path_it + '/' + cmd;
    //    std::cout << path << std::endl;
    found = fileExists(path,&executable);
    if(found && executable){
      std::cout << path << std::endl;
      return path;
    }
  }
  return "";

}

// Returns whether a file exists or not; should also set *executable to true/false 
// depending on if the user has permission to execute the file
bool fileExists(std::string full_path, bool *executable)
{//FINISHED
  //Solution found using stack overflow
  struct stat st;
  if(stat(full_path.c_str(), &st) < 0){
    *executable = false;
    return false;

  }
  if((st.st_mode & S_IEXEC) != 0){
    *executable = true;
    return true;
  }
  *executable = false;
  return false;

}
