#ifndef FILE_STUFF
#define FILE_STUFF
#include "types.h"
#include <vector>
namespace datastream {
    
    int getLongestLength(std::vector<Todo> todos);
    std::vector<Todo> readFile(std::string& path);//reads the file and returns all Todo data
    void writeFile(std::vector<Todo> todos, std::string path);//writes data in memory to the yaml file
    void createBackup(); //creates a backup of the data when it is loaded just in case changes get corrupted

}  

#endif
