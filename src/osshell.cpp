#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
 
std::vector<std::string> splitString(std::string text, char d);
std::string getFullPath(std::string cmd, const std::vector<std::string>& os_path_list);
bool fileExists(std::string full_path, bool *executable);

int main (int argc, char **argv)
{
    std::string input;
    char* os_path = getenv("PATH");
    std::vector<std::string> os_path_list = splitString(os_path, ':');

    std::cout << "Welcome to OSShell! Please enter your commands ('exit' to quit)." << std::endl;
//Load in history



    // Repeat:
    //  Print prompt for user input: "osshell> " (no newline)
y

    //  Get user input for next command


    //  If command is `exit` exit loop / quit program


    //  If command is `history` print previous N commands

//Additional options

    //  For all other commands, check if an executable by that name is in one of the PATH directories

//getFullPath();
//fileExists();

    //   If yes, execute it


    //   If no, print error statement: "<command_name>: Error running command" (do include newline)

    return 0;
}

// Returns vector of strings created by splitting `text` on every occurance of `d`
std::vector<std::string> splitString(std::string text, char d)
{
//NEED TO CODE
    std::vector<std::string> result;

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
