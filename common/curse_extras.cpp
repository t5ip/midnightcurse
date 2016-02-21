#include "curse_extras.h"

void draw_borders(WINDOW *screen)
{
    int x = 0;
    int y = 0;
    int i = 0;

    getmaxyx(screen, y, x);

    // 4 corners 
    mvwprintw(screen, 0, 0, "+");
    mvwprintw(screen, y - 1, 0, "+");
    mvwprintw(screen, 0, x - 1, "+");
    mvwprintw(screen, y - 1, x - 1, "+");

    // sides
    for (i = 1; i < (y-1); i++)
    {
        mvwprintw(screen, i, 0, "|");
        mvwprintw(screen, i, x - 1, "|");
    }
    // top & bottom
    for (i = 1; i < (x-1); i++)
    {
        mvwprintw(screen, 0, i, "-");
        mvwprintw(screen, y - 1 , i, "-");
    }
}
