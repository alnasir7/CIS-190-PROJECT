#include "character.hpp"
#include "drawablecollection.hpp"
#include "obstacle.hpp"
#include <iostream>
#include <memory>
#include <ncurses.h>

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

  setlocale(LC_ALL, "");
  initscr();            /* Start curses mode 		*/
  start_color();        /* Start the color functionality */
  cbreak();             /* Line buffering disabled, Pass on
                         * everty thing to me 		*/
  keypad(stdscr, TRUE); /* I need that nifty F1 	*/
  curs_set(0);          // hide cursor
  noecho();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);

  int high_score = 0;
  bool running = true;
  while (running) {

    shared_ptr<Character> c = make_shared<Character>(8, LINES - 8);

    unique_ptr<ObstacleCollection> obstacles =
        make_unique<ObstacleCollection>();
    timeout(33); // 16 is about 60 fps, 33 is about 30
    int cnt = 0;
    while ((ch = getch()) != KEY_F(1)) {
      switch (ch) {
      case 'a':
        c->jump(0.2);
        break;
      case 's':
      case ' ':
        c->jump(0);
        break;
      case 'd':
        c->jump(-0.2);
      }
      clear_screen();
      debug("%d, %d, %f, %d, %d, %d", c->x, c->y, c->dy, c->jumping,
            c->can_jump, obstacles->size());
      c->draw();
      c->update();

      obstacles->draw();
      obstacles->update();

      if (obstacles->collides_with_character(c)) {
        break;
      }

      if (++cnt % 50 == 1) {
        obstacles->generate();
      }

      attron(COLOR_PAIR(1));
      mvprintw(5, 2,
               "Press A to jump high, S/SPACE to normal jump, "
               "D to barely jump");
      mvprintw(6, 2, "Score: %d", cnt / 10);
      attroff(COLOR_PAIR(1));
    }
    clear_screen();
    high_score = max(high_score, cnt / 10);
    attron(COLOR_PAIR(1));
    mvprintw(5, 2, "Your score is: %d", cnt / 10);
    mvprintw(6, 2, "Your high score is: %d", high_score);
    attroff(COLOR_PAIR(1));

    timeout(-1);
    while ((ch = getch()) != ' ' && ch != 'n')
      ;
    switch (ch) {
    case ' ':
      continue;
    case 'n':
      running = false;
      break;
    default:
        // should not run
        // no op
        ;
    }
  }

  endwin(); /* End curses mode		  */
  cout << "High score: " << high_score << endl;
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