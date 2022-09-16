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
const std::string keybinds {"F1:Exit|F2:Save|F3:Exit And Save|F4:New Todo|F5:Delete Todo|Enter:Access Todo"};
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
void deleteTodo(std::vector<Todo>& todos, std::vector<item>& items);
void saveData(std::vector<Todo>& todos);
WINDOW* createWindow(int width, int length, int row, int col);
void destroyWindow(WINDOW* win);
std::string promptUser(int row, int col);
char promptUserDelete(int row, int col);
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

   
    mvprintw(row-(row-18), (col-mesgSize)/2, "%s", mesg.c_str()); 
    mvchgat(row-(row-18), (col-mesgSize)/2, mesg.size(), A_BOLD,2,NULL );

    
    mvprintw((row/2)+4, (col-headerSize)/2, "%s", header.c_str()); 
    mvchgat((row/2)+4, (col-headerSize)/2, headerSize, A_BOLD,1,NULL );

    

    mvprintw(row-3, (col-keybinds.size())/2, "%s", keybinds.c_str());
    mvchgat(row-3, (col-keybinds.size())/2, keybinds.size(), A_BOLD,2, NULL);
   
    refresh();

    /*Other windows*/
    WINDOW* win= newwin(todoSize,longestLength,(row/2)+6,(col-longestLength)/2);
    box(win,0,0);
    wrefresh(win);  
    std::vector<item> items {};
   
    if(todos.size()>0)
    {
    for(int i{0}; i<todos.size(); ++i)
    {
        item n_item {todos.at(i).getName(),i, false};
        items.push_back(n_item);
    }
    items.at(0).selected = true;//set the first entry as selected
    }
    printTodos(win,items);

    bool loop = true;

    while(loop)
    {
        std::string input{};
        switch(getch())
        {
            case KEY_F(1):
                loop = false;
                break;
            case KEY_F(2):
                datastream::writeFile(todos,path);
                break;
            case KEY_F(3):
                datastream::writeFile(todos,path);
                loop = false;
                break;
            case KEY_F(5):
                if(items.size()>0)
                {
                    char response = promptUserDelete((row/2)-2, (col/2)-10);
                    if(response == 'y')
                    deleteTodo(todos,items);
                }
                wclear(win);
                destroyWindow(win);
                win= createWindow(static_cast<int>(todos.size())+4,datastream::getLongestLength(todos)+7,row,col);
                
                break;
            case KEY_F(4):
                 input = promptUser((row/2)-2, (col/2)-10);   
                 addTodo(todos,items,input); 
                 destroyWindow(win);
                 win= createWindow(static_cast<int>(todos.size())+4,datastream::getLongestLength(todos)+7,row,col);
                 box(win,0,0);
                 break;
            case KEY_UP:
                if(items.size() > 1)
                    incrementSelection(items);
                printTodos(win,items);
                break;
            case KEY_DOWN:
                if(items.size() > 1)
                    decrementSelection(items);
                printTodos(win, items);
                break;

        }
            printTodos(win,items);
    }
    delwin(win);
    endwin();

    return 0;

}

void printTodos(WINDOW* win, std::vector<item>& items)
{
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);   

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

        text.append(i.title).append(" ");//extra space added to overwrite any extra characters, since having [*] increases the size. The space will overwite the character pushed over by [*]
        int margin {2};

        if(i.selected == true)
        {
            wattrset(win, COLOR_PAIR(4)| A_BOLD);
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
    item newItem {name,static_cast<int>(todos.size()),false};
    
    if(items.size() == 0)
        newItem.selected=true;

    todos.push_back(newTodo);
    items.push_back(newItem);
}

void deleteTodo(std::vector<Todo>& todos, std::vector<item>& items)
{

    

    int index {};
    for (item& i: items)
    {
        if (i.selected == true)
            index = i.index;
    }

    items.erase(items.begin() + index);
    todos.erase(todos.begin()+index);
    if(items.size()>0)
        items.at(0).selected = true;

}


WINDOW* createWindow(int width, int length,int row, int col)
{
    WINDOW* win = newwin(width,length,(row/2)+6,(col-length)/2);
    box(win,0,0);
    wrefresh(win);
    return win;

}

char promptUserDelete(int row, int col)
{
    WINDOW* prompt = newwin(7,50,row,col-15);
    box(prompt,0,0);
    mvwprintw(prompt,3,1,"%s", "Are you sure you want to delete this Todo(y/n)?");
    wrefresh(prompt);
    char response {};
    bool loop = true; //get input until the user enters y or n
    while(loop)
    {
        response = getch();
        if(response == 'y' || response == 'n')
            break;
    }
    wclear(prompt);
    destroyWindow(prompt);
    return response;
}

std::string promptUser(int row, int col)
{
    WINDOW* win = newwin(5,40,row,col-10);

    mvwprintw(win, 1, 1,"%s", "Enter the Todo Title:");
    box(win,0,0);
    wrefresh(win);
    std::string input{};
    bool prompt = true;    
    while(prompt)
    {
        int key = getch();
        

        switch(key)
        {
            case 10:
              prompt = false;
              break;
            case KEY_BACKSPACE:
              if(input.size() > 0)
                input.pop_back();
             break;

        default:
        input += key;
        break;
        }
                
        std::string currInput {input + "<-"};
        wclear(win);              
        mvwprintw(win, 1, 1,"%s", "Enter the Todo Title:");
        box(win,0,0);
        wrefresh(win);
        mvwprintw(win, 3, 1,"%s", currInput.c_str());
        wrefresh(win);

   

    }
    
        
    wclear(win);
    destroyWindow(win);
    return input;
}



void destroyWindow(WINDOW* win)
{
    wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);
}


