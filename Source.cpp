#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
#include <iterator>
#include <fstream>
#include <any>

class INI
{

public:

    template<typename T>
    T get_value(const std::string& str) //"section.value"
    {
        std::pair<std::string, std::string> buf_pair = std::move(get_section(str));
        std::string buf1 = m[buf_pair.first].at(buf_pair.second);

        auto _type = typeid(T).name();

        std::any any = is_type(buf1);

        std::cout << std::any_cast<int>(any);
        
        auto boool = any.type() == typeid(T);

        if (boool) { return std::any_cast<T>(any); }
        
    }
 
   std::any is_type(const std::string& str)
    {
       std::any a;
        // типы данных 
        // bool 
        // int
        // double
        // string
        //char
        // если есть буквы и цифры то это строка 
        //если есть точка или запятая это double
        // если только число то это инт

       
        if (str.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") != std::string::npos) //ЭТО СТРОКА 
        {
            {
                std::string str1 = str;
                return  a.emplace<std::string>(str1);
            }
        }
        if (str.find_first_of("1234567890") != std::string::npos) //ЭТО инт
        {
            {
                int i = stoi(str); 
                return  a.emplace<int>(i);
            }
        }

        if (str.find_first_of("1234567890.,") != std::string::npos) //ЭТО Дабл
        {
            {
                double d = stod(str); 
                return a.emplace<double>(d);
            }
        }
        std::cout << "Non type is_type\n"; throw("попадос");/// ТУТ исключение 
    }
        

    std::pair<std::string, std::string> get_section(const std::string& str)  //("section.value")
    {

        std::string section;
        std::string value;

        int counter = 0;

        for (unsigned i = 0; i < str.size(); i++)
        {
            if (str[i] != ' ' && (counter == 1))
            {
                value += str[i];
            }
            else if (str[i] != ' ' && str[i] != '.')
            {
                section += str[i];
            }
            else if (str[i] == '.')
            {
                counter = 1;
            }

        }
        return std::make_pair(section, value);
    }

    bool find_ch(int ind,char ch)
    {
        auto size = str[ind].size();
        for (unsigned i = 0; i < size ; i++)
        {
            if (str[ind][i] == ch)
            {
                return true;
            }            
        }
        return false;
    }
    
    std::pair<std::string,std::string> extr_valve(int ind)
    {
        std::string s1;
        std::string s2;
        int counter = 0;
        for (unsigned i = 0; i< str[ind].size(); i++)
        {
            if (str[ind][i] != ' '&& (counter==1))
            {
                s2 += str[ind][i];
            }
            else if (str[ind][i] != ' ' && str[ind][i] != '=')
            {
                s1 += str[ind][i];
            }
            else if (str[ind][i]=='=')
            {
                counter = 1;
            }
            
        }; 
        return std::make_pair(s1, s2);
    }

    std::string extr_section(int ind)
    {
        std::string s;
        for (unsigned i = 0; i<str[ind].size(); i++)
        {
            if (str[ind][i] == ' ' )
            {
            }
            else if ((str[ind][i] != ' ') && (str[ind][i] != '[') && (str[ind][i]!=']'))
            {
                s += str[ind][i];
            }
            else if (str[ind][i] == '[' || (str[ind][i] == ']'))
            {
                 
            }

        };
        return s;
    }

    void edit_file(std::vector<std::string> &l)
    {
        unsigned i = 0;
        auto size = l.size();

        for (; i < size; )
        {
            std::string section;
            std::pair<std::string, std::string> pair;
            if (l[i].find('[') != std::string::npos && l[i + 1].find('[') == std::string::npos && i<size)
            {
                section = std::move(extr_section(i));
                i++;/////нашли секцию

            for (; i < size&& l[i].find('[') == std::string::npos; )
                    {
                        if (l[i].find('=')!=std::string::npos)
                        {
                          pair = std::move(extr_valve(i)); /// эту пару засунуть в мап0 
                         m[section][pair.first] = pair.second;// insert(pair.first, pair.second);
                         i++;
                        } 
                    }  
            }
            else { i++; } //если есть пустая секция
        }

    };

    INI(std::string s) :file(std::ifstream( s +".txt")) //// работа со строкой из файла
    {
        if (file.is_open())
        {
            while (!file.eof())
            { 
                std::string s;
                std::getline(file, s);

                if (s.size() < 3)
                {
                    // не записываем строку в массив
                }
                else if (s.find(';')!=std::string::npos)
                {
                    auto it = s.find(';'); /// удаляем комментарии
                    if (it > 0) 
                    {
                        s.erase(s.begin() + it, s.end()); str.push_back(std::move(s));
                    }
                    else {}
                }
                else 
                {
                str.push_back(std::move(s));
                }
            }
                file.close();

                edit_file(str);
        }
        else
        {
            std::cerr << "File not open!;";
        }
    }

    INI() {}

    std::map<std::string, std::map<std::string, std::string>> m;
    std::vector<std::string> str; // сюда засовываем файл по строчно; 
    std::ifstream file;
private:
};
int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");


    INI parser("INI");

  auto value = parser.get_value<int>("Section4.Mode");

  std::cout << value << "\n";



    std::cout << parser.m["Section1"]["var1"];
    return (0);

}