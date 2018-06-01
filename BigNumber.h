#pragma once
#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <vector>
#include <iostream>
using namespace std;

class BigNumber {
private:
	vector<int> numbers;
	int size;
public:
	BigNumber();
	BigNumber(long number, int l);
	BigNumber(const BigNumber& bn);
	BigNumber(vector<int> nums, int digits);

	bool operator > (BigNumber const &number);
	bool operator < (BigNumber const &number);
	bool operator == (BigNumber const &number);
	bool operator >= (BigNumber const &number);
	bool operator <= (BigNumber const &number);
	BigNumber operator = (BigNumber const &number);
	BigNumber operator + (BigNumber const &number);
	BigNumber operator - (BigNumber const &number);
	BigNumber operator * (BigNumber const &number);
	BigNumber operator / (BigNumber const &number);
	BigNumber operator % (BigNumber const &number);

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
