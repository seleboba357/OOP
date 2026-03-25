#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

class Fraction {
private:
    int numerator;    
    int denominator;  


    int gcd(int a, int b) const {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }


    void reduce() {
        if (denominator == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }

        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
    }

public:

    Fraction() : numerator(0), denominator(1) {}

    Fraction(int num, int den = 1) : numerator(num), denominator(den) {
        if (den == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }
        reduce();
    }


    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}


    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }


    void setNumerator(int num) {
        numerator = num;
        reduce();
    }

    void setDenominator(int den) {
        if (den == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }
        denominator = den;
        reduce();
    }

    Fraction operator+(const Fraction& other) const {
        int newNum = numerator * other.denominator + other.numerator * denominator;
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    Fraction operator-(const Fraction& other) const {
        int newNum = numerator * other.denominator - other.numerator * denominator;
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    Fraction operator*(const Fraction& other) const {
        int newNum = numerator * other.numerator;
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Деление на ноль");
        }
        int newNum = numerator * other.denominator;
        int newDen = denominator * other.numerator;
        return Fraction(newNum, newDen);
    }


    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator>(const Fraction& other) const {
        return other < *this;
    }

    bool operator<=(const Fraction& other) const {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }


    Fraction& operator=(const Fraction& other) {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;
    }

    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }


    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }


    void printDecimal() const {
        std::cout << toDouble();
    }

 
    void printFraction() const {
        std::cout << numerator;
        if (denominator != 1) {
            std::cout << "/" << denominator;
        }
    }


    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
        fraction.printDecimal();
        return os;
    }


    friend std::istream& operator>>(std::istream& is, Fraction& fraction) {
        int num, den;
        char slash;
        is >> num >> slash >> den;
        if (slash != '/') {
            is.setstate(std::ios::failbit);
            return is;
        }
        fraction = Fraction(num, den);
        return is;
    }
};


int main() {
    try {
        
        Fraction f1(3, 4);      
        Fraction f2(1, 2);      
        Fraction f3(5);        

        std::cout << "f1 = "; f1.printFraction(); std::cout << " = " << f1 << std::endl;
        std::cout << "f2 = "; f2.printFraction(); std::cout << " = " << f2 << std::endl;
        std::cout << "f3 = "; f3.printFraction(); std::cout << " = " << f3 << std::endl;

        std::cout << "\nАрифметические операции:" << std::endl;

        Fraction sum = f1 + f2;
        std::cout << f1 << " + " << f2 << " = " << sum << " (";
        sum.printFraction();
        std::cout << ")" << std::endl;

        Fraction diff = f1 - f2;
        std::cout << f1 << " - " << f2 << " = " << diff << " (";
        diff.printFraction();
        std::cout << ")" << std::endl;

        Fraction prod = f1 * f2;
        std::cout << f1 << " * " << f2 << " = " << prod << " (";
        prod.printFraction();
        std::cout << ")" << std::endl;

        Fraction quot = f1 / f2;
        std::cout << f1 << " / " << f2 << " = " << quot << " (";
        quot.printFraction();
        std::cout << ")" << std::endl;

        std::cout << "\nОперации сравнения:" << std::endl;
        std::cout << f1 << " < " << f2 << " = " << (f1 < f2 ? "true" : "false") << std::endl;
        std::cout << f1 << " > " << f2 << " = " << (f1 > f2 ? "true" : "false") << std::endl;
        std::cout << f1 << " == " << f2 << " = " << (f1 == f2 ? "true" : "false") << std::endl;

        std::cout << "\nСоставные операции:" << std::endl;
        Fraction f4 = f1;
        std::cout << "f4 = " << f4 << std::endl;
        f4 += f2;
        std::cout << "f4 += f2 = " << f4 << std::endl;

        std::cout << "\nВвод дроби (в формате числитель/знаменатель): ";
        Fraction f5;
        std::cin >> f5;
        std::cout << "Вы ввели: " << f5 << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}