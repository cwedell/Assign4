#include "Window.h"
#include <iostream>

using namespace std;

Window::Window() {
  idleTime = 0;
  isIdle = true;
  myStudent;
}

Window::Window(bool i, Student s) {
  idleTime = 0;
  isIdle = i;
  myStudent = s;
}

Window::~Window() {
}

int Window::getIdleTime() {
  return idleTime;
}

void Window::setIdleTime(int t) {
  idleTime = t;
}

bool Window::getIsIdle() {
  return isIdle;
}

void Window::setIsIdle(bool b) {
  isIdle = b;
}

Student Window::getStudent() {
  return myStudent;
}

void Window::setStudent(Student s) {
  myStudent = s;
}
