#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "../common/curse_extras.h"

int main(int argc, char *argv[])
{
    int x = 0;
    int y = 0;
    int iNewParent_y = 0;
    int iNewParent_x = 0;
    int next_x = 0;
    int next_y = 0;
    int dir_x = 1;
    int dir_y = 1;
    int iLoops = 0;
    int iSlowdownFactor = 1;
    int iInfoSize = 10;
    int iParent_x = 0;
    int iParent_y = 0;
    int iMiddle_x = 0;
    bool bFlames = false;

    bool bColor = false;
    
    timespec mytime; 
    mytime.tv_sec = 0;
    mytime.tv_nsec = 1000000; // one msec
    mytime.tv_nsec *= 250; // multiply by amount of msecs
    
    initscr(); // Initialize the window
    noecho(); // Don't echo any keypresses
    curs_set(FALSE); // Don't display the cursor
    
    if (true == has_colors())
    {
        bColor = true;
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_YELLOW);
    }

    getmaxyx(stdscr, iParent_y, iParent_x);

    WINDOW *map  = newwin(iParent_y - iInfoSize, iParent_x, 0, 0);
    WINDOW *info = newwin(iInfoSize, iParent_x, iParent_y - iInfoSize, 0);

    wattron(info, COLOR_PAIR(2));
    
    wattron(map, COLOR_PAIR(2));
    draw_borders(map);
    draw_borders(info);

    iMiddle_x = iParent_x/2 - 14; 

    if (1 >  iMiddle_x)
    {
        iMiddle_x = 1;
    }

    mvwprintw(info, 2, iMiddle_x, "...into the Midnightbox!");
        
    wrefresh(map);
    wrefresh(info);

    while (1)
    {
        // Global var `stdscr` is created by the call to `initscr()`
        getmaxyx(stdscr, iNewParent_y, iNewParent_x);
            
        if ((iNewParent_y != iParent_y) || (iNewParent_x != iParent_x))
        {
            iParent_x = iNewParent_x;
            iParent_y = iNewParent_y;

            wresize(map, iParent_y - iInfoSize, iParent_x);
            wresize(info, iInfoSize, iParent_x);

            mvwin(info, iParent_y - iInfoSize, 0);

            wclear(stdscr);
            wclear(map);
            wclear(info);

            draw_borders(map);
            draw_borders(info);
                
                       
            iMiddle_x = iParent_x/2 - 14; 

            if (1 >  iMiddle_x)
            {
                iMiddle_x = 1;
            }

            mvwprintw(info, 2, iMiddle_x, "Welcome into the Midnightbox!");
            // Handle situations where object goes out of window
            if (x > iParent_x - 1 - 10)
            {
                x = iParent_x - 1 - 10;
            }
            
            if (y > iParent_y - 1 - 6)
            {
                y = iParent_y - iInfoSize - 1 - 12;
            }

            wrefresh(info);
            wrefresh(map);
            
            if ((10 >  iNewParent_x) || (10 > iNewParent_y)) 
            {
                y = 1;
                x = 1;
                continue;
            }
        }

        wclear(map);
;
        draw_borders(map);

        wattron(map, COLOR_PAIR(1));

        if (10 < iLoops%100)
        {
            mvwprintw(map, y,x,  " .''''. ");
            mvwprintw(map, y+1,x,"( Q  O )");
            mvwprintw(map, y+2,x," ' '' ' ");
            mvwprintw(map, y+3,x,"  ||||  ");
            mvwprintw(map, y+4,x,"  '..'  ");
            mvwprintw(map, y+5,x,"Welcome!");
        }
        else
        {
            mvwprintw(map, y,x,  " .''''. ");
            mvwprintw(map, y+1,x,"( _  O )");
            mvwprintw(map, y+2,x," ' '' ' ");
            mvwprintw(map, y+3,x,"  ||||  ");
            mvwprintw(map, y+4,x,"  '..'  ");
            mvwprintw(map, y+5,x,"Welcome!");
        }

        wattroff(map, COLOR_PAIR(1));
        wattron(map, COLOR_PAIR(2));
        wrefresh(map);
    
        nanosleep(&mytime, NULL);
        iLoops++;

        if (0 == iLoops%iSlowdownFactor)
        {
            next_x = x + dir_x;
            next_y = y + dir_y;
        
            if (next_x >= iParent_x - 10 || next_x < 1) 
            {
                dir_x*= -1;
                x += dir_x;
                bFlames = true;
            } 
            else 
            {
                x += dir_x;
                bFlames = false;
            }
            
            if (next_y >= (iParent_y-iInfoSize-6) || next_y < 1) 
            {
                dir_y *= -1;
                y += dir_y;
                bFlames = true;
            } 
            else 
            {
                y += dir_y;
                bFlames = false;
            }
        }
        
        if ((1 == iLoops%10) || (0 ==iLoops))
        {
            int iMaxHeight = 6;

            if (true == bFlames)
            {
                iMaxHeight = iInfoSize-1;       
            }
            // Clear previous flames
            wclear(info);
            draw_borders(info);
                           
            iMiddle_x = iParent_x/2 - 14; 

            if (1 >  iMiddle_x)
            {
                iMiddle_x = 1;
            }

            mvwprintw(info, 2, iMiddle_x, "...into the Midnightbox!");
            
            wattron(info, COLOR_PAIR(3));
            for (int i=1; i<iParent_x-1; i++)
            {
                for (int j=iInfoSize-2; j>iInfoSize-2-rand()%iMaxHeight; j--)
                {
                        mvwprintw(info, j, i, "#");
                }
            }
                
            wrefresh(info);
            wattroff(info, COLOR_PAIR(3));
            wattron(info, COLOR_PAIR(2));
        }
    }

    wattroff(info, COLOR_PAIR(2));
    delwin(map);
    delwin(info);

    endwin(); // Restore normal terminal behavior
}
