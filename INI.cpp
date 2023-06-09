#include"INI.h"



    INI::INI(std::string s) :file(std::ifstream(s + ".txt")) //// работа со строкой из файла
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
                else if (s.find(';') != std::string::npos)
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
            throw std::runtime_error(s + " File not open!");
        }
    }


    std::pair<std::string, std::string> INI::get_section(const std::string& str)   //("section.value")
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
        if (m[section][value].size() == 0) { throw std::runtime_error(section + " " + value + " Non value"); }
        return std::make_pair(section, value);
    }


    std::any INI::is_type(const std::string& str) const
    {
        std::any a;

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

    }


    std::pair<std::string, std::string> INI::extr_valve(int ind) const
    {
        std::string s1;
        std::string s2;
        int counter = 0;
        for (unsigned i = 0; i < str[ind].size(); i++)
        {
            if (str[ind][i] != ' ' && (counter == 1))
            {
                s2 += str[ind][i];
            }
            else if (str[ind][i] != ' ' && str[ind][i] != '=')
            {
                s1 += str[ind][i];
            }
            else if (str[ind][i] == '=')
            {
                counter = 1;
            }

        };
        return std::make_pair(s1, s2);
    }

    std::string INI::extr_section(int ind) const
    {
        std::string s;
        for (unsigned i = 0; i < str[ind].size(); i++)
        {
            if (str[ind][i] == ' ')
            {
            }
            else if ((str[ind][i] != ' ') && (str[ind][i] != '[') && (str[ind][i] != ']'))
            {
                s += str[ind][i];
            }
            else if (str[ind][i] == '[' || (str[ind][i] == ']'))
            {

            }

        };
        return s;
    }


    void INI::edit_file(std::vector<std::string>& l)
    {
        unsigned i = 0;
        auto size = l.size();

        for (; i < size; )
        {
            std::string section;
            std::pair<std::string, std::string> pair;
            if (l[i].find('[') != std::string::npos && l[i + 1].find('[') == std::string::npos && i < size)
            {
                section = std::move(extr_section(i));
                i++;/////нашли секцию

                for (; i < size && l[i].find('[') == std::string::npos; )
                {
                    if (l[i].find('=') != std::string::npos)
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

