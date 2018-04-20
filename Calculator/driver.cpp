

#include "MegaCalc.h"
#include "MegaInt.h"
#include <iostream>
#include <deque>
using namespace std;


int main()
{
	
	MegaCalc mc; //Create a calculator
	mc.run();//use it
	return EXIT_SUCCESS;
}//mc's destructor may throw an exception