#include "../include/terminalControl.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

namespace terminalControl {

bool bInitTerminal() {
#ifdef _WIN32
  HANDLER console = GetStdHandle(STD_OUTPUT_HANDLE);

  if (console == INVALID_HANDLE_VALUE) return false;

  DWORD mode = 0;
  if (!GetConsoleMode(console, &mode) return false;

      mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;)
    if (!SetConsoleMode(console, mode)) return false;

#endif

  return true;
}

void vChangeTextColor(int color) { cout << "\033[" << color << "m"; }
void vChangeBackgroundColor(int color) { cout << "\033[" << color << "m"; }
void vMoveCursor(int x, int y) {
  cout << "\033[" << y << ";" << x << "H";
  cout.flush();
}
void vClearScreen() {
  cout << "\033[2J";
  cout.flush();
}
void vResetTerminal() {
  // Reset terminal settings to default
  cout << "\033[0m";  // Reset all attributes
  // cout << "\033[?25h";  // Show cursor
  // cout << "\033[2J";    // Clear screen
  // cout << "\033[H";     // Move cursor to home position
  cout.flush();
}

void vPrintColoredTextAtPosition(int x, int y, char* text, int textColor,
                                 int backgroundColor) {
  vMoveCursor(x, y);
  vChangeTextColor(textColor);
  vChangeBackgroundColor(backgroundColor);
  cout << text << '\n';
  vResetTerminal();
}

}  // namespace terminalControl