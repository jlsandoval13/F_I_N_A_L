#include "BigNumber.h"

BigNumber::BigNumber()
{
	numbers[0] = 0;
	size = 0;
}

BigNumber::BigNumber(long number, int l)
{
	numbers.resize(l);
	for (int i = 0; i < l; i++)
	{
		numbers[i] = number % 10;
		number /= 10;
	}
	size = l;
}

BigNumber::BigNumber(const BigNumber& bn)
{
	this-> numbers = bn.digits();
	this-> size = bn.getLength();
}

BigNumber::BigNumber(vector<int> nums, int digits)
{
	numbers.clear();
	for (int i = 0; i<digits; i++)
	{
		numbers.push_back(nums[i]);
	}
	size = digits;
}

bool BigNumber::operator > (BigNumber const &number)
{
	if (size < number.getLength())
		return false;
	else if (size > number.getLength())
		return true;
	else
	{
		for (int i = size - 1; i >= 0; i--)
		{
			if (number.find(i)>numbers[i])
				return false;
			else if (number.find(i)<numbers[i])
				return true;
		}
	}
	return false;
}

bool BigNumber::operator < (BigNumber const &number)
{
	if (size>number.getLength())
		return false;
	else if (size<number.getLength())
		return true;
	else
	{
		for (int i = size - 1; i >= 0; i--)
		{
			if (number.find(i)<numbers[i])
				return false;
			else if (number.find(i)>numbers[i])
				return true;
		}
	}
	return false;
}

bool BigNumber::operator == (BigNumber const &number)
{
	if (!(size == number.getLength()))
		return false;
	else
	{
		for (int i = 0; i<size; i++)
			if (number.find(i) != numbers[i])
				return false;
	}
	return true;
}

bool BigNumber::operator >= (BigNumber const &number)
{
	return *this > number || *this == number;
}

bool BigNumber::operator <= (BigNumber const &number)
{
	return *this < number || *this == number;
}

BigNumber BigNumber::operator = (BigNumber const &number)
{
	numbers.clear();
	for (int i = 0; i<number.getLength(); i++)
	{
		numbers.push_back(number.find(i));
	}
	size = number.getLength();
	return *this;
}

BigNumber BigNumber::operator + (BigNumber const &number)
{
	vector<int> added, smallcpy = number.digits(), bigcpy = numbers;
	int carry = 0;

	if ((*this)<number)
	{
		bigcpy.swap(smallcpy);
	}

	for (int i = 0; i<bigcpy.size() - smallcpy.size() + 1; i++)
	{
		smallcpy.push_back(0);
	}

	for (int i = 0; i<bigcpy.size(); i++)
	{
		int val = bigcpy[i] + smallcpy[i] + carry;
		added.push_back(val % 10);
		if (val >= 10)
			carry = val / 10;
		else
			carry = 0;
	}
	while (carry>0)
	{
		added.push_back(carry % 10);
		carry /= 10;
	}
	BigNumber a(added, added.size());
	return a;
}

BigNumber BigNumber::operator - (BigNumber const &number)
{
	vector<int> large = numbers, small = number.digits();
	int biggerSize = size, smallerSize = number.getLength();

	if (numbers == number.digits() || biggerSize < smallerSize)
	{
		return BigNumber(0, 1);
	}
	while (biggerSize>smallerSize)
	{
		small.push_back(0);
		smallerSize++;
	}

	int borrow = 0, val;
	for (int i = 0; i < biggerSize; i++)
	{
		val = large[i] - borrow - (i >= smallerSize ? 0 : small[i]);
		borrow = 0;
		if (val < 0)
		{
			val += 10;
			borrow = 1;
		}
		large[i] = val;
	}
	while (large[biggerSize - 1] == 0)
	{
		large.pop_back();
		biggerSize--;
	}
	BigNumber s(large, large.size());
	return s;
}

BigNumber BigNumber::operator * (BigNumber const &number)
{
	vector<int> big = numbers, small = number.digits();
	int bigsz = big.size(), smallsz = small.size();
	vector<int> product(bigsz + smallsz);
	if (bigsz<smallsz)
	{
		big.swap(small);
		bigsz = big.size(), smallsz = small.size();
	}

	for (int i = 0; i<bigsz; i++)
	{
		int carry = 0;
		for (int j = 0; j<smallsz; j++)
		{
			product[i + j] += carry + small[j] * big[i];
			carry = product[i + j] / 10;
			product[i + j] = product[i + j] % 10;
		}
		product[i + bigsz] += carry;
	}
	if (product[product.size() - 1] == 0)
	{
		product.pop_back();
	}
	BigNumber p(product, product.size());
	return p;
}

BigNumber BigNumber::operator / (BigNumber const &number)
{
	try
	{
		vector<int> numer = numbers, denom = number.digits();
		BigNumber nb(numer, numer.size()), db(denom, denom.size());

		if (number.getLength() <= 1 && number.find(0) == 0)
			throw 1;
		else if (*this == number)
			return BigNumber(1, 1);
		else if (size<number.getLength())
		{
			return BigNumber(0, 1);
		}
		else if (nb<db)
		{
			return BigNumber(0, 1);
		}
		while (nb.getLength()<denom.size())
		{
			numer.push_back(0);
			nb.setVector(numer);
		}

		BigNumber *n = &nb;
		BigNumber q(0, 1);
		BigNumber one(1, 1);
		while ((*n) >= db)
		{
			*n = ((*n) - db);
			q = q + one;
		}
		return q;
	}
	catch (int i)
	{
		cout << "Error: division by 0" << endl;
	}
	return BigNumber(0, 0);
}

BigNumber BigNumber::operator % (BigNumber const &number)
{
	if (*this<number)
		return BigNumber(0, 1);
	BigNumber divd = (*this / number);
	BigNumber rem = divd * number;
	return *this - rem;
}

void BigNumber::print()
{
	for (int i = size - 1; i >= 0; i--)
	{
		cout << numbers[i];
	}
	cout << endl;
}

int BigNumber::find(int i) const
{
	return numbers[i];
}

vector<int> BigNumber::digits() const
{
	return numbers;
}

int BigNumber::getLength() const
{
	return size;
}

int BigNumber::sigDigit()
{
	for (int i = size - 1; i >= 0; i--)
		if (numbers[i] > 0)
			return i;
	return 0;
}

bool BigNumber::set(int value, int index)
{
	int sig = this->sigDigit();
	if (value < 10 && value >= 0 && index >= 0 && index <= sig)
	{
		numbers[index] = value;
		return true;
	}
	return false;
}

void BigNumber::setVector(vector<int> newval)
{
	this->numbers = newval;
	this->size = newval.size();
}

void BigNumber::setLength(int newsize)
{
	this->size = newsize;
}
