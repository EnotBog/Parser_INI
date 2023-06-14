#pragma once
#include <any>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <variant>

class INI
{

public:

   

    template<typename T>
    T get_value(const std::string& str) //"section.value"
    {
        T result;
        std::pair<std::string, std::string> buf_pair = get_section(str);

        std::string& buf1 = m[buf_pair.first].at(buf_pair.second);

        auto _type = typeid(T).name();

        /* std::any any = is_type(buf1, _type);

        auto any1 = any.type().name();*/


        std::variant<int, float, long, double, std::string> var;

        var = is_type_var(buf1, _type);

            if (std::holds_alternative<T>(var))
            {
               result = *std::get_if<T>(&var);
            }
            else if (std::holds_alternative<int>(var))
            {
               result= (*std::get_if<int>(&var));
            }
            else if (std::holds_alternative<float>(var))
            {
                  result = (*std::get_if<float>(&var));
            }

            return  result;

        std::cerr << "Non value" + str << "\n";
            return NULL;
    }



    //if (any.has_value())
    //{
    //    if (_type == any1)
    //    {
    //        return std::any_cast<T>(any);
    //    }
    //    else 
    //    {
    //        std::cout << "Not type: " << _type << str << " Has type :" << any1;
    //    }
    //}

    //else
    //{
    //    throw std::runtime_error("Non value " + std::string(_type) + " " + str);
    //}
    INI(std::string s); //// работа со строкой из файла




private:
    std::map<std::string, std::map<std::string, std::string>> m;
    std::vector<std::string> str; // сюда засовываем файл по строчно; 
    std::ifstream file;


    std::pair<std::string, std::string> get_section(const std::string& str);   //("section.value")     

    std::variant<int, float, long, double, std::string> is_type_var(std::string& str, const char* type)const;

    std::any is_type(std::string& str, const char* _type) const;

    std::pair<std::string, std::string> extr_valve(int ind) const;

    std::string extr_section(int ind) const;

    void edit_file(std::vector<std::string>& l);
};
   