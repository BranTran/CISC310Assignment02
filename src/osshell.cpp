#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
 
std::vector<std::string> splitString(std::string text, char d);
std::string getFullPath(std::string cmd, const std::vector<std::string>& os_path_list);
bool fileExists(std::string full_path, bool *executable);

int main (int argc, char **argv)
{
	//hello comment added
    std::string input;
    char* os_path = getenv("PATH");
    std::cout << os_path;
    std::vector<std::string> os_path_list = splitString(os_path, ':');
    std::vector<std::string>::iterator path_it = os_path_list.begin();

    for(path_it = os_path_list.begin(); path_it != os_path_list.end(); path_it++){
      std::cout << *path_it << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "Welcome to OSShell! Please enter your commands ('exit' to quit)." << std::endl;
//Load in history
    /*
      vector of history
      open file (figure out where to put file. Probably bin/)
      read file and store the LAST 128 (if applicable) into vector
      
     */

    //    bool* executable;
    //*executable = false;
    bool exit_flag = false;
    //    std::string full_path ("");
    // Repeat:
    //  Print prompt for user input: "osshell> " (no newline)
    while(!(exit_flag))
    {
      std::cout << "osshell>";

    //  Get user input for next command
      std::cin >> input;

      // If just \n next

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
      

    //  For all other commands, check if an executable by that name is in one of the PATH directories

      //For each thing in path vector
      //
      //getFullPath(cmd, path);
      //
      //QUESTION: WHat is executable???
      
      //if(fileExists(full_path, executable))
      if(1==0)
      {
	//   If yes, execute it
	// fork
	//output = execv()
	//std::cout < output <std::endl;
      }
      else
      {
	std::cout<<"<Command_name>: Error running command"<<std::endl;
	//   If no, print error statement: "<command_name>: Error running command" (do include newline)
      }
      exit_flag = true;
    }//while exit_flag
    return 0;
}

// Returns vector of strings created by splitting `text` on every occurance of `d`
std::vector<std::string> splitString(std::string text, char d)
{
//NEED TO CODE
  std::string::iterator it;
  std::string path;
  std::vector<std::string> result;
  for(it = text.begin(); it != text.end(); it++){
    if(*it == d){
      //      std::cout << "Compared it:" <<*it<<" and found match"<<std::endl;
      result.push_back(path);
      path.clear();
    }
    else{
      path.push_back(*it);
    }
  }
    return result;
}

// Returns a string for the full path of a command if it is found in PATH, otherwise simply return ""
std::string getFullPath(std::string cmd, const std::vector<std::string>& os_path_list)
{
//THING TO DO
    return "";
}

// Returns whether a file exists or not; should also set *executable to true/false 
// depending on if the user has permission to execute the file
bool fileExists(std::string full_path, bool *executable)
{
//THING TO DO
    *executable = false;
    return false;
}
