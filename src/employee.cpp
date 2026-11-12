
#include "../include/employee.hpp"

#include <iostream>
#include <limits>

#include "../include/appConfig.hpp"
#include "../include/stdTypes.hpp"
#include "../include/string.hpp"

using namespace string;

using namespace employee;

using namespace std;

namespace employee {

uint8_t validateString(char* str) {
  uint8_t ERROR_STATE = E_OK;
  int len = iStringLengthPc(str);
  if (str == nullptr || len == 0 || len >= 20) {
    ERROR_STATE = E_NOK;
  } else {
    // do nothing
  }

  return ERROR_STATE;
}

uint8_t validatesalary(int salary) {
  uint8_t ERROR_STATE = E_OK;

  if ((salary == '\n' || salary == '\r') || salary <= 0) {
    ERROR_STATE = E_NOK;
  } else {
    // do nothing
  }

  return ERROR_STATE;
}
uint8_t validateAge(int age) {
  uint8_t ERROR_STATE = E_OK;

  if ((age == '\n' || age == '\r') || age <= 0 || age > 100) {
    ERROR_STATE = E_NOK;
  } else {
    // do nothing
  }

  return ERROR_STATE;
}
void createNewEmployee(Employee* employee) {
  // #if DATA_MODE == CLASS_AND_STATIC_ARRAY
  uint8_t ERROR_STATE = E_OK;
  char name[20], department[20];
  fill(name, name + 20, '\0');
  fill(name, name + 20, '\0');
  int age, salary;

  // Enter Name ------------------
  do {
    if (ERROR_STATE == E_NOK) {
      cout << "Enter a valid Employee Name: ";
    } else {
      cout << "Enter Employee Name: ";
    }
    cin.getline(name, NAME_LENGTH);
    ERROR_STATE = validateString(name);
  } while (ERROR_STATE == E_NOK);
  employee->setName(name);
  ERROR_STATE = E_OK;

  // Enter Age ------------------
  do {
    if (ERROR_STATE == E_NOK) {
      cout << "Enter a valid age: ";
    } else {
      cout << "Enter Employee age: ";
    }
    if (!(cin >> age)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ERROR_STATE = validateAge(age);
  } while (ERROR_STATE == E_NOK);
  employee->setAge(age);
  ERROR_STATE = E_OK;

  // Enter Department ------------------
  do {
    if (ERROR_STATE == E_NOK) {
      cout << "Enter a valid Employee Department: ";
    } else {
      cout << "Enter Employee Department: ";
    }
    cin.getline(department, DEPARTMET_LENGTH);
    ERROR_STATE = validateString(department);
  } while (ERROR_STATE == E_NOK);
  employee->setDepartment(department);
  ERROR_STATE = E_OK;

  // Enter Salary ------------------
  do {
    if (ERROR_STATE == E_NOK) {
      cout << "Enter a valid Salary: ";
    } else {
      cout << "Enter Employee Salary: ";
    }
    if (!(cin >> salary)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ERROR_STATE = validatesalary(salary);
  } while (ERROR_STATE == E_NOK);
  employee->setSalary(salary);
  ERROR_STATE = E_OK;
}

#if DATA_MODE == CLASS_AND_STATIC_ARRAY

uint8_t appendEmployee(Employee emp, Employee* employees, int currentPosition) {
  uint8_t ERROR_STATE = E_OK;
  if (currentPosition < NUMBER_OF_EMPLOYEES) {
    employees[currentPosition] = emp;
  } else {
    ERROR_STATE = E_NOK;
  }

  return ERROR_STATE;
}

#elif DATA_MODE == STRUCT_AND_DYNAMIC_ARRAY

uint8_t appendEmployee(Employee emp, Employee** employees, int currentPosition,
                       int* currentsize) {
  uint8_t ERROR_STATE = E_OK;
  if (currentsize == nullptr) {
    *currentsize = NUMBER_OF_EMPLOYEES;
  }
  if (currentPosition < *currentsize) {
    (*employees)[currentPosition] = emp;
  } else {
    *currentsize *= 2;
    Employee* newEmployees = new Employee[*currentsize];
    for (int i = 0; i < currentPosition; i++) {
      newEmployees[i] = (*employees)[i];
    }
    delete[] * employees;
    *employees = newEmployees;
  }

  return ERROR_STATE;
}

// imp of struct & from 46 & 52
#else
// do nothing
#endif

void displayEmployees(Employee* employees, int numOfEmployees) {
  cout << "Employees:\n";
  for (int i = 0; i < numOfEmployees; i++) {
    char name[20], department[20];
    fill(name, name + 20, '\0');
    fill(department, department + 20, '\0');
    employees[i].getName(name);
    employees[i].getDepartment(department);
    cout << "Employee" << i + 1 << ":\n";
    cout << "Name: " << name << ", Age: " << employees[i].getAge()
         << ", Salary:" << employees[i].getSalary()
         << " ,Department: " << department << endl;
  }
}

}  // namespace employee
