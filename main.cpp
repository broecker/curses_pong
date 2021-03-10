#include <cstdlib>
#include <iostream>

#include <curses.h>

void cleanup() { endwin(); }

int main(int argc, const char **argv) {
  std::cout << "Hello World!" << std::endl;

  initscr();
  cbreak();
  noecho();
  clear();

  refresh();
  getch();

  atexit(cleanup);

  return 0;
}