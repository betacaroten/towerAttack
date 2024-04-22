#include <fstream>
#include <sstream>
#include <string>
#include <ncurses.h>

#include "Screen.hpp"

void initColours() {
  init_pair(7, COLOR_BLACK, COLOR_WHITE);
  init_pair(9, COLOR_BLUE, COLOR_BLACK);
  init_pair(8, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
}

int main() {
  initscr();
  nodelay(stdscr, TRUE);
  
  if (has_colors() == FALSE) {
    printw("%s", "Colours not supported\n");
    refresh();
  }
  noecho();
  start_color();
  initColours();
  curs_set(0);
  
  attron(COLOR_PAIR(9));
  std::string welcome = "TOWER ATTACK\n"
                        "\n";
  attroff(COLOR_PAIR(9));
  
  attron(COLOR_PAIR(2));
  printw(welcome.c_str());
  attroff(COLOR_PAIR(2));
  
  Screen screen;
  bool quit = screen.choseGameScreen();
  
  if (quit) {
    attron(COLOR_PAIR(8));
    printw("\n\n\n\n\nThank you for playing ~ (c) AM.\n");
    attroff(COLOR_PAIR(8));
    refresh();
  }
  
  curs_set(1);
  
  endwin();
  return 0;
}