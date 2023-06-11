

#include "INI.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    try 
    {
    INI parser("INI");

    auto value = parser.get_value<std::string>("Section2.var1");

    std::cout << value << "\n";
      
    return (0);
    }
  
    
    catch (const std::runtime_error& ex) 
    {
        std::cout << ex.what();
    }
    catch (const std::bad_any_cast & ex)
    {
        std::cout << ex.what();
    }
}