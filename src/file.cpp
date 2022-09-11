#include "file.h"
#include "types.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>

  //helper function to return strings based on the status Enum in types.h
    std::string status( todoStatus stat)
    {

        switch (stat)
        {
            case todoStatus::notStarted:
                return "Not Started";
            case todoStatus::inProgress:
                return "In Progress";
            case todoStatus::done:
                return "Done";
            default:
                return "Err";
        }

    }





namespace datastream {

    std::vector<Todo> readFile(std::string& path)
    {
        std::ifstream file(path);
        YAML::Parser parser(file);

        std::vector<Todo> data{};
        return data;
    }
    void writeFile(std::vector<Todo> todos, std::string path)
    {
        YAML::Emitter output; //this will output our data into our data file
        
        for (Todo& todo: todos)
        {
            output << YAML::BeginMap;

            output << YAML::Key   << "Title";
            output << YAML::Value << todo.getName();
            output << YAML::Key   << "Status";
            output << YAML::Value << status(todo.getStatus());
            
            int counter {0};
            //now loop through all our tasks
            for (Task& task : todo.getTasks())
            {
                 std::string header {"Task "};
                 header += std::to_string(counter);
                 output << YAML::Key   << header ;
                 output << YAML::Value 
                        << YAML::BeginSeq
                        << task.getName()
                        << task.getContent()
                        << task.getStatus()
                        << YAML::EndSeq;

                 ++counter;
                                    
            }
            output << YAML::EndMap; 
        }

        //overwrite old data in the data.yaml file with the new data
        std::ofstream file;
        file.open(path, std::ofstream::out);
        file << output.c_str();
        file.close();
    }
    void createBackup()
    {

    }
}
