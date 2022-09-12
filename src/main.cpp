#include "ncurses.h"
#include "yaml-cpp/yaml.h"
#include "types.h"
#include "file.h"
int main()
{	
	//initscr();			/* Start curses mode 		  */
	//printw("Hello World !!!");	/* Print Hello World		  */
//	refresh();			/* Print it on to the real screen */
//	getch();			/* Wait for user input */
//	endwin();			/* End curses mode		  */
   
    std::vector<Todo> todos;
    std::string path {"/home/haydn/Github/TodoList/test/test.yaml"};
    Todo test = Todo("A");
    Todo test2 = Todo("Todo");
    Todo test3 = Todo("test");
    
    Task t = Task("test", "Test code for bugs");
    Task y = Task("r", "There are bugs in the code");

    test.addTask(t);
    test2.addTask(t);
    test2.addTask(y);
    test3.addTask(t);

    todos.push_back(test);
    todos.push_back(test2);
    todos.push_back(test3);
    todos.push_back(test);
    datastream::writeFile(todos, path); 
    datastream::readFile(path);
    return 0;
}


