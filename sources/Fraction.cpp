#include "Fraction.hpp"

// Bdika!

namespace ariel
{
    // Constructors
    Fraction::Fraction() : numerator(0), denominator(1) {}
    Fraction::Fraction(int num, int den) //: numerator(num), denominator(den)
    {
        if(den == 0)
        {
            throw invalid_argument("denominator can't be 0 !");
        }
        int gcd = abs(__gcd(num, den));
        numerator = num / gcd;
        denominator = den / gcd;
    }
    Fraction::Fraction(float new_float) : numerator(0), denominator(1) //***************************
    {
        if(new_float == 0)
        {
            throw invalid_argument("denominator can't be 0 !");
        }
        int g = new_float*1000;
//        int gcd = __gcd();
        int num;
        int den;
    }
//    Fraction::Fraction(const Fraction& other) : numerator(other.get_numerator()), denominator(other.denominator) {}
//    Fraction::Fraction(Fraction&& other) noexcept : numerator(0), denominator(1) {}
//    Fraction &Fraction::operator=(const Fraction& other) { return *this; }
//    Fraction &Fraction::operator=(Fraction&& other) noexcept { return *this; }

    // Get & Set
    int Fraction::get_numerator() const { return numerator; }
    int Fraction::get_denominator() const { return denominator; }
    void Fraction::set_numerator(int num) { numerator = num; }
    void Fraction::set_denominator(int den)
    {
        if (den == 0)
        {
            throw invalid_argument("Denominator can't be zero!");
        }
        denominator = den;
    }

    // Overloaded operators for arithmetic operations
    Fraction Fraction::operator+(const Fraction& other) const
    {
        int num = numerator * other.denominator + other.numerator * denominator;
        int den = denominator * other.denominator;
        return Fraction(num, den).reduce();
    }

    Fraction Fraction::operator-(const Fraction& other) const
    {
        int num = numerator * other.denominator - other.numerator * denominator;
        int den = denominator * other.denominator;
        return Fraction(num, den).reduce();
    }

    Fraction Fraction::operator*(const Fraction& other) const
    {
        int num = numerator * other.numerator;
        int den = denominator * other.denominator;
        return Fraction(num, den).reduce();
    }

    Fraction Fraction::operator/(const Fraction& other) const
    {
        int num = numerator * other.denominator;
        int den = denominator * other.numerator;
        return Fraction(num, den).reduce();
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
        os << " " << fraction.numerator << '/' << fraction.denominator << " ";
        return os;
    }

    istream& operator>>(istream& is, Fraction& fraction)
    {
        is >> fraction.numerator >> fraction.denominator;
        return is;
    }

    // Friend functions
    Fraction operator+(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return fraction + f;
    }
    Fraction operator+(const float& value, const Fraction& fraction) { return fraction+value; }

    Fraction operator-(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return fraction - f;
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
        return fraction * f;
    }
    Fraction operator*(const float& value, const Fraction& fraction){ return fraction*value; }

    Fraction operator/(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return fraction/f;
    }
    Fraction operator/(const float& value, const Fraction& fraction)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return f/fraction;
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
        return fraction != f;
    }
    bool operator!=(const float& value, const Fraction& fraction) { return fraction != value; }

    bool operator>(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return fraction > f;
    }
    bool operator>(const float& value, const Fraction& fraction)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return f > fraction;
    }

    bool operator<(const Fraction& fraction, const float& value)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return fraction < f;
    }
    bool operator<(const float& value, const Fraction& fraction)
    {
        // Convert float value to a fraction
        Fraction f(value);
        // Add the fractions
        return f < fraction;
    }

    bool operator>=(const Fraction& fraction, const float& value) { return !(fraction < value); }
    bool operator>=(const float& value, const Fraction& fraction) { return !(value < fraction); }

    bool operator<=(const Fraction& fraction, const float& value) { return !(fraction > value); }
    bool operator<=(const float& value, const Fraction& fraction) { return !(value < fraction); }

    // Helper function to reduce the fraction to its lowest terms
    Fraction Fraction::reduce()
    {
        int gcd = abs(__gcd(numerator, denominator));
        int num = numerator / gcd;
        int den = denominator / gcd;
        return Fraction(num, den);
    }


}

//#######################################################################################################################

