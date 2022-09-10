#ifndef FILE_STUFF
#define FILE_STUFF
#include "types.h"
#include <vector>
namespace datastream {
 
    std::vector<Todo>& readFile();//reads the file and returns all Todo data
    void writeFile();
    void createBackup();

}  

#endif
