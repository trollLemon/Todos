#ifndef DATATYPES
#define DATATYPES
#include <string>
#include <vector>



enum todoStatus
{
    notStarted,
    inProgress,
    done,
};


/*Class for a Task
 * A task can be things you need to do for software development, 
 * like: refactor code, or something you need to do for the Day like
 * go to the store
 *
 * It contains two strings and a bool:
 * -A string for the name of the task
 * -A string for the description
 * - The bool to say if its been finished or not
 */
 class Task
{
    private:
        std::string content;
        std::string name;
        bool isDone;
    public:
        Task(std::string& title, std::string& input)
        {
            this->name = title;
            this->content = input;
            this-> isDone = false;
        };

        bool getStatus()
        {
            return this->isDone;
        };

        std::string getContent()
        {
            return this->content;
        };

        void setContent(std::string& newStuff)
        {
            this-> content = newStuff;
        };
        
        void setName(std::string& newName)
        {
            this->name = newName;
        };
};

/*
 * The Todo class represents the main goal of what someone wants to do.
 *
 * Example, TODO: make a GUI app.
 *
 * And the things the person needs to do in order to create that GUI app will be tasks.
 *
 * So the data will look like this:
 *
 *  todo GUI project
 *     tasks:
 *     get libraries
 *     code
 *     test
 *     deploy
 *
 * This means the todo class will have a std::string for a name, and a vector of tasks.
 * We also want an Enum to see if we are done, in progress of finishing, or havent started the todo
 */
class Todo{

    private:
    std::string name;
    std::vector<Task> tasks;
    todoStatus status; 
    public:
    
    Todo(std::string title)
    {
        this->name = title;
        this-> status = todoStatus::notStarted;
    };

    void inProgress()
    {
        this->status = todoStatus::inProgress;
    };

    void done()
    {
        this->status = todoStatus::done;
    };

    std::string& getName()
    {
        return this->name;
    };

    todoStatus getStatus()
    {
        return this->status;
    };

    std::vector<Task>& getTasks()
    {
        return this->tasks;
    };
};



#endif
