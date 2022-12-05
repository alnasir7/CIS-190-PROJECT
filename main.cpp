#include "character.hpp"
#include "obstacle.hpp"
#include <ncurses.h>
#include <memory>

void debug(const char *str, ...) {
  // #ifndef _DEBUG
  static int ticks = 0;
  va_list args;
  va_start(args, str);
  mvprintw(3, 3, "%d ", ticks);
  vw_printw(stdscr, str, args);
  va_end(args);
  // #endif
}

void clear_screen();

using namespace std;
int main() {
  int ch;

  initscr();            /* Start curses mode 		*/
  start_color();        /* Start the color functionality */
  cbreak();             /* Line buffering disabled, Pass on
                         * everty thing to me 		*/
  keypad(stdscr, TRUE); /* I need that nifty F1 	*/
  curs_set(0);          // hide cursor
  noecho();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);


  shared_ptr<Character> c = make_shared<Character> (5, LINES-8);
  shared_ptr<Obstacle> o = make_shared<Obstacle> (30, LINES-8);
  timeout(100);
  while ((ch = getch()) != KEY_F(1)) {
    switch (ch) {
    case 'a':
      c->jump(1);
      break;
    case 's':
    case ' ':
      c->jump(0);
      break;
    case 'd':
      c->jump(-1);
    }
    clear_screen();
    debug("%d, %d, %f, %d, %d", c->x, c->y, c->dy, c->jumping, c->can_jump);
    c->draw();
    c->update();

    o->draw();
    o->update();

    if (c->collides(o.get())) {
      break;
    }

    attron(COLOR_PAIR(1));
    mvprintw(5, 2, "Press F1 to exit. Press A to jump high, S/SPACE to normal jump, D to barely jump");
    attroff(COLOR_PAIR(1));
  }
  endwin(); /* End curses mode		  */
  return 0;
}


void clear_screen() {
  int x, y, w, h;

  x = 0;
  y = 0;
  w = COLS;
  h = LINES;

  for (int j = y; j <= y + h; ++j) {
    for (int i = x; i <= x + w; ++i) {
      mvaddch(j, i, ' ');
    }
  }
}
