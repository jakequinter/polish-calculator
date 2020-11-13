//
//  info.hpp
//  Calculator
//
//  Created by Jake Quinter on 11/13/20.
//

#ifndef info_h
#define info_h

#include <stdio.h>
#include <string>

using namespace std;

class info
{
  // data members (variables)
private:
    string course;
    string developer;
    string instructor;

  // methods
public:
    void identify();
    void identify(string assignmentName);
    ~info();
    info();
};

#endif
