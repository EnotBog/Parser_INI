#pragma once
#include <any>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
#include <fstream>

class INI
{

public:

    template<typename T>
    T get_value(const std::string& str) //"section.value"
    {

        std::pair<std::string, std::string> buf_pair = get_section(str);

        std::string &buf1 = m[buf_pair.first].at(buf_pair.second);

        auto _type = typeid(T).name();

        std::any any = is_type(buf1,_type);

        if (any.has_value())
        {
          return std::any_cast<T>(any); }
        else
        {
            throw std::runtime_error("Non tupe " + std::string(_type) + " " + str);
        }
    }

    INI(std::string s); //// работа со строкой из файла

private:
    std::map<std::string, std::map<std::string, std::string>> m;
    std::vector<std::string> str; // сюда засовываем файл по строчно; 
    std::ifstream file;


    std::pair<std::string, std::string> get_section(const std::string& str);   //("section.value")     

    std::any is_type( std::string& str, const char* _type ) const;
   
    std::pair<std::string, std::string> extr_valve(int ind) const;

    std::string extr_section(int ind) const;

    void edit_file(std::vector<std::string>& l);
};
