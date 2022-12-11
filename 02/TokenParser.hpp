#ifndef TOKEN_PARSER_HPP_

#define TOKEN_PARSER_HPP_

#include <string>

typedef void(*f_uint64_t)(uint64_t);
typedef void(*f_string)(const std::string&);
typedef void(*f_void)();

class TokenParser
{
private:
	f_uint64_t callback_uint64_t = nullptr;
	f_string callback_string = nullptr;

	f_void callback_start = nullptr;
	f_void callback_end = nullptr;
public:

	TokenParser() = default;

	//Устанавливаем callback-функцию перед стартом парсинга.
	void SetStartCallback(f_void callback);

	//Устанавливаем callback-функцию после окончания парсинга.
	void SetEndCallback(f_void callback);

	//Устанавливаем callback-функцию для обработки чисел.
	void SetDigitTokenCallback(f_uint64_t callback);

	//Устанавливаем callback-функцию для обработки строк.
	void SetStringTokenCallback(f_string callback);

	//Парсинг строки.
	void Parse(const std::string& str);

};

#endif //!TOKEN_PARSER_HPP_