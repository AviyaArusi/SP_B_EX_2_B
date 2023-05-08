#include "Fraction.hpp"

using namespace std;
namespace ariel
{
    // Constructors
    Fraction::Fraction() : numerator(0), denominator(1) {}

    Fraction::Fraction(int num, int den) : numerator(num), denominator(den)
    {
        if (den == 0)
        {
            //            throw runtime_error("Can't divide by zero!\n");
            throw invalid_argument("denominator can't be 0 !\n");
        }
        reduce();
    }
    Fraction::Fraction(float new_float) : numerator(static_cast<int>(new_float * 1000)), denominator(1000)
    {
        if (new_float == 0)
        {
            //            numerator = 0;
            //            denominator = 1;
        }
        else
        {
            reduce();
        }
    }

    Fraction::Fraction(const Fraction &other) : numerator(other.getNumerator()), denominator(other.getDenominator()) {}
    Fraction::Fraction(Fraction &&other) noexcept : numerator(other.getNumerator()), denominator(other.getDenominator()) {}

    Fraction &Fraction::operator=(const Fraction &other)
    {
        numerator = other.getNumerator();
        denominator = other.getDenominator();
        return (*this);
    }
    Fraction &Fraction::operator=(Fraction &&other) noexcept
    {
        numerator = other.getNumerator();
        denominator = other.getDenominator();
        return (*this);
    }

    // Get & Set
    int Fraction::getNumerator() const { return numerator; }
    int Fraction::getDenominator() const { return denominator; }
    void Fraction::setNumerator(int num) { numerator = num; }
    void Fraction::setDenominator(int den)
    {
        if (den == 0)
        {
            throw runtime_error("Denominator can't be zero!\n");
            //            throw invalid_argument("Denominator can't be zero!\n");
        }
        denominator = den;
    }

    // Overloaded operators for arithmetic operations
    const Fraction operator+(const Fraction &frac1, const Fraction &frac2)
    {
        //         My version!
        int lcm = abs((frac1.getDenominator() * frac2.getDenominator()) / __gcd(frac1.getDenominator() , frac2.getDenominator()));
        int num1 = frac1.getNumerator() * (lcm / frac1.getDenominator());
        int num2 = frac2.getNumerator() * (lcm / frac2.getDenominator());
        overFlow(num1, num2, '+');
        int num = num1+num2;
        return Fraction(num, lcm);
    }

    const Fraction operator-(const Fraction &frac1, const Fraction &frac2)
    {
        int lcm = abs((frac1.getDenominator() * frac2.getDenominator()) / __gcd(frac1.getDenominator() , frac2.getDenominator()));
        int num1 = frac1.getNumerator() * (lcm / frac1.getDenominator());
        int num2 = frac2.getNumerator() * (lcm / frac2.getDenominator());
        overFlow(num1, num2, '-');
        int num = num1-num2;
        return Fraction(num, lcm);
    }

    const Fraction operator*(const Fraction &frac1, const Fraction &frac2)
    {
        overFlow(frac1.getNumerator(), frac2.getNumerator(), '*');
        overFlow(frac1.getDenominator(), frac2.getDenominator(), '*');
        int num = frac1.getNumerator() * frac2.getNumerator();
        int den = frac1.getDenominator() * frac2.getDenominator();
        return Fraction(num, den);
    }

    const Fraction operator/(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac2.getNumerator() == 0)
        {
            throw runtime_error("Can't divide by zero!\n");
        }
        overFlow(frac1.getNumerator(), frac2.getDenominator(), '*');
        overFlow(frac1.getDenominator(), frac2.getNumerator(), '*');
        int num = frac1.getNumerator() * frac2.getDenominator();
        int den = frac1.getDenominator() * frac2.getNumerator();
        return Fraction(num, den);
    }

    // Overloaded comparison operators
    bool operator==(const Fraction &frac1, const Fraction &frac2)
    {
        return (frac1.getNumerator() == frac2.getNumerator()) && (frac1.getDenominator() == frac2.getDenominator());
    }

    bool operator!=(const Fraction &frac1, const Fraction &frac2)
    {
        return !(frac1 == frac2);
    }

    bool operator>(const Fraction &frac1, const Fraction &frac2)
    {
        return (frac1.getNumerator() * frac2.getDenominator()) > (frac2.getNumerator() * frac1.getDenominator());
    }

    bool operator<(const Fraction &frac1, const Fraction &frac2)
    {
        return (frac1.getNumerator() * frac2.getDenominator()) < (frac2.getNumerator() * frac1.getDenominator());
    }

    bool operator>=(const Fraction &frac1, const Fraction &frac2)
    {
        return !(frac1 < frac2);
    }

    bool operator<=(const Fraction &frac1, const Fraction &frac2)
    {
        return !(frac1 > frac2);
    }

    // Overloaded ++ and -- operators
    Fraction &Fraction::operator++()
    {
        numerator += denominator;
        return *this;
    }
    const Fraction Fraction::operator++(int)
    {
        Fraction temp = (*this);
        numerator += denominator;
        return temp;
    }

    Fraction &Fraction::operator--()
    {
        numerator -= denominator;
        return *this;
    }

    const Fraction Fraction::operator--(int)
    {
        Fraction temp = (*this);
        numerator -= denominator;
        return temp;
    }

    // Overloaded << and >> operators
    ostream &operator<<(ostream &os, const Fraction &fraction)
    {
        os << "" << fraction.numerator << '/' << fraction.denominator << "";
        return os;
    }

    istream &operator>>(istream &is, Fraction &fraction)
    {
        //        if (!valid_is(is&))
        //        {
        //            throw invalid_argument("Invalid input stream!\n");
        //        }
        is >> fraction.numerator >> fraction.denominator;
        if (is.fail())
        {
            throw runtime_error("Invalid input stream!\n");
        }

        if (fraction.denominator == 0)
        {
            throw runtime_error("Denominator can't be zero!\n");
        }
        // Make friend function reduce()
        int gcd = abs(__gcd(fraction.getNumerator(), fraction.getDenominator()));
        fraction.setNumerator(fraction.getNumerator() / gcd);
        fraction.setDenominator(fraction.getDenominator() / gcd);

        if (fraction.getDenominator() < 0)
        {
            fraction.setDenominator(fraction.getDenominator() * -1);
            fraction.setNumerator(fraction.getNumerator() * -1);
        }
        return is;
    }

    // Helper function to reduce the fraction to its lowest terms
    void Fraction::reduce()
    {
        int gcd = abs(__gcd(numerator, denominator));
        numerator = numerator / gcd;
        denominator = denominator / gcd;
        if (denominator < 0)
        {
            denominator *= -1;
            numerator *= -1;
        }
    }

    void overFlow(int num1, int num2, char opertor)
    {
        int max_int = numeric_limits<int>::max();
        int min_int = numeric_limits<int>::min();
        int den = 0;
        switch (opertor)
        {
        case '+':
            if ((num2 > 0 && num1 > (max_int - num2)) || (num2 < 0 && num1 < (min_int - num2)))
            {
                throw overflow_error("Addition overflow");
            }
            break;
        case '-':
            if ((num2 < 0 && num1 > max_int + num2) || (num2 > 0 && num1 < min_int + num2))
            {
                throw overflow_error("Subtraction overflow");
            }
            break;
        case '*':
            if ((num2 > 0 && num1 > max_int / num2) || (num2 < 0 && num1 < max_int / num2))
            {
                throw overflow_error("Multiplication overflow");
            }
            break;
        }
    }

}
