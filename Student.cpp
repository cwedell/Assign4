#include "Student.h"
#include <iostream>

using namespace std;

Student::Student() {
  timeArrived = -1;
  timeHelped = -1;
  timeNeeded = -1;
  waitTime = -1;
}

Student::Student(int a, int n) {
  timeArrived = a;
  timeHelped = 0;
  timeNeeded = n;
  waitTime = 0;
}

Student::~Student() {
}

int Student::getTimeArrived() {
  return timeArrived;
}

void Student::setTimeArrived(int t) {
  timeArrived = t;
}

int Student::getTimeHelped() {
  return timeHelped;
}

void Student::setTimeHelped(int t) {
  timeHelped = t;
}

int Student::getTimeNeeded() {
  return timeNeeded;
}

void Student::setTimeNeeded(int t) {
  timeNeeded = t;
}

int Student::getWaitTime() {
  return waitTime;
}

void Student::setWaitTime(int t) {
  waitTime = t;
}
