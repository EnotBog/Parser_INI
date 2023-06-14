

#include "INI.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    try 
    {
    INI parser("INI");

  //  auto value = parser.get_value<int>("Section2.var1");

    std::cout << parser.get_value<std::string>("Section1.var1") << "\n";
    std::cout << parser.get_value<int>("Section1.var1") << "\n";
    std::cout << parser.get_value<double>("Section1.var1") << "\n";

      
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