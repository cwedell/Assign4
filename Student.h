#include <iostream>

using namespace std;

class Student {
private:
  int timeArrived;
  int timeHelped;
  int timeNeeded;
  int waitTime;

public:
  Student();
  Student(int a, int n);
  ~Student();

  int getTimeArrived();
  void setTimeArrived(int t);
  int getTimeHelped();
  void setTimeHelped(int t);
  int getTimeNeeded();
  void setTimeNeeded(int t);
  int getWaitTime();
  void setWaitTime(int t);
};
