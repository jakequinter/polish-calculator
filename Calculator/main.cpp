//
//  main.cpp
//  Calculator
//
//  Created by Jake Quinter on 11/13/20.
//

#include <iostream>

#include "info.h"
#include "calculator.h"

int main(int argc, const char * argv[]) {
    
    // info
    info myInfo;
    myInfo.identify("Assignment #9: Calculator");
    
    calculator polishCalculator;
    polishCalculator.calculatorTest(polishCalculator);
    
    return 0;
}
