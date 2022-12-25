#include "BigInt.h"


//сравнение двух чисел по модулю
int compareByAbs(const BigInt& a, const BigInt& b)
{
	if (a.size > b.size)
		return +1;
	if (a.size < b.size)
		return -1;

	for (size_t i = a.size - 1; i != std::string::npos; --i)
	{
		if (a.digits[i] > b.digits[i])
			return +1;
		if (a.digits[i] < b.digits[i])
			return -1;
	}

	return 0;
}

//сложение двух чисел по модулю
BigInt additionByAbs(const BigInt& a, const BigInt& b)
{
	const BigInt& min = (a.size < b.size) ? a : b;
	const BigInt& max = (a.size >= b.size) ? a : b;

	BigInt c(max.size + 1);

	int extraTen = 0;

	for (size_t i = 0; i < min.size; i++)
	{
		int sum = min.digits[i] + max.digits[i];
		sum += extraTen;
		c.digits[i] = sum % 10;
		extraTen = sum / 10;
	}

	for (size_t i = min.size; i < max.size; i++)
	{
		int sum = max.digits[i];
		sum += extraTen;
		c.digits[i] = sum % 10;
		extraTen = sum / 10;
	}

	c.digits[c.size - 1] = extraTen;
	c.remove_insignificant_zeros();

	return c;
}

//вычитание двух чисел по модулю
BigInt subtractionByAbs(const BigInt& a, const BigInt& b)
{
	const BigInt& max = a;
	const BigInt& min = b;

	BigInt c(max.size);

	int creditTen = 0;

	for (size_t i = 0; i < min.size; ++i)
	{
		int diff = max.digits[i] - min.digits[i] - creditTen;
		creditTen = 0;

		if (diff < 0)
		{
			diff += 10;
			creditTen = 1;
		}

		c.digits[i] = diff;
	}

	for (size_t i = min.size; i < max.size; ++i)
	{
		int diff = max.digits[i] - creditTen;
		creditTen = 0;

		if (diff < 0)
		{
			diff += 10;
			creditTen = 1;
		}

		c.digits[i] = diff;
	}

	c.remove_insignificant_zeros();

	return c;
}

//произведение числа на цифру по модулю
BigInt multByAbs(const BigInt& number, char digit)
{
	if (digit == 0)
		return BigInt(); //0

	BigInt c(number.size + 1);

	int extraTens = 0;

	for (size_t i = 0; i < number.size; ++i)
	{
		int multOfDigits = number.digits[i] * digit + extraTens;

		c.digits[i] = multOfDigits % 10;
		extraTens = multOfDigits / 10;
	}

	c.digits[c.size - 1] = extraTens;

	c.remove_insignificant_zeros();

	return c;
}

//произведение двух чисел по модулю
BigInt multByAbs(const BigInt& a, const BigInt& b)
{
	if (a.isNull() || b.isNull())
		return BigInt(); //0

	BigInt c(a.size + b.size);

	for (size_t i = 0; i < b.size; ++i) //перебор цифр второго числа
	{
		int digit = b.digits[i];

		if (digit != 0)
		{
			BigInt term = multByAbs(a, digit); //умножаем цифру на первое число

			term.add_nulls(i); //сдвигаем результат на соответствующий разряд

			c = additionByAbs(c, term);
		}
	}

	return c;
}



//удаление незначащих нулей
void BigInt::remove_insignificant_zeros()
{
	size_t n = 0;
	for (size_t i = size - 1; i > 0 && digits[i] == 0; --i)
		++n;

	if (n == 0)
		return;

	size_t new_size = size - n;
	char* new_digits = new char[new_size];

	for (size_t i = 0; i < new_size; ++i)
		new_digits[i] = digits[i];

	delete[] digits;

	digits = new_digits;
	size = new_size;
}

//зануление числа
void BigInt::null()
{
	delete[] digits;
	size = 1;
	digits = new char[size];
	digits[0] = 0;
	isPositive = true;
}

//проверка числа на ноль
bool BigInt::isNull() const
{
	if (size == 1 && digits[0] == 0)
		return true;
	return false;
}

//добавление нулей в конце числа
void BigInt::add_nulls(size_t count)
{
	size_t new_size = size + count;
	char* new_digits = new char[new_size]();

	for (size_t i = 0; i < size; ++i)
		new_digits[count + i] = digits[i];

	delete[] digits;

	digits = new_digits;
	size = new_size;
}



//копирование из другого BigInt
void BigInt::copy(const BigInt& other)
{
	size = other.size;

	digits = new char[size];
	for (size_t i = 0; i < size; ++i)
		digits[i] = other.digits[i];

	isPositive = other.isPositive;
}

//обмен с другим BigInt
void BigInt::swap(BigInt& other)
{
	std::swap(size, other.size);
	std::swap(digits, other.digits);
	std::swap(isPositive, other.isPositive);
}



//приватный конструктор для выделения памяти
BigInt::BigInt(size_t new_size)
{
	size = new_size;
	digits = new char[size]();
	isPositive = true;
}



//конструктор по-умолчанию
BigInt::BigInt()
{
	size = 1;
	digits = new char[size];
	digits[0] = 0;
	isPositive = true;
}

//нахождение кол-ва цифр в числе
size_t findSize(int32_t number)
{
	size_t count = 0;

	do {
		number /= 10;
		++count;
	} while (number != 0);

	return count;
}

