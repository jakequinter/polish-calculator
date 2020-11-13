//
//  info.cpp
//  Calculator
//
//  Created by Jake Quinter on 11/13/20.
//

#include <iostream>
#include <string>
#include "info.h"

using namespace std;

void info::identify()
{
  cout << "*****************************************\n";
  cout << "Course:         " << course << endl;
  cout << "Instructor:     " << instructor << endl;
  cout << "Developer:      " << developer << endl;
  cout << "*****************************************\n\n";
}

void info::identify(string assignmentName)
{
  cout << "*****************************************\n";
  cout << "Course:         " << course << endl;
  cout << "Instructor:     " << instructor << endl;
  cout << "Developer:      " << developer << endl;
  cout << "Assignment:     " << assignmentName << endl;
  cout << "*****************************************\n\n";
}

info::~info()
{
    
}

info::info()
{
    course = "CPS362 Data Structures";
    instructor = "Judith Ligocki";
    developer = "Jake Quinter";
}
