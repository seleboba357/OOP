#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <utility>
#include <vector>



// шаблоны для идеально передачи аргументов 
template<typename T>
void wrapper(T&& arg)
{
    func(std::forward<T>(arg));
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // два значения разных типов в одном объекте 
    std::pair<int, std::string> p = { 1, "Hello" };
    std::cout << p.first << " " << p.second << std::endl;

    // создание пары без явного указания типов 
    auto p = std::make_pair(10, 3.14);

    // перемещение ресурсов, чтобы избежать копирования 
    std::vector<int> v1 = { 1, 2, 3 };
    std::vector<int> v2 = std::move(v1);

    std::cout << "v1 size: " << v1.size() << std::endl;
    std::cout << "v2 size: " << v2.size() << std::endl;

    // свапает значение двух переменных 
    int a = 5, b = 10;
    std::swap(a, b);

    std::cout << a << " " << b << std::endl;

    // замена значение переменной с возвратом старого 
    int x = 5;
    int old = std::exchange(x, 10);

    std::cout << "old: " << old << ", new: " << x << std::endl;




    return 0;
}