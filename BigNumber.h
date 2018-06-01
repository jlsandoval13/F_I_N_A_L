#pragma once
#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <vector>
#include <iostream>
using namespace std;

class BigNumber {
private:
	vector<int> numbers;      /*vector of digits each saving one num*/
	int size;
public:
	BigNumber();
	BigNumber(long number, int l); 	  /*Passes in a long value and creates a BigNumber*/
	BigNumber(const BigNumber& bn);	  /*Copy constructor for BigNumber that saves the values into the newly constructed one*/
	BigNumber(vector<int> nums, int digits);  /* stores the number of digits in the BigNumber*/

	bool operator > (BigNumber const &number);	  /*returns true if this > num*/
	bool operator < (BigNumber const &number);	  /*returns true if this < num*/
	bool operator == (BigNumber const &number);	  /*returns true if this == num*/
	bool operator >= (BigNumber const &number);	  /*returns true if this >= num*/
	bool operator <= (BigNumber const &number);	  /*returns true if this <= num*/
	BigNumber operator = (BigNumber const &number);
	BigNumber operator + (BigNumber const &number);	  /*overloaded unary operator for basic addition*/
	BigNumber operator - (BigNumber const &number);	  /*overloaded unary operator for basic subtraction. does not support negative numbers, returns 0 instead*/
	BigNumber operator * (BigNumber const &number);	  /*overloaded unary operator for basic multiplication*/
	BigNumber operator / (BigNumber const &number);	  /*overloaded unary operator for basic division. generates and prints a division by zero error if the denominator num = 0. will return 0 if num>*this*/
	BigNumber operator % (BigNumber const &number);	  /*overloaded unary operator for basic modulus function*/

	/*loops through numbers backwards, prints digits in correct order*/
	/*access the element of numbers[i] from outside the original BigNumber object*/
	/*returns this->numbers*/
	/*returns this->size*/
	/*returns the most significant (nonzero) digit*/
	/*sets the digit at numbers[index] to the int value*/
	/*sets numbers to the new vector<int> newval*/
	/*sets this->size to int newsize*/
	void print();
	int find(int i) const;
	vector<int> digits() const;
	int getLength() const;
	int sigDigit();
	bool set(int value, int index);
	void setVector(vector<int> newval);
	void setLength(int newLength);
};

#endif