//конструктор на базе числа (неявно приводит все int'ы к BigInt для поддержки семантики работы с ним)
BigInt::BigInt(int32_t number)
{
	if (number < 0)
		isPositive = false;
	else
		isPositive = true;

	number = abs(number);

	size = findSize(number);
	digits = new char[size];

	for (size_t i = 0; i < size; ++i)
	{
		digits[i] = number % 10;
		number /= 10;
	}
}

//конструктор на базе строки
BigInt::BigInt(const std::string& str)
{
	if (str.empty())
	{
		size = 1;
		digits = new char[size];
		digits[0] = 0;
		isPositive = true;
		return;
	}

	isPositive = true;
	size_t offset = 0;

	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			isPositive = false;
		offset = 1;
	}

	if (str.find_first_not_of("0123456789", offset) != std::string::npos)
	{
		size = 1;
		digits = new char[size];
		digits[0] = 0;
		isPositive = true;
		return;
	}

	while (str[offset] == '0' && offset < str.size() - 1)
		++offset;

	size = str.size() - offset;

	digits = new char[size];

	for (size_t i = 0; i < size; ++i)
		digits[i] = str[str.size() - 1 - i] - '0';

	if (isNull())
		isPositive = true;
}

//конструктор копирования
BigInt::BigInt(const BigInt& other)
{
	copy(other);
}

//конструктор перемещения
BigInt::BigInt(BigInt&& other) :BigInt()
{
	swap(other);
}

//оператор присваивания копированием
BigInt& BigInt::operator=(const BigInt& other)
{
	if (this != &other)
	{
		null();
		copy(other);
	}

	return *this;
}

//оператор присваивания перемещением
BigInt& BigInt::operator=(BigInt&& other)
{
	if (this != &other)
	{
		null();
		swap(other);
	}

	return *this;
}

//деструктор 
BigInt::~BigInt()
{
	delete[] digits;
}



//оператор унарного минуса
BigInt BigInt::operator-() const
{
	BigInt result = *this;

	result.isPositive = !result.isPositive;

	if (result.isNull())
		result.isPositive = true;

	return result;
}

//оператор сложения
BigInt BigInt::operator+(const BigInt& other) const
{
	BigInt result;

	if (this->isPositive == other.isPositive)
	{
		result = additionByAbs(*this, other);
		result.isPositive = this->isPositive;
	}
	else
	{
		if (compareByAbs(*this, other) > 0)
		{
			result = subtractionByAbs(*this, other);
			result.isPositive = this->isPositive;
		}
		else
		{
			result = subtractionByAbs(other, *this);
			result.isPositive = other.isPositive;
		}
	}

	if (result.isNull())
		result.isPositive = true;

	return result;
}

//оператор вычитания
BigInt BigInt::operator-(const BigInt& other) const
{
	BigInt result;

	if (this->isPositive != other.isPositive)
	{
		result = additionByAbs(*this, other);
		result.isPositive = this->isPositive;
	}
	else
	{
		if (compareByAbs(*this, other) > 0)
		{
			result = subtractionByAbs(*this, other);
			result.isPositive = this->isPositive;
		}
		else
		{
			result = subtractionByAbs(other, *this);
			result.isPositive = other.isPositive;
		}
	}

	if (result.isNull())
		result.isPositive = true;

	return result;
}

//оператор умножения
BigInt BigInt::operator*(const BigInt& other) const
{
	BigInt result = multByAbs(*this, other);

	if (this->isPositive == other.isPositive)
		result.isPositive = true;
	else
		result.isPositive = false;

	if (result.isNull())
		result.isPositive = true;

	return result;
}



BigInt BigInt::operator+(int32_t number) const
{
	return *this + BigInt(number);
}

//оператор вычитания
BigInt BigInt::operator-(int32_t number) const
{
	return *this - BigInt(number);
}

//оператор умножения
BigInt BigInt::operator*(int32_t number) const
{
	return *this * BigInt(number);
}



//оператор равенства
bool BigInt::operator==(const BigInt& other) const
{
	if ((this->isPositive == other.isPositive) && (compareByAbs(*this, other) == 0))
		return true;
	return false;
}

//оператор неравенства
bool BigInt::operator!=(const BigInt& other) const
{
	return (*this == other);
}

//оператор меньше
bool BigInt::operator<(const BigInt& other) const
{
	if (this->isPositive == other.isPositive)
	{
		int code = compareByAbs(*this, other);

		if ((this->isPositive && code < 0) || (!this->isPositive && code > 0))
			return true;
		return false;
	}
	else
	{
		if (other.isPositive)
			return true;
		return false;
	}
}

//оператор больше
bool BigInt::operator>(const BigInt& other) const
{
	return (other < *this);
}

//оператор меньше или равно
bool BigInt::operator<=(const BigInt& other) const
{
	return !(*this > other);
}

//оператор больше или равно
bool BigInt::operator>=(const BigInt& other) const
{
	return !(*this < other);
}



std::ostream& operator<<(std::ostream& output, const BigInt& bigint)
{
	if (!bigint.isPositive)
		output << '-';

	for (size_t i = bigint.size - 1; i != std::string::npos; --i)
		output << (int)bigint.digits[i];

	return output;
}