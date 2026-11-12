#include "../include/menu.hpp"

#include <iostream>

#include "../include/ArrowInput2.hpp"
#include "../include/appConfig.hpp"
#include "../include/appPrivate.hpp"
#include "../include/employee.hpp"
#include "../include/stdTypes.hpp"
#include "../include/terminalControl.hpp"
#include "sys/ioctl.h"
#include "unistd.h"

using namespace employee;

using namespace ArrowInput2;

using namespace terminalControl;

using namespace std;

using namespace terminalControl;

using namespace menu;

// #define NUMBER_OF_EMPLOYEES 20

namespace menu {
void vViewHomeScreen() {
  vPrintColoredTextAtPosition(X_POSITION, NEW_POSITION, "New", 32, 45);
  vPrintColoredTextAtPosition(X_POSITION, DISPLAY_POSITION, "Display", 33, 46);
  vPrintColoredTextAtPosition(X_POSITION, EXIT_POSITION, "Exit", 34, 47);
  vMoveCursor(CURSOR_X, NEW_POSITION);
}

void vViewMenu() {
  int currentX = CURSOR_X, currentY = NEW_POSITION, currentEmp = 0;

#if DATA_MODE == CLASS_AND_STATIC_ARRAY
  // do nothing
  Employee emps[NUMBER_OF_EMPLOYEES];
#elif DATA_MODE == STRUCT_AND_DYNAMIC_ARRAY
  Employee *emps = new Employee[NUMBER_OF_EMPLOYEES];
  int currentSize = NUMBER_OF_EMPLOYEES;
#else
  // do nothin

#endif

  char currentPage = 'h';
  char byte1 = 'q';
  char byte2 = 'q';
  char byte3 = 'q';
  char flag = 'y';
  uint8_t ERROR_STATE = E_OK;
  // Display instructions for the user
  printf("Press the arrow keys to test the program (press 'q' to quit):\n");

  vViewHomeScreen();

  // Infinite loop that runs until the user chooses to quit
  do {
    // Read a key from the user
    byte1 = getch_linux();
    // cout<<"Byte 1 :: "<<byte1<<endl;
    // If the key is the beginning of an arrow-key escape sequence
    if (byte1 == '\n' || byte1 == '\r') {
      // printf("%c", byte1);
      vClearScreen();
      // go to current page
      switch (currentY) {
        case NEW_POSITION:
          currentPage = 'n';
          vPrintColoredTextAtPosition(X_POSITION, MIN_Y_POSITION,
                                      "Enter the Employees data:", 32, 45);
          Employee employee;

          do {
#if DATA_MODE == CLASS_AND_STATIC_ARRAY

            if (currentEmp < NUMBER_OF_EMPLOYEES) {
              cout << "Enter Employee Number " << currentEmp + 1 << " data: \n";
              createNewEmployee(&employee);
              ERROR_STATE = appendEmployee(employee, emps, currentEmp);
            } else {
              ERROR_STATE = E_NOK;
            }
#elif DATA_MODE == STRUCT_AND_DYNAMIC_ARRAY
            cout << "Enter Employee Number " << currentEmp + 1 << " data: \n";
            createNewEmployee(&employee);
            ERROR_STATE =
                appendEmployee(employee, &emps, currentEmp, &currentSize);
#else
// do nothing
#endif

            if (ERROR_STATE == E_NOK) {
              cout << "you Can't add new Employee\n";
              uint8_t flag;
              do {
                cout << "Please Enter x if you want to exit: " << flush;
                flag = getch_linux();
                cout << endl;
              } while (flag != 'x' && flag != 'X');
              // break;
            } else {
              currentEmp++;
              cout << "Do you want to enter the next employee? y/n: " << flush;
              flag = getch_linux();
              cout << endl;
              while (flag != 'y' && flag != 'Y' && flag != 'n' && flag != 'N') {
                cout << "Please Enter y or n: ";
                flag = getch_linux();
                cout << endl;
              }
            }

          } while (flag != 'n' && flag != 'N' && ERROR_STATE == E_OK);
          currentPage = 'h';
          vClearScreen();
          vViewHomeScreen();

          // function  -------> scan data
          break;
        case DISPLAY_POSITION:
          currentPage = 'd';
          displayEmployees(emps, currentEmp);
          cout << "if you want to exit press x: " << flush;
          flag = getch_linux();
          cout << endl;
          while (flag != 'x' && flag != 'X') {
            cout << "Please Enter x if you want to exit: ";
            flag = getch_linux();
          }
          currentPage = 'h';
          vClearScreen();
          vViewHomeScreen();
          currentY = NEW_POSITION;

          break;
        case EXIT_POSITION:
          // currentPage = 'h';
          // vClearScreen();
          // vViewHomeScreen();
          byte1 = 'q';
          break;
        default:
          // do nothing
          break;
      }
    }
    if (byte1 == '\033') {
      int terminalBuffer = 0;
      ioctl(STDIN_FILENO, FIONREAD, &terminalBuffer);
      // cout << terminalBuffer;
      if (terminalBuffer == 2) {
        // Skip the second character '['
        byte2 = getch_linux();
        // cout<<"Byte 2 :: "<<byte2<<endl;
        byte3 = getch_linux();
        // The third character determines the arrow direction
        // cout<<"Byte 3 :: "<<byte3<<endl;
        switch (byte3) {
          case 'A':
            if (currentY > MIN_Y_POSITION) {
              currentY--;
              vMoveCursor(currentX, currentY);
              // printf("↑ Up Arrow\n");
            } else {
              // do nothing
            }
            break;

          case 'B':
            // currentY++;
            if (currentY < MAX_Y_POSITION) {
              currentY++;
              vMoveCursor(currentX, currentY);
              // printf("↓ Down Arrow\n");
            } else {
              // do nothing
            }
            break;

          case 'C':
            // currentX++;
            // vMoveCursor(currentX, currentY);
            // printf("→ Right Arrow\n");
            // break;

          case 'D':
            // currentX--;
            // vMoveCursor(currentX, currentY);
            // printf("← Left Arrow\n");
            break;
          case 'H':
            if (currentPage != 'h') {
              vClearScreen();
              vViewHomeScreen();
              currentX = 5;
              currentY = 20;
              vMoveCursor(5, 20);
            }
            printf("← Home Button \n");
            break;
          case 'F':
            printf("End Button\n");
            break;
        }
      } else {
        byte1 = 'q';
        // do nothing
      }

    } else {
      // do nothing
    }

    // cout << "=================================" << endl;
  } while (byte1 != 'q' &&
           byte1 != 'Q');  // Exit the program if the user presses Q or q
  // Exit the program successfully
  // vClearScreen();
  cout << '\n';
}
}  // namespace menu