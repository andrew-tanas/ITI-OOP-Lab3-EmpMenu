#include "../include/ArrowInput2.hpp"

#include <termios.h>  // Used to control terminal settings
#include <unistd.h>   // Provides Unix functions such as read

#include <cstdio>    // C standard I/O functions such as printf
#include <iostream>  // Standard input/output library

// Alternative implementation of getch() for Linux systems
namespace ArrowInput2 {
char getch_linux() {
  char buf = 0;  // Variable to store the input character

  struct termios old = {0};  // Structure to save current terminal settings

  // Save the current terminal settings
  tcgetattr(0, &old);

  // Disable Canonical Mode (do not wait for Enter key)
  old.c_lflag &= ~ICANON;

  // Disable Echo so typed characters are not displayed
  old.c_lflag &= ~ECHO;

  // Require at least one character to be read
  old.c_cc[VMIN] = 1;

  // No timeout while waiting for input
  old.c_cc[VTIME] = 0;

  // Apply the modified settings immediately
  tcsetattr(0, TCSANOW, &old);

  // Read a single character immediately from the keyboard
  read(0, &buf, 1);

  // Re-enable Canonical Mode
  old.c_lflag |= ICANON;

  // Re-enable Echo
  old.c_lflag |= ECHO;

  // Restore the terminal to its original settings
  tcsetattr(0, TCSADRAIN, &old);

  // Return the character that was read
  return buf;
}

}  // namespace ArrowInput2
