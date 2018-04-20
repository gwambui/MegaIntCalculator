#include "MegaInt.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
using std::ostream;


//Constructors: initialized with a char pointer
MegaInt::MegaInt(char* megaint)
{
	std::deque<char> copychar(megaint , megaint + sizeof(megaint) /sizeof(char) );
	cout << megaint << endl;
}
//Empty constructor
MegaInt::MegaInt()
{
	this->acc = std::deque<char>();
	this->sign = "+";
}

//constructor initialized from integer
MegaInt::MegaInt(int a, char* sg)
{
	string n = to_string(a);
	for (int i = 0; i<n.size(); ++i)
	{
		string s = n.substr(i);
		
		const char* x = s.c_str();
		
		
		acc.push_back(x[0]);
		//delete []x;
	}
	this->sign= sg;
}
MegaInt MegaInt::convert(int t, char* sg)
{
	std::deque<char> temp;
	string a = to_string(t);
	for (int i = 0; i<a.size(); ++i)
	{
		string s = a.substr(i);

		const char* x = s.c_str();
		temp.push_back(x[0]);
	}
	this->acc=temp;
	return *this;
}

//Destructor
MegaInt::~MegaInt()
{
	acc.clear();
	
}

//Operator Overloads
MegaInt MegaInt::operator+(MegaInt mi)
{
	//this->acc = plus(acc, mi.acc);
	this->add(mi);
	return *this ;
}
MegaInt MegaInt::operator+=(MegaInt mi)
{
	*this = *this + mi;
	return *this;
}
MegaInt MegaInt::operator-=(MegaInt mi)
{
	*this = *this - mi;
	return *this;
}
MegaInt MegaInt::operator-(MegaInt mi)
{
	
	//this->acc = minus(acc, mi.acc);
	this->subtract(mi);
	return *this;
}
 
MegaInt MegaInt::operator=(MegaInt mi)
{
	if (this->acc == mi.acc)
	{
		return *this;
	}
	else
	{
		this->acc = mi.acc;
		this->sign = mi.sign;
		return *this;
	}
}

MegaInt MegaInt::operator++()
{	
	MegaInt zero(0, "+");
	std::deque<char> temp;
	temp.push_back('1');
	if (*this == zero){
		this->sign = "+";
		this->acc.clear();
		this->acc.push_back('1');
		return *this;
	}
	if (this->sign == "-"){ this->acc =minus(acc, temp); }
	else{ this->acc = plus(acc, temp); }
	
	return *this;

	
}

MegaInt MegaInt::operator--()
{
	MegaInt zero(0, "+");
	std::deque<char> temp;
	temp.push_back('1');
	if (*this == zero){
		this->sign = "-";
		this->acc.clear();
		this->acc.push_back('1');
		return *this;
	}
	if (this->sign == "-"){this->acc = plus(acc, temp);}
	else{ this->acc = minus(acc, temp); }
	return *this;
	
}


bool MegaInt::operator<=(MegaInt mi)
{
	return *this < mi || *this == mi;
	/*bool less = false ;
	if (this->acc.size() < mi.acc.size())
	{
		less = true;
		return less;
		
	}
	else if (this->acc.size() > mi.acc.size())
	{
		return less;
	}
	else
	{
		for (int i = 0; i < mi.acc.size() ; ++i)
		{
			if (((int)acc.at(i) - '0') < ((int)mi.acc.at(i) - '0'))
			{
				less = true;
				cout << less << endl;
				return less;
			}
			else if (((int)acc.at(i) - '0') == ((int)mi.acc.at(i) - '0'))
			{
				less = true;
				cout << i << ' ' << less << mi.acc.size()<< endl;
			}
			else{
				less = false;
				

			}
			
		}
		return less;
	}*/

}
bool MegaInt::operator>=(MegaInt mi)
{
	return *this > mi || *this == mi;
}
MegaInt MegaInt::operator*=(MegaInt mi)
{
	*this = *this * mi;
	return *this;
	
}
MegaInt MegaInt::operator *(MegaInt mi)
{
	this->multiply(mi);
	return *this;

	
}

MegaInt MegaInt::operator /=(MegaInt n)
{
	*this = *this / n;
	return *this;

}
MegaInt MegaInt::operator /(MegaInt mi)
{

	this->divide(mi);
	return *this;
}

