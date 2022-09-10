#include "ncurses.h"
#include "yaml-cpp/yaml.h"
int main()
{	
	//initscr();			/* Start curses mode 		  */
	//printw("Hello World !!!");	/* Print Hello World		  */
//	refresh();			/* Print it on to the real screen */
//	getch();			/* Wait for user input */
//	endwin();			/* End curses mode		  */

YAML::Node config = YAML::LoadFile("/home/haydn/Github/TodoList/test/test.yaml");
    return 0;
}


