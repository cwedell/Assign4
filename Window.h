#include "Student.h"
#include <iostream>

using namespace std;

class Window {
private:
  int idleTime;
  bool isIdle;
  Student myStudent;

public:
  Window();
  Window(bool i, Student s);
  ~Window();

  int getIdleTime();
  void setIdleTime(int t);
  bool getIsIdle();
  void setIsIdle(bool b);
  Student getStudent();
  void setStudent(Student s);
};
