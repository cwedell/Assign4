#include "GenQueue.h"
#include "Window.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main(int c, char** argv) {
  // read file *****************************************************************
  ifstream filein;
  try {
    filein.open(argv[1]);
  } catch(exception& e) {
    cout << "File not found." << endl;
    return 1;
  }
  int lineCount = 0; // number of lines in file
  string instring = "";
  int linetoint = 0;
  int numWindows = 0; // number of windows
  int countArrivals = 0; // number of arrival times
  bool countingArrivals = false;
  bool countingWaves = false;
  int maxWave = 0; // number of students in largest wave
  int nextArrival = 0; // number of lines until a arrival time appears
  int linestonextArrival = 0; // counts up until next arrival time
  int countStudents = 0; // counts number of students
  while(getline(filein, instring)) {
    linetoint = 0;
    try {
      linetoint = stoi(instring);
    } catch(exception& e) {
      cout << "Non-numeric data found in line " << lineCount + 1 << endl;
      return 1;
    }
    if(lineCount == 0) { // first line, number of windows
      numWindows = linetoint;
      countingArrivals = true; // next line will have the first arrival time
      goto CONTINUE;
    }
    if(nextArrival == linestonextArrival && lineCount > 2 && !countingWaves) { // this line is another arrival time
      countingArrivals = true;
    }
    if(countingWaves) { // counting a wave
      if(linetoint > maxWave) {
        maxWave = linetoint;
      }
      nextArrival = linetoint;
      linestonextArrival = 0;
      countStudents += linetoint;
      countingWaves = false;
    } else if(countingArrivals) { // counting an arrival time
      ++countArrivals;
      countingArrivals = false;
      countingWaves = true;
    } else {
      ++linestonextArrival; // count up lines to next wave
    }
    CONTINUE: ;
    ++lineCount;
  }
  if(lineCount != 1 + (2 * countArrivals) + countStudents) {
    cout << "Unexpected number of lines. Check your input file for missing or extra wait times." << endl;
    return 1;
  }
  filein.close();
  filein.open(argv[1]);
  int arrivalTimes[countArrivals]; // arrival times for each wave
  int numStudents[countArrivals]; // number of students in each wave
  int waitTimes[countArrivals][maxWave]; // wait times for each student in each wave
  lineCount = 0;
  countArrivals = 0;
  countingArrivals = true;
  nextArrival = 0;
  linestonextArrival = 0;
  while(getline(filein, instring)) {
    linetoint = stoi(instring);
    if(lineCount > 0) {
      if(nextArrival == linestonextArrival && lineCount > 2 && !countingWaves) {
        countingArrivals = true;
      }
      if(countingWaves) {
        numStudents[countArrivals - 1] = linetoint; // save the number of students in this wave
        nextArrival = linetoint;
        linestonextArrival = 0;
        countingWaves = false;
      } else if(countingArrivals) {
        arrivalTimes[countArrivals] = linetoint; // save the arrival time of this wave
        ++countArrivals;
        countingArrivals = false;
        countingWaves = true;
      } else {
        waitTimes[countArrivals - 1][linestonextArrival] = linetoint; // save the wait time for this student
        ++linestonextArrival;
      }
    }
    ++lineCount;
  }
  for(int i = 0; i < countArrivals; ++i) {
    for(int j = numStudents[i]; j < maxWave; ++j) { // initialize any unused values in the waitTimes array
      waitTimes[i][j] = -1;
    }
  }
  filein.close();

  // queue *********************************************************************
  GenQueue <Student> myQueue = GenQueue<Student>();
  Window arrWindows[numWindows];
  for(int i = 0; i < numWindows; ++i) {
    arrWindows[i] = Window();
  }
  bool finished = false;
  int clockTick = 0;
  int numWave = 0;
  int numWindowsIdle = numWindows;
  int longestIdle = -1;
  int maxIdleTime = -1;
  Student arrStudents[countStudents]; // array to hold students after finished at window
  int arrStudentsIdx = 0;
  Student currStudent;
  while(!finished) {
    if(clockTick == arrivalTimes[numWave]) {
      for(int i = 0; i < numStudents[numWave]; ++i) {
        myQueue.insert(Student(clockTick, waitTimes[numWave][i])); // add student to the queue with arrival time and wait time needed
      }
      ++numWave;
    }
    for(int i = 0; i < numWindows; ++i) { // determine if any students are finished
      if(!arrWindows[i].getIsIdle()) {
        if(arrWindows[i].getStudent().getTimeHelped() + arrWindows[i].getStudent().getTimeNeeded() <= clockTick) {
          Student empty;
          arrStudents[arrStudentsIdx] = arrWindows[i].getStudent();
          arrWindows[i].setStudent(empty);
          arrWindows[i].setIsIdle(true);
          ++arrStudentsIdx;
          ++numWindowsIdle;
        }
      }
      if(arrStudentsIdx == countStudents) { // if array of students is full, simulation finished
        goto SIM_FINISHED;
      }
    }
    while(numWindowsIdle > 0 && !myQueue.isEmpty()) {
      longestIdle = -1;
      maxIdleTime = -1;
      for(int i = 0; i < numWindows; ++i) { // get idle window that has been idle the longest
        if(arrWindows[i].getIsIdle() && arrWindows[i].getIdleTime() > maxIdleTime) {
          longestIdle = i;
          maxIdleTime = arrWindows[i].getIdleTime();
        }
      }
      currStudent = myQueue.remove();
      currStudent.setTimeHelped(clockTick); // set the time the student was helped
      currStudent.setWaitTime(clockTick - currStudent.getTimeArrived()); // set the time the student waited
      arrWindows[longestIdle].setStudent(currStudent); // remove student from the queue and place them at a window
      arrWindows[longestIdle].setIsIdle(false);
      --numWindowsIdle;
    }
    for(int i = 0; i < numWindows; ++i) {
      if(arrWindows[i].getIsIdle()) { // increment idle time
        arrWindows[i].setIdleTime(arrWindows[i].getIdleTime() + 1);
      }
    }
    ++clockTick;
  }
  SIM_FINISHED: ;

  // output statistics *********************************************************
  int sumWaitTimes = 0;
  float meanWaitTime = 0.0f;
  float medianWaitTime = 0.0f;
  int maxWaitTime = 0;
  int num10MinuteWaitTime = 0;
  int sumIdleTimes = 0;
  float meanIdleTime = 0.0f;
  int maxWindowIdleTime = 0;
  int num5MinuteIdleTime = 0;
  int arrStudentWaitTimes[countStudents];
  for(int i = 0; i < countStudents; ++i) { // create array of wait times
    arrStudentWaitTimes[i] = arrStudents[i].getWaitTime();
  }
  sort(arrStudentWaitTimes, arrStudentWaitTimes + countStudents); // sort to find median
  for(int i = 0; i < countStudents; ++i) { // gather statistics on student wait times
    sumWaitTimes += arrStudentWaitTimes[i];
    if(arrStudentWaitTimes[i] > maxWaitTime) {
      maxWaitTime = arrStudentWaitTimes[i];
    }
    if(arrStudentWaitTimes[i] > 10) {
      ++num10MinuteWaitTime;
    }
  }
  meanWaitTime = sumWaitTimes / countStudents;
  if(countStudents % 2 == 0) { // if length even, need average of two middle values
    int idx = countStudents / 2;
    medianWaitTime = (arrStudentWaitTimes[idx] + arrStudentWaitTimes[idx + 1]) / 2;
  } else {
    int idx = (countStudents / 2) + 0.5;
    medianWaitTime = arrStudentWaitTimes[idx];
  }
  for(int i = 0; i < numWindows; ++i) { // gather statistics on window idle times
    sumIdleTimes += arrWindows[i].getIdleTime();
    if(arrWindows[i].getIdleTime() > maxIdleTime) {
      maxWindowIdleTime = arrWindows[i].getIdleTime();
    }
    if(arrWindows[i].getIdleTime() > 5) {
      ++num5MinuteIdleTime;
    }
    meanIdleTime = sumIdleTimes / numWindows;
  }
  cout << "Mean student wait time: " << meanWaitTime << endl;
  cout << "Median student wait time: " << medianWaitTime << endl;
  cout << "Longest student wait time: " << maxWaitTime << endl;
  cout << "Number of students waiting over 10 minutes: " << num10MinuteWaitTime << endl;
  cout << "Mean window idle time: " << meanIdleTime << endl;
  cout << "Longest window idle time: " << maxWindowIdleTime << endl;
  cout << "Number of windows idle for over 5 minutes: " << num5MinuteIdleTime << endl;
  return 0;
}
