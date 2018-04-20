#ifndef MEGACALC_H
#define MEGACALC_H
#include "MegaInt.h"

#include<string>
#include<iostream>
using std::ostream;
using std::string;

	class MegaCalc
	{
		
	private:
		MegaInt accumulator;
		string rawcommand;
		char operation;
		MegaInt operand;
		string mode;
		char* positive{ "+" };
	public:
		//Constructor/destructor
		MegaCalc();
		~MegaCalc();

		// Main operations
		void factorial();
		MegaInt hailstone();
		void welcome();
		void quit();

		//runner
		void run();
		void parse();
		void help();
		void clear();
		
	};

#endif // !MEGACALC_H