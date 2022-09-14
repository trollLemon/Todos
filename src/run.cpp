#include "run.h"
#include "ncurses.h"
#include "types.h"
#include "file.h"
#include "locale.h"
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <bits/stdc++.h>




/*Const variables-------------------------------------------------------------*/



//logo
const std::string logo1{"      #       # #######                             "};
const std::string logo2{"     #       #     #     ####  #####   ####   ####  "};
const std::string logo3{"    #       #      #    #    # #    # #    # #      "};
const std::string logo4{"   #       #       #    #    # #    # #    #  ####  "};
const std::string logo5{"  #       #        #    #    # #    # #    #      # "};
const std::string logo6{" #       #         #    #    # #    # #    # #    # "};
const std::string logo7{"#       #          #     ####  #####   ####   #### "};


std::string path {"/home/haydn/Github/TodoList/test/test.yaml"};
const std::string mesg {" ~ A todo list from inside your Terminal ~"};
const std::string header {"Todos:"};
const std::string keybinds {"F1:Exit|F2:Save|F3:Exit And Save|F4:Access Todos"};
int logoSize {static_cast<int>(logo1.size())};
int mesgSize {static_cast<int>(mesg.size())};
int headerSize{static_cast<int>(header.size())};


/*declarations--------------------------------------------------------------------------*/
void printTodos(WINDOW* , std::vector<Todo>& todos);//prints todo titles in our little box below the "Todos:" header


void run()
{

    
    std::vector<Todo> todos {datastream::readFile(path)};
    


    /*runtime vars*/
    int longestLength {datastream::getLongestLength(todos)+7};//the width for our todo box under the todos header,we add 7 so the text has some space from the borders
    int todoSize {static_cast<int>(todos.size())+4};          //the height for the todo box
                                                              

    /*Init main window*/
    setlocale(LC_ALL, "");  //set locale so we can print special chars 

    initscr();
    start_color();
    noecho();
    cbreak();
    keypad(stdscr,true);
    curs_set(0);
    
    //set up some colors
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    
    
    box(stdscr,0,0); 

    int row {};
    int col {};

    getmaxyx(stdscr,row,col);	

    /*Printing Main Text*/

    mvprintw((row-(row-3)),(col-logoSize)/2, "%s", logo1.c_str());
    mvprintw((row-(row-4)),(col-logoSize)/2, "%s", logo2.c_str());
    mvprintw((row-(row-5)),(col-logoSize)/2, "%s", logo3.c_str());
    mvprintw((row-(row-6)),(col-logoSize)/2, "%s", logo4.c_str());
    mvprintw((row-(row-7)),(col-logoSize)/2, "%s", logo5.c_str());
    mvprintw((row-(row-8)),(col-logoSize)/2, "%s", logo6.c_str());
    mvprintw((row-(row-9)),(col-logoSize)/2, "%s", logo7.c_str());
    
    //color the ascii text
    for(int i{3}; i<10; ++i)
    {
        mvchgat((row-(row-i)), (col-logoSize)/2, logoSize, A_BOLD, 3, NULL);
    }

    mvprintw(row/2,(col-mesgSize)/2,"%s",mesg.c_str());
    mvchgat(row/2, (col-mesgSize)/2, mesgSize, A_BLINK, 1, NULL);	
    mvprintw((row/2)+4, (col-headerSize)/2, "%s", header.c_str());
    mvchgat((row/2)+4,(col-headerSize)/2, headerSize, A_BLINK,2,NULL);
    
    mvprintw(row-3, (col-keybinds.size())/2, "%s", keybinds.c_str());
    mvchgat(row-3, (col-keybinds.size())/2, keybinds.size(), A_BOLD,2, NULL);
    refresh();
   
    /*Other windows*/
    WINDOW *win = newwin(todoSize,longestLength,(row/2)+6,(col-longestLength)/2);
    box(win,0,0);

    printTodos(win,todos);


    //TODO: wait for user input, if F4 is pressed, pass input into the second window so the user can select a Todo

    
    getch();
    endwin();


}

void printTodos(WINDOW* win, std::vector<Todo>& todos)
{
    
    int counter {2};//start at the second line in the window
    for(Todo& todo: todos)
    {
        std::string text {"[]"};
        text.append(todo.getName());
        mvwprintw(win, counter, 2,"%s", text.c_str());//TODO:get rid of magic number
        ++counter;    
    }


    wrefresh(win);

}


