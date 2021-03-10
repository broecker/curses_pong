#include <cstdlib>
#include <curses.h>
#include <unistd.h>

int term_size_x = 0;
int term_size_y = 0;

WINDOW* main_window = nullptr;

void init() {
	initscr();
	cbreak();
  // Don't display a cursor.
  curs_set(FALSE);
  // Don;t echo keypresses.
	noecho();
  // Return from getch after 0.1s
  halfdelay(1);
	keypad(stdscr, TRUE);
	refresh();
}

void cleanup() { 
  endwin(); 
}

void getWindowDimensions() {
  getmaxyx(stdscr, term_size_y, term_size_x);
}

int main(int argc, const char **argv) {
  init();
  getWindowDimensions();
  atexit(cleanup);

  getWindowDimensions();

  // Ball
  int x = rand() % term_size_x, y = rand() % term_size_y;
  int dx = 1, dy = 1;

  while (true) {
    getWindowDimensions();
    clear();

    int text_offset = term_size_y/2;
    mvprintw(text_offset, 20, "Term: %dx%d", term_size_x, term_size_y);
    mvprintw(text_offset+1, 20, "Ball: %d,%d", x, y);

    // Draw the ball.
    mvprintw(y, x, "@");
    refresh();

    // Ball movement and collision detection
    x += dx;
    y += dy;
    if (x >= term_size_x) {
      x = term_size_x-1;
      dx *= -1;
    }
    if (x < 0) {
      x = 0;
      dx *= -1;
    }
    if (y >= term_size_y) {
      y = term_size_y-1;
      dy *= -1;
    }
    if (y < 0) {
      y = 0;
      dy *= -1;
    }

    const int c = getch();
    if (c == 27 || c == 'q') {
      exit(0);
    }


    usleep(30000);
  }

  cleanup();
  return 0;
}