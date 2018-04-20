#include"MegaCalc.h"
#include "MegaInt.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
using std::ostream;
#include <regex>
using std::iostream;

//constructors
MegaCalc::MegaCalc() : 
accumulator{ MegaInt(0,"+") },
rawcommand{},
operation{},
operand{ MegaInt()},
mode("on")
{
	welcome();
	cout << "Accumulator is empty" << endl << endl;
	//run();
}
	
MegaCalc::~MegaCalc()
{
}

//runner
void MegaCalc::run()
{
	while (mode == "on")
	{
		cout << "Welcome to the Mega Caculator: for very big digits" << endl << endl
			<< "Please enter a command 'q' to quit 'a' for help" << endl << ":";
			
		cin.clear();
		std::string input;
		std::getline(cin, input);
		//If input is empty, command is same as previous execution
		if (input == ""){ this->rawcommand = rawcommand; }
		else{ this->rawcommand = input; }
		//Handles empty input that comes during first run
		if (rawcommand == ""){ rawcommand = "a"; }
		//remove spaces
		rawcommand.erase(remove_if(rawcommand.begin(), rawcommand.end(), isspace), rawcommand.end());

		//remove tabs
		rawcommand.erase(remove(rawcommand.begin(), rawcommand.end(), '\t'), rawcommand.end());

		parse();

		switch (operation)
		{
		
		case 'c'://command to clear the accumulator
			accumulator.clear();
			cout << "Accumulator = " << accumulator << endl << endl;
			break;
		case 'n'://command to negate accumulator if it is positive
			accumulator.negate();
			cout << "Accumulator = " << accumulator << endl << endl;
			break;
		case 'f'://computes factorial, Member of MegaCalc
			this->factorial();
			cout << "Accumulator = " << accumulator << endl << endl;
			break;
		case 'h': //Coomputes Hailstone Member of MegaCalc
			hailstone();
			break;
		case'm': //Clears the screen
			clear();
			break;
		case'p': //Print the Accumulator
			cout << "Accumulator = " << this->accumulator << endl << endl;
			break;
		case 'a': //Print help menu
			help();
			break;
		case 'q': //Exit calculator
			this->quit();
			break;
		case '+': //Adds operand to accumulator and sets accumulator equal to results
			accumulator + operand;
			break;
		case'-': //Subtracts operand from accumulator and sets accumulator equal to results
			accumulator - operand;
			break;
		case '*': //Multiplies operand by accumulator and sets accumulator equal to results
			accumulator * operand;
			break;
		case '/': //Multiplies operand by accumulator and sets accumulator equal to results
			accumulator / operand;
			break;
		case '%':// Computes modulus and sets accumulator equal to results
			accumulator % operand; 
			break;
		case '=': //Assigns the value of Accumulator to the input operand
			accumulator = operand;
			break;

		}

	}


}
void MegaCalc::parse()
{	//Reads user input and parses it to extract operation and operand. 

	//For Unary commands
	if (rawcommand.size() == 1)
	{
		//caps to small
		std::transform(rawcommand.begin(), rawcommand.end(), rawcommand.begin(), ::tolower);
		
		this->operation = *rawcommand.c_str();
		
	}
	else //Regex filter For Binary commands
	{	//("([-|+|*|/|%|=])((\\+|-)?)([[:d:]]+)")
		
		std::regex e("([-|+|*|/|%|=])([+-]?)([[:d:]]+)");
	
		std::cmatch match;

		std::regex_match(this->rawcommand.c_str(), match, e);
		
		this->operation = match.str(1)[0];
		cout << endl;
		for (auto x:match){
			//print parsed input
		std::cout << "[" << x << "]" ;
		}cout << endl<< endl;
		//Catch invalid input
		if (match.str(1).empty()){ cout << "Invalid Input. Please try again" << endl << endl;
		return;
		}char* endptr = NULL;
		//Set operand sign and value
		if ((match.str(2).empty()) | (match.str(2)[0] == '+'))
		{
			
			this->operand.setsign("+");
			//this->operand.setacc(std::strtoll(match.str(3)));
			this->operand.toDeque(match.str(3));
			cout << "operand = " << operand<<endl;
			cout << endl;
		}
		else
		{
			this->operand.setsign("-");
			//this->operand.setacc(std::stoi(match.str(3)));
			this->operand.toDeque(match.str(3));
			cout << "operand = " << operand << endl;
			cout << endl;
		}
	
	}
}
void MegaCalc::factorial()
{

	if (this->accumulator.getsign() == '-')
	{
		cout<<"Cannot compute factorial, accumulator is less than 0" << endl;
	} 
	else
	{	//crawl starts from 1 and enables computing each factorial upto the accumulator
		MegaInt fact(1, "+");
		MegaInt crawl(1,"+");
	
		while(crawl <= accumulator)
		{
			fact *crawl;
			++crawl;
			cout<<"factorial: "<< fact<<endl;
		}
		accumulator = fact;
	
	}
}
MegaInt MegaCalc::hailstone()
{
	if (this->accumulator.getsign() == '-')
	{
		std::cout << " Can't perform the hailstone sequence on a negative value" << endl << endl;
		return accumulator;
	}
	else
	{
		MegaInt zero(0, "+");
		MegaInt one(1, "+");
		MegaInt two(2, "+");
		MegaInt three(3, "+");
		int count = 0;
		MegaInt test = accumulator;
		while (test > one)
		{

			int end = (int)accumulator.getacc()[accumulator.getacc().size() - 1]-'0';
			//cout << "end" << end ;
			if (end % 2 > 0)
			//if	(test % two > zero)
			{
				accumulator * three ;

				accumulator + one;
				//cout << "acc*3-1 " << accumulator << endl;
				

			}
			else
			{
				accumulator / two;
				//cout << "acc/2 " << accumulator << endl;
			}
			count++;
			std::cout << accumulator << " ";
			test = accumulator;
		}
		cout << endl << endl;
		this->accumulator.setacc(count);
		return accumulator;
	}
}
void MegaCalc::welcome()
{
	cout << R"( 
    _           _  _  _  _  _  _    _  _  _           _                      
   (_) _     _ (_)(_)(_)(_)(_)(_)_ (_)(_)(_) _      _(_)_                    
   (_)(_)   (_)(_)(_)           (_)         (_)   _(_) (_)_                  
   (_) (_)_(_) (_)(_) _  _      (_)    _  _  _  _(_)     (_)_                
   (_)   (_)   (_)(_)(_)(_)     (_)   (_)(_)(_)(_) _  _  _ (_)               
   (_)         (_)(_)           (_)         (_)(_)(_)(_)(_)(_)               
   (_)         (_)(_) _  _  _  _(_) _  _  _ (_)(_)         (_)               
   (_)         (_)(_)(_)(_)(_)(_)  (_)(_)(_)(_)(_)         (_)               
                                                                             
                                                                             
       _  _  _           _        _                _  _  _                   
    _ (_)(_)(_) _      _(_)_     (_)            _ (_)(_)(_) _                
   (_)         (_)   _(_) (_)_   (_)           (_)         (_)               
   (_)             _(_)     (_)_ (_)           (_)                           
   (_)            (_) _  _  _ (_)(_)           (_)                           
   (_)          _ (_)(_)(_)(_)(_)(_)           (_)          _                
   (_) _  _  _ (_)(_)         (_)(_) _  _  _  _(_) _  _  _ (_)               
      (_)(_)(_)   (_)         (_)(_)(_)(_)(_)(_)  (_)(_)(_)                  
                                                                             
                                                                                            
                                                                                                                                        

)" << endl <<endl;
}
void MegaCalc::quit()
{
	this->mode = "off";

	cout << R"(

    _  _  _  _    _           _  _  _  _  _  _    
   (_)(_)(_)(_) _(_)_       _(_)(_)(_)(_)(_)(_)   
    (_)        (_) (_)_   _(_)  (_)               
    (_) _  _  _(_)   (_)_(_)    (_) _  _          
    (_)(_)(_)(_)_      (_)      (_)(_)(_)         
    (_)        (_)     (_)      (_)               
    (_)_  _  _ (_)     (_)      (_) _  _  _  _    
   (_)(_)(_)(_)        (_)      (_)(_)(_)(_)(_)   
                                                  
                                                  


)" << endl;
}
void MegaCalc::help()
{
	cout << "		WELCOME TO THE CALCULATOR HELP MENU" << endl << endl;

	cout << "		HERE ARE THE COMMAND EXAMPLES" << endl << endl;

	cout << "A sign may be included with new operand or ommited for a default positive" << endl << endl;

	cout << "Binary commands must include the operation and operand" << endl << endl;
	
	cout << "Command example binary operation:	+1" << endl;

	cout << "Command example signed binary operation: *-1	" << endl;

	cout << "Command example binary operation: %1 " << endl;

	cout << "Command example unary operation:  f" << endl << endl;

	cout << "		HERE ARE THE COMMAND OPTIONS" << endl << endl;

	cout << "+i - accumulator = accumulator + i (i is assumed positive)" << endl << endl;

	cout << "++i - accumulator = accumulator + i (i is read as positive) " << endl << endl;

	cout << "+-i - accumulator = accumulator + i (i is read a negative)" << endl << endl;

	cout << "-i - accumulator = accumulator - i ( i is assumed positive)" << endl << endl;
	
	cout << "-+i - accumulator = accumulator - i (i is read as positive)" << endl << endl;

	cout << "--i - accumulator = accumulator - i (i is read a negative)" << endl << endl;
	
	cout << "*i - accumulator = accumulator * i (i is assumed positive)" << endl << endl;
	
	cout << "*+i - accumulator = accumulator * i (i is read as positive) " << endl << endl;

	cout << "*-i - accumulator = accumulator * i (i is read a negative)" << endl << endl;
	
	cout << "/i - accumulator = accumulator / i (i is assumed positive)" << endl << endl;

	cout << "/+i - accumulator = accumulator / i (i is read as positive) " << endl << endl;

	cout << "/-i - accumulator = accumulator  i (i is read a negative)" << endl << endl;

	cout << "%i - accumulator = accumulator % i (i is assumed positive)" << endl << endl;

	cout << "%+i - accumulator = accumulator % i (i is read as positive) " << endl << endl;

	cout << "%-i - accumulator = accumulator % i (i is read a negative)" << endl << endl;

	cout << "c - clear the accumulator " << endl << endl;

	cout << "n - negates the accumulator " << endl << endl;

	cout << "f - accumulator = accumulator!  "<< endl << endl;
	
	cout << "h - Prints hailstone sequence, accumulator = size of series" << endl << endl;

	cout << "Enter - repeats previous operation." << endl << endl;
	
	cout << "q - Exits MegaCalc" << endl << endl;

	cout << "a - The trusted help menu, you can return here as many times as you like!!" << endl << endl;

	cout << "m - Clears the screen" << endl << endl;

	cout << "p - print the accumulator" << endl << endl;
}
//e_command: erase/clear the screen
void MegaCalc::clear()
{
	cout << string(100, '\n');
}