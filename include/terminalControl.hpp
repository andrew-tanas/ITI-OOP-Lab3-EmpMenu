#ifndef TERMINAL_CONTROL_HPP_
#define TERMINAL_CONTROL_HPP_

namespace terminalControl {

bool bInitTerminal();
void vResetTerminal();
void vChangeTextColor(int color);
void vChangeBackgroundColor(int color);
void vMoveCursor(int x, int y);
void vClearScreen();
void vPrintColoredTextAtPosition(int x, int y, char* text, int textColor,
                                 int backgroundColor);
}  // namespace terminalControl
// void vResetTerminal();
// void vChangeTextColor(int color);
// void vChangeBackgroundColor(int color);
// void vMoveCursor(int row, int col);
// void vClearScreen();

#endif