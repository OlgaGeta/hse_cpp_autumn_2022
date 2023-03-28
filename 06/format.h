#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>

#include <sstream>
#include <cstddef>
#include <string>
#include <exception>
#include <cctype>


class ValueError: public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Wrong value in {}";
    }
};

class BracketsError: public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Wrong brackets usage";
    }
};

class ArgumentError: public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Wrong numbers of arguments";
    }
};


void parse(std::ostream &out, size_t num)
{}


template <class T>
void parse(std::ostream &out, size_t num, const T& arg)
{
    if(num == 0)
        out << arg;
    else
        throw ValueError();
}



template <class T, class... Args>
void parse(std::ostream &out, size_t num, const T &arg, const Args&... args)
{
    if(num == 0)
        out << arg;
    else
        parse(out, num - 1, args...);
}


template <class... Args>
std::string format(const std::string &s, const Args& ... args)
{
    if(s.empty())
    {
        std::string result = s;
        return result;
    }

    if(s == "{}")
        throw ValueError();

    size_t sizeargs = sizeof...(args);

    size_t numofbrackets = 0;
    std::ostringstream ss;
    bool flag = false;
    bool is_num = false;
    size_t buf = 0;
    if(sizeargs == 0)
    {
        std::string result = s;
        return result;
    }

    for(auto c: s)
    {
        if(c == '{')
        {
            if(flag)
                throw BracketsError();
            if(c+1 == '}')
                throw ValueError();
            flag = true;
            continue;
        }
        if(c == '}')
        {
            if(!flag)
                throw BracketsError();
            if(!is_num)
                throw ValueError();
            flag = false;
            parse(ss, buf, args...);
            buf = 0;
            is_num = false;
            numofbrackets++;
            continue;
        }
        if(flag)
        {
            if(!std::isdigit(c))
                throw ValueError();
            buf = buf * 10 + static_cast<size_t>(c - '0');
            if( buf > 10000)
                throw ValueError();
            is_num = true;
            continue;
        }
        ss << c;
    }
    if(flag)
        throw BracketsError();
    //std::cout << sizeargs<<std::endl;
    //std::cout << numofbrackets<<std::endl;
    if(numofbrackets < sizeargs)
    {
        throw ArgumentError();
    }
    return ss.str();
}

#endif