MegaInt MegaInt::operator %(MegaInt mi)
{
	this->mod(mi);
	return *this;
	/*
	while (*this >= mi)
	{
		this->acc = minus(this->acc, mi.acc);

	}
*/

	

	
}

MegaInt MegaInt::operator %=(MegaInt mi)
{
	 *this = *this % mi;
	return *this;
}

bool MegaInt::operator==(MegaInt mi)
{
	bool equal = false;
	if (this->acc.size() == mi.acc.size())
	{

		for (int i = 0; i < mi.acc.size(); ++i)
		{
			if (((int)acc.at(i) - '0') != ((int)mi.acc.at(i) - '0'))
			{
				equal = false;
				return equal;
			}
			else if (((int)acc.at(i) - '0') == ((int)mi.acc.at(i) - '0'))
			{
				equal = true;
			}
			else{
				equal = false;
				

			}

		}
		

		equal = true;
		//cout << less << endl;
		return equal;
	
		}
	else  
	{
		return equal;
	}

	
		
	
}

bool MegaInt::operator!=(MegaInt mi)
{
	return *this < mi || *this > mi;
}
bool MegaInt::operator >(MegaInt mi)
{
	bool greater = false;
	if (this->acc.size() > mi.acc.size())
	{
		greater = true;
		return greater;
	}
	else if (this->acc.size() < mi.acc.size())
	{
		return greater;
	}
	else
	{
		for (int i = 0; i < mi.acc.size(); ++i)
		{
			if (((int)this->acc.at(i) - '0') > ((int)mi.acc.at(i) - '0'))
			{
				greater = true;
				return greater;
			}
			else if (((int)this->acc.at(i) - '0') < ((int)mi.acc.at(i) - '0')){
				greater = false;
				return greater;
			}
			else{
				greater = false;
			}
		}
	}
	return greater;
}

bool MegaInt::operator <(MegaInt mi)
{
	bool less = false;
	if (this->acc.size() < mi.acc.size())
	{
		less = true;
		return less;

	}
	else if (this->acc.size() > mi.acc.size())
	{
		return less;
	}
	else
	{
		for (int i = 0; i < mi.acc.size(); ++i)
		{
			if (((int)this->acc.at(i) - '0') < ((int)mi.acc.at(i) - '0'))
			{
				less = true;
				return less;
			}
			else if (((int)this->acc.at(i) - '0') > ((int)mi.acc.at(i) - '0')){
				less = false;
				return less;
			}
			else{
				less = false;
			}
			

		}
	}
		return less;
}
char MegaInt::operator[](int n)
{
	if (n >= 0 && n < acc.size())
	{
		return this->acc.at(n);
	}
	else{
		cout << n << " is out of range size of accumulator is " << acc.size();
		return NULL;
	}

}
ostream& operator<<(ostream& output, MegaInt& mi)
{
	
	output << mi.toString();
	return output;
}

