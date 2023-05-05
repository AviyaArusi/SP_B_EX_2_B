#include "Fraction.hpp"

using namespace std;
namespace ariel
{
    // Constructors
//    Fraction::Fraction() : numerator(0), denominator(1) {}
    Fraction::Fraction(int num, int den) : numerator(num), denominator(den)
    {
        if(den == 0)
        {
//            throw runtime_error("Can't divide by zero!\n");
            throw invalid_argument("denominator can't be 0 !\n");
        }
//        numerator = num;
//        denominator = den;
        reduce();
    }
    Fraction::Fraction(float new_float) : numerator(static_cast<int>(new_float * 1000)), denominator(1000)
    {
        if(new_float == 0)
        {
//            numerator = 0;
//            denominator = 1;
        }
        else
        {
            reduce();
        }
    }
//    Fraction::Fraction(const Fraction& other) : numerator(other.get_numerator()), denominator(other.denominator) {}
//    Fraction::Fraction(Fraction&& other) noexcept : numerator(0), denominator(1) {}
//    Fraction &Fraction::operator=(const Fraction& other) { return *this; }
//    Fraction &Fraction::operator=(Fraction&& other) noexcept { return *this; }

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
    Fraction Fraction::operator+(const Fraction& other) const
    {
        // M version!
//        int lcm = abs(denominator * other.getDenominator() / __gcd(denominator,other.getDenominator()));
//        int num1 = numerator * (lcm / denominator);
//        int num2 = other.getDenominator() * (lcm / other.getDenominator());
//        return Fraction(overFlow(num1, num2, '+'), lcm);
//         My version!
        int num = numerator * other.denominator + other.numerator * denominator;
        int den = denominator * other.denominator;
        return Fraction(num, den);
    }

    Fraction Fraction::operator-(const Fraction& other) const
    {
        int num = numerator * other.denominator - other.numerator * denominator;
        int den = denominator * other.denominator;
        return Fraction(num, den);
    }

    Fraction Fraction::operator*(const Fraction& other) const
    {
        int num = numerator * other.numerator;
        int den = denominator * other.denominator;
        return Fraction(num, den);
    }

    Fraction Fraction::operator/(const Fraction& other) const
    {
        if(other.getNumerator() == 0) { throw runtime_error("Can't divide by zero!\n"); }
        int num = numerator * other.denominator;
        int den = denominator * other.numerator;
        return Fraction(num, den);
    }

    // Overloaded comparison operators
    bool Fraction::operator==(const Fraction& other) const
    {
        return (numerator == other.numerator) && (denominator == other.denominator);
    }

    bool Fraction::operator!=(const Fraction& other) const
    {
        return !(*this == other);
    }

    bool Fraction::operator>(const Fraction& other) const
    {
        return (numerator * other.denominator) > (other.numerator * denominator);
    }

    bool Fraction::operator<(const Fraction& other) const
    {
        return (numerator * other.denominator) < (other.numerator * denominator);
    }

    bool Fraction::operator>=(const Fraction& other) const
    {
        return !(*this < other);
    }

    bool Fraction::operator<=(const Fraction& other) const
    {
        return !(*this > other);
    }

    // Overloaded ++ and -- operators
    Fraction& Fraction::operator++()
    {
        numerator += denominator;
        return *this;
    }
    const Fraction Fraction::operator++(int)
    {
        Fraction temp = *this;
        numerator += denominator;
        return temp;
    }

    Fraction& Fraction::operator--()
    {
        numerator -= denominator;
        return *this;
    }

    const Fraction Fraction::operator--(int)
    {
        Fraction temp = *this;
        numerator -= denominator;
        return temp;
    }

    // Overloaded << and >> operators
    ostream& operator<<(ostream& os, const Fraction& fraction)
    {
        os << "" << fraction.numerator << '/' << fraction.denominator << "";
        return os;
    }

    istream& operator>>(istream& is, Fraction& fraction)
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
            fraction.setDenominator(fraction.getDenominator()*-1);
            fraction.setNumerator(fraction.getNumerator()*-1);
        }
        return is;
    }

    // Friend functions
    Fraction operator+(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (fraction + f);
    }
    Fraction operator+(const float& value, const Fraction& fraction) { return (fraction+value); }

    Fraction operator-(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (fraction - f);
    }
    Fraction operator-(const float& value, const Fraction& fraction)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return f - fraction;
    }

    Fraction operator*(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (fraction * f);
    }
    Fraction operator*(const float& value, const Fraction& fraction){ return (fraction*value); }

    Fraction operator/(const Fraction& fraction, const float& value)
    {
        if(value == 0) { throw runtime_error("Can't divide by zero!\n"); }

        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (fraction/f);
    }
    Fraction operator/(const float& value, const Fraction& fraction)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (f/fraction);
    }

    bool operator==(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return fraction == f;
    }
    bool operator==(const float& value, const Fraction& fraction) { return fraction == value; }

    bool operator!=(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (fraction != f);
    }
    bool operator!=(const float& value, const Fraction& fraction) { return (fraction != value); }

    bool operator>(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (fraction > f);
    }
    bool operator>(const float& value, const Fraction& fraction)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (f > fraction);
    }

    bool operator<(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (fraction < f);
    }
    bool operator<(const float& value, const Fraction& fraction)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return (f < fraction);
    }

    bool operator>=(const Fraction& fraction, const float& value) { return !(fraction < value); }
    bool operator>=(const float& value, const Fraction& fraction) { return !(value < fraction); }

    bool operator<=(const Fraction& fraction, const float& value) { return !(fraction > value); }
    bool operator<=(const float& value, const Fraction& fraction) { return !(value >fraction); }

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

    int Fraction::overFlow(int num1, int num2, char opertor) const
    {
        int den = 0;
        switch (opertor)
        {
            case '+':
                if ((num2 > 0 && num1 > (max_int - num2)) || (num2 < 0 && num1 < (min_int - num2)))
                {
                    throw overflow_error("Addition overflow");
                }

                den = (num1 + num2);
                break;
            case '-':
                if ((num2 < 0 && num1 > max_int + num2) || (num2 > 0 && num1 < min_int + num2))
                {
                    throw overflow_error("Subtraction overflow");
                }

                den = (num1 - num2);
                break;
            case '*':
                if ((num2 > 0 && num1 > max_int / num2) || (num2 < 0 && num1 < max_int / num2))
                {
                    throw overflow_error("Multiplication overflow");
                }

                den = (num1 * num2);
                break;
        }

        return den;
    }




}
