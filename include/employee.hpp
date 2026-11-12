#ifndef _EMPLOYEE_HPP_
#define _EMPLOYEE_HPP_

#include <iostream>

#include "appConfig.hpp"
#include "stdTypes.hpp"
#include "string.hpp"

using namespace std;

using namespace string;

namespace employee {
#if DATA_MODE == CLASS_AND_STATIC_ARRAY

class Employee {
 private:
  int age;
  char name[20];
  char department[20];
  int salary;

 public:
  // Employee() {
  //   age = 0;
  //   fill(name, name + 20, 'a');
  //   fill(department, department + 20, 'a');
  //   salary = 0;
  // }
  // setter
  void setName(char* name) {
    fill(this->name, this->name + 20, '\0');
    iCopyStaticStringWithSameLength(name, this->name);
  }
  void setAge(int age) { this->age = age; }
  void setDepartment(char* department) {
    fill(this->department, this->department + 20, '\0');
    iCopyStaticStringWithSameLength(department, this->department);
  }
  void setSalary(int salary) { this->salary = salary; }

  // getter
  void getName(char* name) {
    iCopyStaticStringWithSameLength(this->name, name);
  }
  int getAge() { return this->age; }
  void getDepartment(char* department) {
    iCopyStaticStringWithSameLength(this->department, department);
  }
  int getSalary() { return this->salary; }
};
uint8_t appendEmployee(Employee emp, Employee* employees, int currentPosition);

#elif DATA_MODE == STRUCT_AND_DYNAMIC_ARRAY
typedef struct {
 private:
  int age;
  char name[20];
  char department[20];
  int salary;

 public:
  // Employee() {
  //   age = 0;
  //   fill(name, name + 20, 'a');
  //   fill(department, department + 20, 'a');
  //   salary = 0;
  // }
  // setter
  void setName(char* name) {
    fill(this->name, this->name + 20, '\0');
    iCopyStaticStringWithSameLength(name, this->name);
  }
  void setAge(int age) { this->age = age; }
  void setDepartment(char* department) {
    fill(this->department, this->department + 20, '\0');
    iCopyStaticStringWithSameLength(department, this->department);
  }
  void setSalary(int salary) { this->salary = salary; }

  // getter
  void getName(char* name) {
    iCopyStaticStringWithSameLength(this->name, name);
  }
  int getAge() { return this->age; }
  void getDepartment(char* department) {
    iCopyStaticStringWithSameLength(this->department, department);
  }
  int getSalary() { return this->salary; }
} Employee;
uint8_t appendEmployee(Employee emp, Employee** employees, int currentPosition,
                       int* currentsize = nullptr);

#else
#error please select correct data structure approach :)

#endif

void createNewEmployee(Employee* employee);
void displayEmployees(Employee* employees, int numOfEmployees);

}  // namespace employee

#endif