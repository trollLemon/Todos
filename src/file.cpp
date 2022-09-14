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
    
    //helper to return an enum based on a string

    todoStatus stringToEnum(std::string string)
    {
        if(string == "Not Started")
            return todoStatus::notStarted;
        else if (string== "In Progress")
            return todoStatus::inProgress;
        else
            return todoStatus::done;
    }




namespace datastream {



int getLongestLength(std::vector<Todo> todos){

    int len {0};

    for (Todo& todo: todos)
    {
        if(todo.length() > len)
            len = todo.length();
    }

    return len;

}


    std::vector<Todo> readFile(std::string& path)
    {
        YAML::Node file = YAML::LoadFile(path);
        std::vector<Todo> data{};
        
        for(int i{0}; i< file.size(); ++i)
        {
            std::string todoTitle = file[i][i].as<std::string>();
            todoStatus enumStatus = stringToEnum(file[i]["status"].as<std::string>());           
            Todo newTodo = Todo(todoTitle,enumStatus);
            
            for(int j{0}; j < file[i]["data"].size(); ++j)
            {
                std::string title = file[i]["data"][j]["name"].as<std::string>();
                std::string content = file[i]["data"][j]["content"].as<std::string>();  
                std::string done = file[i]["data"][j]["isDone"].as<std::string>(); 

                bool isDone;

                if(done== "true")
                    isDone=true;
                else
                    isDone=false;

                Task newTask = Task(title,content,isDone);
                newTodo.addTask(newTask);


            }

            data.push_back(newTodo);
        }
        
        return data;
    }
    void writeFile(std::vector<Todo> todos, std::string path)
    {
        YAML::Emitter output; //this will output our data into our data file
        
        output << YAML::BeginSeq;

        
        int counter{0} ;
        for(Todo& t : todos )
        {
             output << YAML::BeginMap;
             output << YAML::Key << counter;
             output << YAML::Value << t.getName();
             output << YAML::Key << "status";
             output << YAML::Value << status(t.getStatus());
             output << YAML::Key << "data";
             output << YAML::Value;
             output << YAML::BeginSeq;
             
            for (Task& tsk : t.getTasks())
            {
                output << YAML::BeginMap;
                output << YAML::Key   << "name";
                output << YAML::Value << tsk.getName();
                output << YAML::Key   << "content";
                output << YAML::Value << tsk.getContent();
                output << YAML::Key   << "isDone" << YAML::Value << tsk.getStatus();
                output << YAML::EndMap;
            }
            output << YAML::EndSeq;
            output << YAML::EndMap;
            ++counter;
        }
        output << YAML::EndSeq;

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