//Arithmetic operations
//Add
MegaInt MegaInt::add(MegaInt mi)
{
	
	if (this->sign == mi.sign)
	{
		this->acc = plus(this->acc, mi.acc);
	}
	else if (*this > mi)
	{
		//result.sign = this->sign;
		this->acc = minus(this->acc, mi.acc);
	}
	else if (*this < mi)
	{
		this->sign = mi.sign;
		this->acc = minus(mi.acc, this->acc);
	}
	else
	{
		
		this->sign = "+";
		this->acc.clear();
		this->acc.push_back('0');
	}
	return *this;
}
//Subtract
MegaInt MegaInt::subtract(MegaInt mi)
{
	if (this->sign != mi.sign)
	{	
		this->acc = plus(this->acc, mi.acc);
	}
	else if (*this > mi)
	{

		this->acc = minus(this->acc, mi.acc);
	}
	else if (*this < mi)
	{
		this->sign = "-";
		this->acc = minus(mi.acc, this->acc);
	}
	else
	{
		this->sign = "+";
		this->acc.clear();
		this->acc.push_back('0');
	}
	return *this;


}
//Multiply
MegaInt MegaInt::multiply(MegaInt mi)
{
	if (this->sign != mi.sign)
	{
		this->product(mi);
		this->setsign("-"); 
	}
	else
	{
		this->product(mi);
		this->setsign("+");
	}

	return *this;
	
}
//Divide
MegaInt MegaInt::divide(MegaInt mi)
{
	
	if (this->sign != mi.sign)
	{
		this->sign = "+";
		mi.sign = "+";
		this->div(mi);
		this->sign = "-";
	}
	else
	{
		this->sign = "+";
		mi.sign = "+";
		this->div(mi);
	}
	return *this;
	/*int count = 0;
	while (*this >= mi)
	{
		this->acc = minus(this->acc, mi.acc);
		count++;
	}
	this->setacc(count);*/
}
//Plus
deque<char> MegaInt::plus(deque<char> x, deque<char> y)
{
	std::deque<char> z;
	 long int m = x.size()  ;
	 long int n = y.size() ;
	 long int p = max(m, n) + 1;
	 int carry = 0;
	 int i = p - 1;
	 int j = m - 1;
	 int k = n - 1;
	 int sum;
	 int q;
	 
	
	 
	 while (j >= 0 && k >= 0)
	 {
		sum = ((int)x.at(j) - '0') + ((int)y.at(k) - '0')+ carry;
		q = (sum % 10);
		
		 j--;
		 k--;
		 z.push_front(static_cast<char>(q + '0'));
		 carry = (sum - (sum % 10)) / 10;
		// cout << carry << " carry  " << sum << " sum " << endl << endl;
		 sum = 0;
		
	 }
	
	 // for unprocessed portion of x.. add the carry
	 while (j>=0)
	 {
		 sum = static_cast<int>(x.at(j) - '0') + carry;
		 --j;
		 z.push_front(static_cast<char>(sum % 10) + '0');
		 carry = (sum - (sum % 10)) / 10;
	 }
	
	 while (k >= 0)
	 {	   
	 sum = static_cast<int>(y.at(k) - '0') + carry;
		 --k;
		 z.push_front(static_cast<char>(sum % 10) + '0');
		 carry = (sum - (sum % 10)) / 10;
	 }
	 if (carry>0)z.push_front(static_cast<char>(carry + '0'));
	  this->acc = z;
	  this->popzeros();
	  return this->acc;
	 
	 /*
	 for (char n : z)
	 {
		 std::cout << n << ' ';

	 }
	
	 std::deque<char>::iterator it = z.begin();

	 while (it != z.end())
		 std::cout << ' ' << *it++;*/
	 
}

//Minus
deque<char> MegaInt::minus(std::deque<char> x, std::deque<char> y)
{
	/*std::string msg =  "x cannot be greater than y in x-y";
	try{
	if(y.size() > x.size())
	{throw msg; }*/



	int m = x.size();
	int n = y.size();
	std::deque<char> z;
	int p = max(m, n) + 1;
	int borrow = 0;
	int i = p - 1;
	int j = m - 1;
	int k = n - 1;
	int diff;
	int q;

	while (j >= 0 && k >= 0)
	{
		diff = (((int)x.at(j) - '0') - ((int)y.at(k) - '0') - borrow);
		//cout << ' ' << x.at(j)<<' ' << y.at(k) << ' ';
		if (diff < 0)
		{
			borrow = 1;
			diff = diff + 10;
		}
		else { borrow = 0; }
		z.push_front(static_cast<char>(diff + '0'));

		--j;
		--k;

		//std::cout << borrow << " borrow  " << endl << endl;


	}

	// for unprocessed portion of x.. propagate last borrow
	while (j >= 0)
	{
		diff = (static_cast<int>(x.at(j) - '0') - borrow);
		if (diff < 0)
		{
			borrow = 1;
			diff = diff + 10;
		}
		else{
			borrow = 0;
		}
		--j;
		z.push_front(static_cast<char>(diff)+'0');

	}
	this->acc = z;
	this->popzeros();
	return this->acc;

/*}
	catch (std:: string e){

		cout << e << endl;
	  return x;
	}*/
	
}

