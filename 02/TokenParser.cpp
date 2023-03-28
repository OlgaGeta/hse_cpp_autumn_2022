#include "TokenParser.hpp"

//������������� callback-������� ����� ������� ��������.
void TokenParser::SetStartCallback(f_void callback)
{
	callback_start = callback;
}

//������������� callback-������� ����� ��������� ��������.
void TokenParser::SetEndCallback(f_void callback)
{
	callback_end = callback;
}

//������������� callback-������� ��� ��������� �����.
void TokenParser::SetDigitTokenCallback(f_uint64_t callback)
{
	callback_uint64_t = callback;
}

//������������� callback-������� ��� ��������� �����.
void TokenParser::SetStringTokenCallback(f_string callback)
{
	callback_string = callback;
}

//������� ������.
void TokenParser::Parse(const std::string& str)
{
	if (callback_start != nullptr)
		callback_start();

	size_t offset = 0;

	while (offset < str.length())
	{
		//����� ������� �����������:
		size_t i;
		for (i = offset; i < str.length(); ++i)
			if (str[i] == ' ' or str[i] == '\t' or str[i] == '\n')
				break;

		//���������� ���������� ������:
		std::string token = str.substr(offset, i - offset);

		//���� ����� ������ �� ����� 0:
		if (token.length() != 0)
		{
			//������� ������������� ��������� ����� � �����:
			uint64_t number = 0;
			bool isCorrectNumber = true;
			for (size_t j = 0; j < token.length(); ++j)
			{
				if ('0' <= token[j] and token[j] <= '9')
				{
					int digit = token[j] - '0'; //�������� ����� �� ������� ASCII

					//������ ������������ ���� ��� ����� ��� �������� ��� ������ �� �������:
					long double clone = number;

					number = number * 10 + digit; //�������� ����� ����� �� ���� ������ (*10) + �����
					clone = clone * 10 + digit;

					//���� number �� �����, � �������� � ������ ������ ���������, �� ���������� �������������:
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

			//������ ������, ����� - ������ ��� �����:
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
		}

		//����� ��� �������� ���������� ������:
		offset = i + 1;
	}

	if (callback_end != nullptr)
		callback_end();
}