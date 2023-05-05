#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
//***************
#include <limits>


//using namespace std;

namespace ariel
{

    class Fraction 
    {
    private:
        int numerator;
        int denominator;
        void reduce();

        int overFlow(int, int, char) const;
        static const int max_int = std::numeric_limits<int>::max();
        static const int min_int = std::numeric_limits<int>::min();



    public:
        // Constructors
//        Fraction();
        Fraction(int num = 0, int den = 1);
        Fraction(float);

        bool valid_is(std::istream&) const;

        //Get & Set
        int getNumerator() const;
        int getDenominator() const;
        void setNumerator(int);
        void setDenominator(int);

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

