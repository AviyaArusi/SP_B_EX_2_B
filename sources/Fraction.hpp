#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

using namespace std;
namespace ariel
{

    class Fraction 
    {
    private:
        int numerator;
        int denominator;
        Fraction reduce();


    public:
        // Constructors
        Fraction();
        Fraction(int, int);
        Fraction(float);

        //Get & Set
        int get_numerator() const;
        int get_denominator() const;
        void set_numerator(int);
        void set_denominator(int);

        // Overloaded operators for arithmetic operations
        Fraction operator+(const Fraction&) const;
        Fraction operator-(const Fraction&) const;
        Fraction operator*(const Fraction&) const;
        Fraction operator/(const Fraction&) const;

        // Overloaded comparison operators
        bool operator==(const Fraction&) const;
        bool operator!=(const Fraction&) const;
        bool operator>(const Fraction&) const;
        bool operator<(const Fraction&) const;
        bool operator>=(const Fraction&) const;
        bool operator<=(const Fraction&) const;

        // Overloaded ++ and -- operators
        Fraction& operator++();
        const Fraction operator++(int);
        Fraction& operator--();
        const Fraction operator--(int);

        // Overloaded << and >> operators
        friend std::ostream& operator<<(std::ostream&, const Fraction& );
        friend std::istream& operator>>(std::istream&, Fraction& );

        // Friend functions
        friend Fraction operator+(const Fraction& fraction, const float& value);
        friend Fraction operator+(const float&, const Fraction&);

        friend Fraction operator-(const Fraction& fraction, const float& value);
        friend Fraction operator-(const float&, const Fraction&);

        friend Fraction operator*(const Fraction& fraction, const float& value);
        friend Fraction operator*(const float&, const Fraction&);

        friend Fraction operator/(const Fraction& fraction, const float& value);
        friend Fraction operator/(const float&, const Fraction&);

        friend bool operator==(const Fraction&, const float&);
        friend bool operator==(const float&, const Fraction&);

        friend bool operator!=(const Fraction&, const float&);
        friend bool operator!=(const float&, const Fraction&);

        friend bool operator>(const Fraction&, const float&);
        friend bool operator>(const float&, const Fraction&);

        friend bool operator<(const Fraction&, const float&);
        friend bool operator<(const float&, const Fraction&);

        friend bool operator>=(const Fraction&, const float&);
        friend bool operator>=(const float&, const Fraction&);

        friend bool operator<=(const Fraction&, const float&);
        friend bool operator<=(const float&, const Fraction&);

    };
}

#endif // FRACTION_HPP

