#include <cstdlib>
#include <curses.h>
#include <unistd.h>

// Terminal size.
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

  main_window = newwin(term_size_y, term_size_x, 0, 0);
}

void cleanup() { 
  endwin(); 
}

void getWindowDimensions() {
  getmaxyx(stdscr, term_size_y, term_size_x);
}

bool collideAndClampPosition(int* position, int min, int max) {
  if (*position > max) {
    *position = max;
    return true;
  }
  if (*position < min) {
    *position = min;
    return true;
  }
  return false;
}

int main(int argc, const char **argv) {
  init();
  atexit(cleanup);
  getWindowDimensions();
  
  // Ball
  int x = rand() % term_size_x, y = rand() % term_size_y;
  int dx = 1, dy = 1;

  // Collision borders for the ball.
  int min_x = 1, max_x = term_size_x, min_y = 1, max_y = term_size_y;

  while (true) {
    getWindowDimensions();
    // Update the collision borders.
    max_x = term_size_x-1;
    max_y = term_size_y-1;

    // Clear the window.
    wclear(main_window);

    // Center text roughly in the center of the window.
    int text_offset_y = term_size_y/2-1;
    int text_offset_x = term_size_x/2-10;
    mvwprintw(main_window, text_offset_y, text_offset_x, "Term: %dx%d", term_size_x, term_size_y);
    mvwprintw(main_window, text_offset_y+1, text_offset_x, "Ball: %d,%d", x, y);
    mvwprintw(main_window, text_offset_y+2, text_offset_x, "[Esc] to exit");

    // Draw the window
    wborder(main_window, 0, 0, 0, 0, 0, 0, 0, 0);

    // Draw the ball.
    mvwprintw(main_window, y, x, "@");

    // Draw the window contents.    
    wrefresh(main_window);

    // Ball movement and collision detection
    x += dx;
    y += dy;
    if (collideAndClampPosition(&x, min_x+1, max_x-1)) {
      dx *= -1;
    }
    if (collideAndClampPosition(&y, min_y+1, max_y-1)) {
      dy *= -1;
    }

    // Watch for exit key.
    const int c = getch();
    if (c == 27 || c == 'q') {
      exit(0);
    }

    usleep(30000);
  }

  cleanup();
  return 0;
}