#ifndef MEGAINT_H
#define MEGAINT_H
#include <iostream>
#include <deque>
using std::ostream;

class MegaInt
{
public:
	//constructors
	MegaInt( char*);
	MegaInt(int, char*);
	MegaInt convert(int, char*);
	MegaInt();
	~MegaInt();
	

	//Operator overloads
	MegaInt operator +(MegaInt mi);
	MegaInt operator -(MegaInt mi);
	MegaInt operator = (MegaInt mi);
	MegaInt operator ++();
	MegaInt operator --();
	bool operator <=(MegaInt mi);
	MegaInt operator *=(MegaInt mi);
	MegaInt operator /=(MegaInt);
	MegaInt operator +=(MegaInt mi);
	MegaInt operator -=(MegaInt mi);
	MegaInt operator *(MegaInt);
	MegaInt operator /(MegaInt);
	MegaInt operator %(MegaInt);
	MegaInt operator %=(MegaInt);
	bool operator==(MegaInt mi);
	bool operator <(MegaInt mi);
	bool operator!=(MegaInt mi);
	bool operator>(MegaInt mi);
	bool operator>=(MegaInt mi);
	char operator [](int);
	friend ostream& operator<<(ostream& output, MegaInt& mi);

	//Getters and setters
	const std::deque<char> getacc();
	void setacc(long long int);
	const char getsign();
	void setsign(char*);
	void clear();
	void negate();
	void toDeque(std::string);
	
	private:
	//Variables
	std::deque < char > acc;
	char* sign{ nullptr };

	
	//Arithmetic operations
	MegaInt add(MegaInt mi);
	MegaInt subtract(MegaInt mi);
	MegaInt multiply(MegaInt mi);
	MegaInt divide(MegaInt mi);
	void product(MegaInt);
	void div(MegaInt);		
	void mod(MegaInt);
	std::deque<char> plus(const std::deque<char>, const std::deque<char>);
	std::deque<char> minus(const std::deque<char>, const std::deque<char>);

	//alterations	
	void swap(MegaInt x, MegaInt y);
	const std::string toString();
	
	void popzeros();
	int toInt();
	
	
};




#endif // !MEGAINT_H