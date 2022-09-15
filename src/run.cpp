#include "run.h"
#include "ncurses.h"
#include "types.h"
#include "file.h"
#include "locale.h"
#include <iostream>
#include <string>




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
const std::string keybinds {"F1:Exit|F2:Save|F3:Exit And Save|F4:New Todo|Enter:Access Todos"};
int logoSize {static_cast<int>(logo1.size())};
int mesgSize {static_cast<int>(mesg.size())};
int headerSize{static_cast<int>(header.size())};


/*Structs----------------------------------------------------------------------*/
    
struct item {
    std::string title;
    int index;
    bool selected;
    };

/*declarations--------------------------------------------------------------------------*/
void printTodos(WINDOW* , std::vector<item>& items);//prints todo titles in our little box below the "Todos:" header
void decrementSelection(std::vector<item>& items);
void incrementSelection(std::vector<item>& items);
void addTodo(std::vector<Todo>& todos, std::vector<item>& items, std::string name);
void saveData(std::vector<Todo>& todos);
int run()
{

    
    std::vector<Todo> todos {datastream::readFile(path)};
    


    /*runtime vars*/
    int longestLength {datastream::getLongestLength(todos)+7};//the width for our todo box under the todos header,we add 7 so the text has some space from the borders
    int todoSize {static_cast<int>(todos.size())+4};          //the height for the todo box
    
    //color pairs
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    
    

    /*Init main window*/
    setlocale(LC_ALL, "");  //set locale so we can print special chars 

    initscr();
    start_color();
    noecho();
    cbreak();
    keypad(stdscr,true);
    curs_set(0);
    
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


    
 
    std::vector<item> items {};
    
    for(int i{0}; i<todos.size(); ++i)
    {
        item n_item {todos.at(i).getName(),i, false};
        items.push_back(n_item);
    }
    items.at(0).selected = true;//set the first entry as selected


    
    //program loop
    
    bool cont = true;
    while(cont)
    {
        
    printTodos(win,items);

        switch(getch())
        {
         case KEY_F(1):
             cont=false;
             break;
         case KEY_F(4):
                
            addTodo(todos,items,"test");
             break;
         case KEY_UP:
             incrementSelection(items);
             printTodos(win,items);
             break;
          case KEY_DOWN:
             decrementSelection(items);
             printTodos(win,items);
             break;     

        }//TODO:implement this
    }

    delwin(win); 
    endwin();

    return 0;


}

void printTodos(WINDOW* win, std::vector<item>& items)
{
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);   

    int counter {2};//start at the second line in the window
    for(item& i: items)
    {

        std::string text {};

        if(i.selected == true){
            text= "[*]";
        }
        else{
            text="[]";
        }

        text.append(i.title).append(" ");
        int margin {2};

        if(i.selected == true)
        {
            wattrset(win, COLOR_PAIR(1)| A_BOLD);
        }
        

        mvwprintw(win, counter, margin,"%s", text.c_str());
        wattroff(win,COLOR_PAIR(1));
        wattroff(win,A_BOLD);
        ++counter;    
    }


    wrefresh(win);

}

void incrementSelection(std::vector<item>& items)
{
    if(items.front().selected == true)
    {
        items.back().selected = true;
        items.front().selected = false;
    }
    else
    {
        //find the index of the item that is currently selected, then set the next item as selected
        int index {};
        for(int i{0}; i<items.size(); ++i)
        {
            if(items.at(i).selected ==true)
            {
                index = i;
                break;
            }

        }
        items.at(index).selected =false;
        items.at(index-1).selected = true;
    }
}

void decrementSelection(std::vector<item>& items)
{
    if(items.back().selected == true)
    {
        items.back().selected = false;
        items.front().selected = true;
    }
    else
    {
        //find the index of the item that is currently selected, then set the next item as selected
        int index {};
        for(int i{0}; i<items.size(); ++i)
        {
            if(items.at(i).selected ==true)
            {
                index = i;
                break;
            }

        }
        items.at(index).selected =false;
        items.at(index+1).selected = true;
    }
}


void addTodo(std::vector<Todo>& todos, std::vector<item>& items, std::string name )
{
    Todo newTodo {Todo(name)};
    item newItem {{name,todos.size(),false}};
    todos.push_back(newTodo);
    items.push_back(newItem);
}



