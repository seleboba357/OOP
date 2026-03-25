#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iomanip>

class Fraction {
private:
    int numerator;     
    int denominator;   


    int gcd(int a, int b) const 
    {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) 
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }


    void reduce() 
    {
        if (denominator == 0) 
        {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }

        if (denominator < 0) 
        {
            numerator = -numerator;
            denominator = -denominator;
        }

        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
    }

public:

    Fraction() : numerator(0), denominator(1) {
        std::cout << "Вызван конструктор по умолчанию" << std::endl;
    }

    Fraction(int num, int den = 1) : numerator(num), denominator(den) 
    {
        if (den == 0) 
        {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }
        reduce();
        std::cout << "Вызван конструктор с параметрами: " << numerator << "/" << denominator << std::endl;
    }


    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) 
    {
        std::cout << "Вызван конструктор копирования: " << numerator << "/" << denominator << std::endl;
    }

  
    Fraction(double value) 
    {
 
        const double epsilon = 1e-6;
        int sign = (value < 0) ? -1 : 1;
        value = std::abs(value);

        int num = static_cast<int>(value);
        double fractional = value - num;

        if (fractional < epsilon) 
        {
            numerator = sign * num;
            denominator = 1;
        }
        else {
            int den = 1;
            while (std::abs(value - static_cast<double>(num) / den) > epsilon && den < 1000000) 
            {
                den++;
                num = static_cast<int>(value * den + 0.5);
            }
            numerator = sign * num;
            denominator = den;
            reduce();
        }
        std::cout << "Вызван конструктор из double: " << numerator << "/" << denominator << std::endl;
    }

 
    ~Fraction() 
    {
        std::cout << "Вызван деструктор: " << numerator << "/" << denominator << std::endl;
    }

  
    Fraction& operator=(const Fraction& other) 
    {
        std::cout << "Вызван оператор присваивания (копирование)" << std::endl;
        if (this != &other) 
        {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;
    }

  
    Fraction& operator=(int value) 
    {
        std::cout << "Вызван оператор присваивания из int" << std::endl;
        numerator = value;
        denominator = 1;
        reduce();
        return *this;
    }

  
    Fraction& operator=(double value) 
    {
        std::cout << "Вызван оператор присваивания из double" << std::endl;
        *this = Fraction(value);
        return *this;
    }

 
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

 
    double toDouble() const 
    {
        return static_cast<double>(numerator) / denominator;
    }

   
    operator double() const 
    {
        return toDouble();
    }


    Fraction operator+(const Fraction& other) const 
    {
        int newNum = numerator * other.denominator + other.numerator * denominator;
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    Fraction operator-(const Fraction& other) const 
    {
        int newNum = numerator * other.denominator - other.numerator * denominator;
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    Fraction operator*(const Fraction& other) const 
    {
        int newNum = numerator * other.numerator;
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    Fraction operator/(const Fraction& other) const 
    {
        if (other.numerator == 0) 
        {
            throw std::invalid_argument("Деление на ноль");
        }
        int newNum = numerator * other.denominator;
        int newDen = denominator * other.numerator;
        return Fraction(newNum, newDen);
    }

  
    Fraction operator+(int value) const 
    {
        return *this + Fraction(value);
    }

    Fraction operator-(int value) const 
    {
        return *this - Fraction(value);
    }

    Fraction operator*(int value) const 
    {
        return *this * Fraction(value);
    }

    Fraction operator/(int value) const 
    {
        if (value == 0) 
        {
            throw std::invalid_argument("Деление на ноль");
        }
        return *this / Fraction(value);
    }

  
    Fraction operator+(double value) const 
    {
        return *this + Fraction(value);
    }

    Fraction operator-(double value) const 
    {
        return *this - Fraction(value);
    }

    Fraction operator*(double value) const 
    {
        return *this * Fraction(value);
    }

    Fraction operator/(double value) const 
    {
        if (std::abs(value) < 1e-10) 
        {
            throw std::invalid_argument("Деление на ноль");
        }
        return *this / Fraction(value);
    }

    
    friend Fraction operator+(int value, const Fraction& fraction) 
    {
        return fraction + value;
    }

    friend Fraction operator-(int value, const Fraction& fraction) 
    {
        return Fraction(value) - fraction;
    }

    friend Fraction operator*(int value, const Fraction& fraction) 
    {
        return fraction * value;
    }

    friend Fraction operator/(int value, const Fraction& fraction) 
    {
        return Fraction(value) / fraction;
    }

    friend Fraction operator+(double value, const Fraction& fraction) 
    {
        return fraction + value;
    }

    friend Fraction operator-(double value, const Fraction& fraction) 
    {
        return Fraction(value) - fraction;
    }

    friend Fraction operator*(double value, const Fraction& fraction) 
    {
        return fraction * value;
    }

    friend Fraction operator/(double value, const Fraction& fraction) 
    {
        return Fraction(value) / fraction;
    }

   
    Fraction& operator+=(const Fraction& other) 
    {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) 
    {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) 
    {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) 
    {
        *this = *this / other;
        return *this;
    }

    Fraction& operator+=(int value) 
    {
        *this = *this + value;
        return *this;
    }

    Fraction& operator-=(int value) 
    {
        *this = *this - value;
        return *this;
    }

    Fraction& operator*=(int value) 
    {
        *this = *this * value;
        return *this;
    }

    Fraction& operator/=(int value) 
    {
        *this = *this / value;
        return *this;
    }

  
    Fraction operator-() const 
    {
        return Fraction(-numerator, denominator);
    }

    Fraction operator+() const 
    {
        return *this;
    }

   
    Fraction& operator++() 
    { 
        *this += 1;
        return *this;
    }

    Fraction operator++(int) 
    { 
        Fraction temp = *this;
        *this += 1;
        return temp;
    }

    Fraction& operator--() 
    {
        *this -= 1;
        return *this;
    }

    Fraction operator--(int) 
    {
        Fraction temp = *this;
        *this -= 1;
        return temp;
    }

  
    bool operator==(const Fraction& other) const 
    {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Fraction& other) const 
    {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const 
    {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator>(const Fraction& other) const 
    {
        return other < *this;
    }

    bool operator<=(const Fraction& other) const 
    {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const 
    {
        return !(*this < other);
    }


    bool operator==(int value) const 
    {
        return *this == Fraction(value);
    }

    bool operator!=(int value) const 
    {
        return !(*this == value);
    }

    bool operator<(int value) const 
    {
        return *this < Fraction(value);
    }

    bool operator>(int value) const 
    {
        return *this > Fraction(value);
    }

    bool operator<=(int value) const 
    {
        return *this <= Fraction(value);
    }

    bool operator>=(int value) const 
    {
        return *this >= Fraction(value);
    }

  
    bool operator==(double value) const 
    {
        return std::abs(toDouble() - value) < 1e-9;
    }

    bool operator!=(double value) const 
    {
        return !(*this == value);
    }

    bool operator<(double value) const 
    {
        return toDouble() < value;
    }

    bool operator>(double value) const 
    {
        return toDouble() > value;
    }

    bool operator<=(double value) const 
    {
        return toDouble() <= value;
    }

    bool operator>=(double value) const 
    {
        return toDouble() >= value;
    }

  
    friend bool operator==(int value, const Fraction& fraction) 
    {
        return fraction == value;
    }

    friend bool operator!=(int value, const Fraction& fraction) 
    {
        return !(fraction == value);
    }

    friend bool operator<(int value, const Fraction& fraction) 
    {
        return fraction > value;
    }

    friend bool operator>(int value, const Fraction& fraction) 
    {
        return fraction < value;
    }

    friend bool operator<=(int value, const Fraction& fraction) 
    {
        return fraction >= value;
    }

    friend bool operator>=(int value, const Fraction& fraction) 
    {
        return fraction <= value;
    }

    friend bool operator==(double value, const Fraction& fraction) 
    {
        return fraction == value;
    }

    friend bool operator!=(double value, const Fraction& fraction) 
    {
        return fraction != value;
    }

    friend bool operator<(double value, const Fraction& fraction) 
    {
        return fraction > value;
    }

    friend bool operator>(double value, const Fraction& fraction) 
    {
        return fraction < value;
    }

    friend bool operator<=(double value, const Fraction& fraction) 
    {
        return fraction >= value;
    }

    friend bool operator>=(double value, const Fraction& fraction) 
    {
        return fraction <= value;
    }

  
    void printDecimal() const 
    {
        std::cout << toDouble();
    }

    void printFraction() const 
    {
        std::cout << numerator;
        if (denominator != 1) {
            std::cout << "/" << denominator;
        }
    }

 
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction) 
    {
        fraction.printDecimal();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Fraction& fraction) 
    {
        int num, den;
        char slash;
        is >> num >> slash >> den;
        if (slash != '/') 
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        fraction = Fraction(num, den);
        return is;
    }
};


int main() 
{
    std::cout << std::fixed << std::setprecision(4);

    try 
    {
        std::cout << "=== Демонстрация конструкторов и операторов присваивания ===\n" << std::endl;

        Fraction f1;                  
        Fraction f2(3, 4);            
        Fraction f3 = f2;          
        Fraction f4(0.75);             

        f1 = f2;                        
        f1 = 5;                         
        f1 = 2.5;                       

        std::cout << "\n=== Демонстрация арифметических операций ===\n" << std::endl;

        Fraction a(3, 4);
        Fraction b(1, 2);

        std::cout << "a = " << a << " ("; a.printFraction(); std::cout << ")" << std::endl;
        std::cout << "b = " << b << " ("; b.printFraction(); std::cout << ")" << std::endl;

   
        std::cout << "\nАрифметика с дробями:" << std::endl;
        std::cout << "a + b = " << a + b << std::endl;
        std::cout << "a - b = " << a - b << std::endl;
        std::cout << "a * b = " << a * b << std::endl;
        std::cout << "a / b = " << a / b << std::endl;

     
        std::cout << "\nАрифметика с целыми числами:" << std::endl;
        std::cout << "a + 2 = " << a + 2 << std::endl;
        std::cout << "3 + a = " << 3 + a << std::endl;
        std::cout << "a * 3 = " << a * 3 << std::endl;
        std::cout << "4 * a = " << 4 * a << std::endl;

    
        std::cout << "\nАрифметика с double:" << std::endl;
        std::cout << "a + 0.25 = " << a + 0.25 << std::endl;
        std::cout << "1.5 + a = " << 1.5 + a << std::endl;
        std::cout << "a * 2.0 = " << a * 2.0 << std::endl;

        std::cout << "\n=== Демонстрация операторов сравнения ===\n" << std::endl;

        Fraction x(2, 3);
        Fraction y(3, 4);

        std::cout << "x = " << x << ", y = " << y << std::endl;
        std::cout << "x < y = " << (x < y ? "true" : "false") << std::endl;
        std::cout << "x > y = " << (x > y ? "true" : "false") << std::endl;
        std::cout << "x == 0.6667 = " << (x == 0.6667 ? "true" : "false") << std::endl;
        std::cout << "0.75 == y = " << (0.75 == y ? "true" : "false") << std::endl;
        std::cout << "x < 0.8 = " << (x < 0.8 ? "true" : "false") << std::endl;
        std::cout << "2 > x = " << (2 > x ? "true" : "false") << std::endl;

        std::cout << "\n=== Демонстрация унарных операторов ===\n" << std::endl;

        Fraction z(2, 3);
        std::cout << "z = " << z << std::endl;
        std::cout << "-z = " << -z << std::endl;
        std::cout << "+z = " << +z << std::endl;

        std::cout << "\n=== Демонстрация инкремента/декремента ===\n" << std::endl;

        Fraction w(1, 2);
        std::cout << "w = " << w << std::endl;
        std::cout << "++w = " << ++w << std::endl;
        std::cout << "w++ = " << w++ << std::endl;
        std::cout << "w = " << w << std::endl;
        std::cout << "--w = " << --w << std::endl;

        std::cout << "\n=== Демонстрация составных операторов ===\n" << std::endl;

        Fraction v(1, 3);
        std::cout << "v = " << v << std::endl;
        v += Fraction(1, 6);
        std::cout << "v += 1/6 = " << v << std::endl;
        v *= 2;
        std::cout << "v *= 2 = " << v << std::endl;

        std::cout << "\n=== Демонстрация неявного преобразования в double ===\n" << std::endl;

        Fraction pi(355, 113);  
        double d = pi;           
        std::cout << "pi (355/113) = " << pi << std::endl;
        std::cout << "double d = pi = " << d << std::endl;

        double result = pi * 2.5;  
        std::cout << "pi * 2.5 = " << result << std::endl;

        std::cout << "\n=== Ввод дроби ===\n" << std::endl;
        std::cout << "Введите дробь в формате числитель/знаменатель: ";
        Fraction input;
        std::cin >> input;
        std::cout << "Вы ввели: " << input << " (";
        input.printFraction();
        std::cout << ")" << std::endl;

    }
    catch (const std::exception& e) 
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}