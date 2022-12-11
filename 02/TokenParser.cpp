#include "TokenParser.hpp"

//Устанавливаем callback-функцию перед стартом парсинга.
void TokenParser::SetStartCallback(f_void callback)
{
	callback_start = callback;
}

//Устанавливаем callback-функцию после окончания парсинга.
void TokenParser::SetEndCallback(f_void callback)
{
	callback_end = callback;
}

//Устанавливаем callback-фкнкцию для обработки чисел.
void TokenParser::SetDigitTokenCallback(f_uint64_t callback)
{
	callback_uint64_t = callback;
}

//Устанавливаем callback-функцию для обработки строк.
void TokenParser::SetStringTokenCallback(f_string callback)
{
	callback_string = callback;
}

//парсинг строки.
void TokenParser::Parse(const std::string& str)
{
	if (callback_start != nullptr)
		callback_start();

	size_t offset = 0;

	while (offset < str.length())
	{
		//поиск первого разделителя:
		size_t i;
		for (i = offset; i < str.length(); ++i)
			if (str[i] == ' ' or str[i] == '\t' or str[i] == '\n')
				break;

		//вычисление строкового токена:
		std::string token = str.substr(offset, i - offset);

		//попытка преобразовать строковый токен к числу:
		uint64_t number = 0;
		bool isCorrectNumber = true;
		for (size_t j = 0; j < token.length(); ++j)
		{
			if ('0' <= token[j] and token[j] <= '9')
			{
				int digit = token[j] - '0'; //получаем цифру из символа ASCII

				//создаём вещественный клон для числа (макс. 35 значащих цифр) для проверки для выхода за границы:
				long double clone = number;

				number = number * 10 + digit; //сдвигаем число влево на один разряд (*10) + цифра
				clone = clone * 10 + digit;

				//если number не вырос, а вернулся к началу своего диапазона, то переменная переполнилась :
				if (number < clone)
				{
					isCorrectNumber = false;
					break;
				}
			}
			else
			{
				isCorrectNumber = false;
				break;
			}
		}

		//делаем выводы, токен-строка или число:
		if (isCorrectNumber)
		{
			if (callback_uint64_t != nullptr)
				callback_uint64_t(number);
		}
		else
		{
			if (callback_string != nullptr)
				callback_string(token);
		}

		//сдвиг для вычисления следующего токена:
		offset = i + 1;
	}

	if (callback_end != nullptr)
		callback_end();
}