//
//#include "Fraction.hpp"
//#include <iostream>
//#include <numeric> // for std::gcd
//
//namespace ariel
//{
//    // Constructors
//    Fraction::Fraction() : numerator(0), denominator(1) {}
//
//    Fraction::Fraction(int num, int den) : numerator(num), denominator(den)
//    {
//        if(den == 0)
//        {
//            throw invalid_argument("denominator can't be 0 !");
//        }
//    }
//
////    Fraction::Fraction(double frac)
////    {
////        int sign = (x < 0) ? -1 : 1;
////        x = abs(x);
////        int whole = static_cast<int>(x);
////        double fractional = x - whole;
////
////        int powerOf10 = pow(10, 6); // 6 decimal places
////
////        int num = whole * powerOf10 + round(fractional * powerOf10);
////        int div = gcd(num, powerOf10);
////
////        numerator = sign * (num / div);
////        denominator = powerOf10 / div;
////    }
//
//
////    Fraction::Fraction(const Fraction& copy) : numerator(copy.numerator), denominator(copy.denominator) {}
//
//    // Destructor
////    Fraction::~Fraction(){}
//
//    // Overloaded operators for arithmetic operations
//    Fraction Fraction::operator+(const Fraction& other) const
//    {
//        int num = numerator * other.denominator + other.numerator * denominator;
//        int den = denominator * other.denominator;
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction Fraction::operator-(const Fraction& other) const
//    {
//        int num = numerator * other.denominator - other.numerator * denominator;
//        int den = denominator * other.denominator;
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction Fraction::operator*(const Fraction& other) const
//    {
//        int num = numerator * other.numerator;
//        int den = denominator * other.denominator;
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction Fraction::operator/(const Fraction& other) const
//    {
//        int num = numerator * other.denominator;
//        int den = denominator * other.numerator;
//        return Fraction(num, den).reduce();
//    }
//
//    // Overloaded comparison operators
//    bool Fraction::operator==(const Fraction& other) const
//    {
//        return numerator == other.numerator && denominator == other.denominator;
//    }
//
//    bool Fraction::operator!=(const Fraction& other) const
//    {
//        return !(*this == other);
//    }
//
//    bool Fraction::operator>(const Fraction& other) const
//    {
//        return (numerator * other.denominator) > (other.numerator * denominator);
//    }
//
//    bool Fraction::operator>(const double& other) const
//    {
//        return (numerator * other) > (1 * denominator);
//    }
//
//    bool Fraction::operator<(const Fraction& other) const
//    {
//        return (numerator * other.denominator) < (other.numerator * denominator);
//    }
//
//    bool Fraction::operator>=(const Fraction& other) const
//    {
//        return !(*this < other);
//    }
//
//    bool Fraction::operator<=(const Fraction& other) const
//    {
//        return !(*this > other);
//    }
//
//    // Overloaded ++ and -- operators
//    Fraction& Fraction::operator++()
//    {
//        numerator += denominator;
//        return *this;
//    }
//
//    Fraction Fraction::operator++(int)
//    {
//        Fraction temp = *this;
//        numerator += denominator;
//        return temp;
//    }
//
//    Fraction& Fraction::operator--()
//    {
//        numerator -= denominator;
//        return *this;
//    }
//
//    Fraction Fraction::operator--(int)
//    {
//        Fraction temp = *this;
//        numerator -= denominator;
//        return temp;
//    }
//
//    // Overloaded << and >> operators
//    ostream& operator<<(ostream& os, const Fraction& fraction)
//    {
//        os << " " << fraction.numerator << '/' << fraction.denominator << " ";
//        return os;
//    }
//
//    istream& operator>>(istream& is, Fraction& fraction)
//    {
//        is >> fraction.numerator >> fraction.denominator;
//        return is;
//    }
//
//    // Helper function to reduce the fraction to its lowest terms
//    Fraction Fraction::reduce()
//    {
//        int gcd = abs(std::gcd(numerator, denominator));
//        int num = numerator / gcd;
//        int den = denominator / gcd;
//        return Fraction(num, den);
//    }
//
//    // Overloaded operators for arithmetic operations with float
//
////    Fraction &Fraction::operator=(const Fraction& fraction)
////    {
////        numerator = fraction.numerator;
////        denominator = fraction.denominator;
////        return *this;
////    }
//
//    Fraction operator+(const Fraction& fraction, double value)
//    {
//        int num = static_cast<int>(value * fraction.denominator) + fraction.numerator;
//        int den = fraction.denominator;
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction operator+(double value, const Fraction& fraction)
//    {
//        int num = static_cast<int>(value * fraction.denominator) + fraction.numerator;
//        int den = fraction.denominator;
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction operator-(const Fraction& fraction, double value)
//    {
//        int num = fraction.numerator - static_cast<int>(value * fraction.denominator);
//        int den = fraction.denominator;
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction operator-(double value, const Fraction& fraction)
//    {
//        int num = fraction.numerator - static_cast<int>(value * fraction.denominator);
//        int den = fraction.denominator;
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction operator*(const Fraction& fraction, double value)
//    {
//        int num = static_cast<int>(value * fraction.numerator);
//        int den = fraction.denominator;
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction operator*(double value, const Fraction& fraction)
//    {
//        int num = static_cast<int>(value * fraction.numerator);
//        int den = fraction.denominator;
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction operator/(const Fraction& fraction, double value)
//    {
//        int num = fraction.numerator;
//        int den = static_cast<int>(fraction.denominator * value);
//        return Fraction(num, den).reduce();
//    }
//
//    Fraction operator/(double value, const Fraction& fraction)
//    {
//        int num = fraction.numerator;
//        int den = static_cast<int>(fraction.denominator * value);
//        return Fraction(num, den).reduce();
//    }
//
//}