void MegaInt::product(MegaInt a)
{

	MegaInt partialsum; 
	MegaInt temp;

	int m = this->acc.size();
	int n = a.acc.size();
	
	if (n > m){ swap(*this, a); }
	m = this->acc.size();
	n = a.acc.size();
	int k = n - 1;
	
	int offset = k;
	int carry = 0;
	int holder = 0;
	int q;

	while (k >= 0)
	{	int j = m - 1;
		temp.acc.clear();
		carry = 0;
		while (j >= 0)
		{
			holder = (((int)this->acc.at(j) - '0') * ((int)a.acc.at(k) - '0')) + carry;
			
			q = (holder % 10);
				 
		 	temp.acc.push_front(static_cast<char>(q + '0'));
			carry = (holder - q) / 10;
			
			j--;
			
		}
		if(carry > 0) temp.acc.push_front(static_cast<char>(carry + '0')); 
		
		for (int i = 0; i < offset - k; i++)
		{	
			temp.acc.push_back('0');
		}
	
		partialsum = partialsum + temp;
		
		--k;
	
	}
	*this = partialsum;

}
void MegaInt::div(MegaInt a)
{
	if (a.acc.size() > this->acc.size()){
		this->clear();
		return;
	}
	MegaInt temp;
	MegaInt result;
	int j = a.acc.size();
	for (int i = 0; i < j; ++i)
	{
		temp.acc.push_back(this->acc[i]);
	}	
	int b = 0;
	while (j <= this->acc.size())
	{
		//removes leading zeros from the divisor. othersise messes up with >= operation
		temp.popzeros();
		while (temp >= a)
		{	
			temp - a;
			++b;
		}
		
		result.acc.push_back(static_cast<char>(b + '0'));

		if (j < this->acc.size()){
			temp.acc.push_back(this->acc[j]);
		}
		b = 0;
		j++;	
	}
	
	result.popzeros();
	*this = result;
	/*while (j <= this->acc.size())
	{

		int b = temp.toInt() / a.toInt();
		temp = temp % a;
		result.acc.push_back(static_cast<char>(b + '0'));
		if (j < this->acc.size()){
			temp.acc.push_back(this->acc[j]);
		}

		j++;
	}

	*/
}
void MegaInt::mod(MegaInt a)
{
	MegaInt temp;
	
	int j = a.acc.size();
	
	for (int i = 0; i < j; ++i)
	{
		temp.acc.push_back(this->acc[i]);
		
	}
	//cout << "temp " << temp<<endl;
	while (j <= this->acc.size())
	{

		//int b = temp.toInt() / a.toInt();
		while (temp >= a)
		{
			temp -a;
		}
		//temp.setacc( temp.toInt() - a.toInt()*b);
		
		if (j<this->acc.size()){
			temp.acc.push_back(this->acc[j]);
		}
		j++;
	}

	temp.popzeros();
	*this = temp;
}

const string MegaInt::toString()
{
	string print;
	print = this->sign;
	for (char n : this->getacc())
	{
		print = print + n + ' ';

	}
	return print;
}
void MegaInt::popzeros()
{
	while (this->acc.at(0) == '0' && this->acc.size() > 1)
	{
		this->acc.pop_front();
	}
}
void MegaInt::swap(MegaInt x, MegaInt y)
{
	MegaInt temp ;
	temp = x;
	x = y;
	y = temp;
	return;
}
const deque<char> MegaInt::getacc()
{
	return this->acc;
}
const char MegaInt::getsign()
{
	return *this->sign;
}
void MegaInt::setsign(char* c)
{
	this->sign = c;
}
void MegaInt::setacc(long long int a)
{
	this->acc.clear();
	string n = to_string(a);
	cout << n << endl;
	for (int i = 0; i<n.size(); ++i)
	{
		string s = n.substr(i);

		const char* x = s.c_str();

		this->acc.push_back(x[0]);

	}
		
}
void MegaInt::clear()
{
	this->acc.clear();
	this->acc.push_back('0');
	return;
}
void MegaInt::negate()
{
	if (this->sign == "+")
	{
		this->sign = "-";
	}
	else{
		this->sign = "+";
	}
	return;
}
//I ended up avoiding this toInt method because large numbers 
//have unpredictable behaviour even if long long int is used
int MegaInt::toInt()
{
	int num=0;
	int m = 0;
	int n = this->acc.size()-1;
	while (n >= 0)
	{
		num += ((int)this->acc.at(n) - '0') * pow(10,m);
		++m;
		--n;
	}
	
	return num;
}
//toDeque accepting string input  setacc accepts ints
void MegaInt::toDeque(string s)
{
	this->acc.clear();
	for (int i = 0; i < s.size(); ++i)
	{
		string a  = s.substr(i);

		const char* x = a.c_str();
		this->acc.push_back(x[0]);
	}
	this->acc;
}