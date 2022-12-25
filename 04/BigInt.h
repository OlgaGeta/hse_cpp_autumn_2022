
#ifndef BIG_INT_H__

#define BIG_INT_H__

#include <iostream>
#include <string>

class BigInt
{
	//сравнение двух чисел по модулю
	friend int compareByAbs(const BigInt& a, const BigInt& b);
	//сложение двух чисел по модулю
	friend BigInt additionByAbs(const BigInt& a, const BigInt& b);
	//вычитание двух чисел по модулю
	friend BigInt subtractionByAbs(const BigInt& a, const BigInt& b);
	//произведение числа на цифру по модулю
	friend BigInt multByAbs(const BigInt& number, char digit);
	//произведение двух чисел по модулю
	friend BigInt multByAbs(const BigInt& a, const BigInt& b);

private:
	char* digits;
	size_t size;
	bool isPositive;

	//удаление незначащих нулей
	void remove_insignificant_zeros();

	//зануление числа
	void null();

	//проверка числа на ноль
	bool isNull() const;

	//добавление нулей в конце числа
	void add_nulls(size_t count);

	//копирование из другого BigInt
	void copy(const BigInt& other);
	//обмен с другим BigInt
	void swap(BigInt& other);

private:
	//приватный конструктор для выделения памяти
	BigInt(size_t new_size);

public:
	//конструктор по-умолчанию
	BigInt();
	//конструктор на базе числа (неявно приводит все int'ы к BigInt для поддержки семантики работы с ним)
	BigInt(int32_t number);
	//конструктор на базе строки
	BigInt(const std::string& str);

	//конструктор копирования
	BigInt(const BigInt& other);
	//конструктор перемещения
	BigInt(BigInt&& other);

	//оператор присваивания копированием
	BigInt& operator=(const BigInt& other);
	//оператор присваивания перемещением
	BigInt& operator=(BigInt&& other);

	//деструктор 
	~BigInt();

	//оператор унарного минуса
	BigInt operator-() const;

	//оператор сложения
	BigInt operator+(const BigInt& other) const;
	//оператор вычитания
	BigInt operator-(const BigInt& other) const;
	//оператор умножения
	BigInt operator*(const BigInt& other) const;

	//оператор сложения
	BigInt operator+(int32_t number) const;
	//оператор вычитания
	BigInt operator-(int32_t number) const;
	//оператор умножения
	BigInt operator*(int32_t number) const;

	//оператор равенства
	bool operator==(const BigInt& other) const;
	//оператор неравенства
	bool operator!=(const BigInt& other) const;
	//оператор меньше
	bool operator<(const BigInt& other) const;
	//оператор больше
	bool operator>(const BigInt& other) const;
	//оператор меньше или равно
	bool operator<=(const BigInt& other) const;
	//оператор больше или равно
	bool operator>=(const BigInt& other) const;

	friend std::ostream& operator<<(std::ostream& output, const BigInt& bigint);
};



#endif
