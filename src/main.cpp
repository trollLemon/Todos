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
    Todo test = Todo("A Todo");
    Task t = Task("Sus", "    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");

    test.addTask(t);
    test.addTask(t);

    todos.push_back(test);
    todos.push_back(test);
    datastream::writeFile(todos, path); 

    return 0;
}


