
#include "taskwindow.h"

    
struct item {
    std::string title;
    std::string content;
    bool done;
    bool selected;
    };

WINDOW* drawTaskDesc(int row, int col);
void printTasks(WINDOW* win, std::vector<item>& items);
void printTaskContent(WINDOW* win, std::vector<item>& items);
void clearEverything(WINDOW* p, WINDOW* q);


void addTask(std::vector<Task>& tasks, std::vector<item>& items, std::string name, std::string content);

void launchTaskEditor(Todo& todo, int row, int col)
{
  WINDOW* tasks=newwin(row,col/2,0,0);
  box(tasks,0,0);
  wrefresh(tasks);
  
  WINDOW* content=newwin(row,col/2,0,col/2);
  box(content,0,0);
  wrefresh(content);



  std::vector<item> items;

  int counter {0};

  for(Task t : todo.getTasks())
  {
    item newItem {t.getName(),t.getContent(),t.getStatus(),false};
    items.push_back(newItem);
    ++counter;
  }
  
  if(items.size() != 0)
    items.at(0).selected = true;//select the first item in the list, so the first item is highlighted once the ui is drawn

  //print content of the first item in both windows


  printTasks(tasks, items);
  bool loop = true;

  while(loop)
  {
  
    int key = getch();

    switch(key){
    
      //editing task data will save when ever the user exits
      case KEY_F(1):
        loop = false;
        break;
      
      case KEY_F(2):
        addTask(todo.getTasks(),items,"TEST", "YDIUYTWIUWEYRIUTYEWIUTYEIUWYTIUWEYTIUEWYTIUWEYTIU");
        //add task
        break;
      case KEY_F(3):
        //delete task
        //also prompt user before this is done
        break;
      case KEY_UP:
        break;
      case KEY_DOWN:
        break;
      case '\n':
        //edit task
        //prompt user if they want to change the name or the content of the task
        break;

    }
      
        clearEverything(tasks,content);
        if(items.size()!=0){
          printTasks(tasks,items);
          //printTaskContent(content,items);

        }

    

  }



  clearEverything(tasks,content);

  delwin(tasks);
  delwin(content);

}


void clearEverything(WINDOW* p, WINDOW* q)
{

  wborder(p, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wrefresh(p);
  wborder(q, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wrefresh(q);


}

void printTasks(WINDOW* win, std::vector<item>& items)
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

//TODO:replace this and the addTodo with a template
void addTask(std::vector<Task>& tasks, std::vector<item>& items, std::string name, std::string content  )
{
    Task newTask {Task(name,content)};
    item newItem {name,content,false,false};
    
    if(items.size() == 0)
        newItem.selected=true;

    tasks.push_back(newTask);
    items.push_back(newItem);
}


