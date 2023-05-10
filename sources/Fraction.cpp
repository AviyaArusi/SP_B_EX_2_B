#include "Fraction.hpp"

using namespace std;
namespace ariel
{
    // Constructors:

    /**
     * Default constructor, initializes fraction to 0/1.
     */
    Fraction::Fraction() : numerator(0), denominator(1) {}

    /**
     * Constructor to create fraction from numerator and denominator
     */
    Fraction::Fraction(int num, int den) : numerator(num), denominator(den)
    {
        if (den == 0)
        {
            throw invalid_argument("denominator can't be 0 !\n");
        }
        reduce(); // Reduce the fraction to its lowest terms
    }
    /**
     * Constructor to create fraction from float value
     */
    Fraction::Fraction(float new_float) : numerator(static_cast<int>(new_float * 1000)), denominator(1000) { reduce(); }

    /**
     * Copy constructor, creates a new fraction that is a copy of another fraction
    */
    Fraction::Fraction(const Fraction &other) : numerator(other.numerator), denominator(other.denominator) {}

    /**
     * Move constructor, creates a new fraction by moving data from another fraction
    */
    Fraction::Fraction(Fraction &&other) noexcept : numerator(other.numerator), denominator(other.denominator) {}

    /**
     * Copy assignment operator, assigns a new value to an existing fraction
    */
    Fraction &Fraction::operator=(const Fraction &other)
    {
        numerator = other.numerator;
        denominator = other.denominator;
        return (*this);
    }

    /**
     * Move assignment operator, assigns a new value to an existing fraction by moving data from another fraction
    */
    Fraction &Fraction::operator=(Fraction &&other) noexcept
    {
        numerator = other.numerator;
        denominator = other.denominator;
        return (*this);
    }

    // Get & Set
    int Fraction::getNumerator() const { return numerator; }
    int Fraction::getDenominator() const { return denominator; }

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
        return (*this);
    }

    const Fraction Fraction::operator--(int)
    {
        Fraction temp = (*this);
        numerator -= denominator;
        return temp;
    }

    // Friend operators for arithmetic operations,
    // the functions can handle with casting case. 
    const Fraction operator+(const Fraction &frac1, const Fraction &frac2)
    {
        long long lcm = lcm1(frac1.denominator, frac2.denominator);
        long long num1 = frac1.numerator * (lcm / frac1.denominator);
        long long num2 = frac2.numerator * (lcm / frac2.denominator);
        overFlow(num1, num2, '+');
        int num = num1 + num2;
        return Fraction(num, lcm);
    }

    const Fraction operator-(const Fraction &frac1, const Fraction &frac2)
    {
        return frac1 + (-1*frac2);
    }

    const Fraction operator*(const Fraction &frac1, const Fraction &frac2)
    {
        overFlow(frac1.numerator, frac2.numerator, '*');
        overFlow(frac1.denominator, frac2.denominator, '*');
        int num = frac1.numerator * frac2.numerator;
        int den = frac1.denominator * frac2.denominator;
        return Fraction(num, den);
    }

    const Fraction operator/(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac2.numerator == 0)
        {
            throw runtime_error("Can't divide by zero!\n");
        }
        overFlow(frac1.numerator, frac2.denominator, '*');
        overFlow(frac1.denominator, frac2.numerator, '*');
        int num = frac1.numerator * frac2.denominator;
        int den = frac1.denominator * frac2.numerator;
        return Fraction(num, den);
    }

    // Overloaded comparison operators
    bool operator==(const Fraction &frac1, const Fraction &frac2)
    {
        return (frac1.numerator == frac2.numerator) && (frac1.denominator == frac2.denominator);
    }

    bool operator!=(const Fraction &frac1, const Fraction &frac2)
    {
        return !(frac1 == frac2);
    }

    bool operator>(const Fraction &frac1, const Fraction &frac2)
    {
        return (frac1.numerator * frac2.denominator) > (frac2.numerator * frac1.denominator);
    }

    bool operator<(const Fraction &frac1, const Fraction &frac2)
    {
        return (frac1.numerator * frac2.denominator) < (frac2.numerator * frac1.denominator);
    }

    bool operator>=(const Fraction &frac1, const Fraction &frac2)
    {
        return !(frac1 < frac2);
    }

    bool operator<=(const Fraction &frac1, const Fraction &frac2)
    {
        return !(frac1 > frac2);
    }

    // Overloaded << and >> operators
    ostream &operator<<(ostream &os, const Fraction &fraction)
    {
        os << "" << fraction.numerator << '/' << fraction.denominator << "";
        return os;
    }

    istream &operator>>(istream &is, Fraction &fraction)
    {
        int num, den;
        is >> num >> den;
        if (is.fail())
        {
            throw runtime_error("Invalid input stream!\n");
        }

        if (den == 0)
        {
            throw runtime_error("Denominator can't be zero!\n");
        }
        // Make sure the fraction is reduce;
        fraction.numerator = num;
        fraction.denominator = den;
        fraction.reduce();
        return is;
    }

    // Helper function to reduce the fraction to its lowest terms
    void Fraction::reduce()
    {
        int gcd = abs(__gcd(numerator, denominator));
        numerator = (numerator / gcd);
        denominator = (denominator / gcd);
        if (denominator < 0)
        {
            denominator *= -1;
            numerator *= -1;
        }
    }

    void overFlow(long long num1, long long num2, char opertor)
    {
        long long max_int = numeric_limits<int>::max();
        long long min_int = numeric_limits<int>::min();
        bool err = false;
        switch (opertor)
        {
        case '+':
            if ( (num1+num2 > max_int) || (num1+num2 < min_int) )// Check only where num1 in positive.
            {
                err = true;
            }
            break;

        case '-':
            if ( (num1-num2 > max_int) || (num1-num2 < min_int) )// Check only where num1 in positive.
            {
                err = true;
            }
            break;

        case '*':
              if ((num1*num2 > max_int) || (num1*num2 < min_int))
            {
                err = true;
            }
            break;
        }

        if (err){ throw overflow_error("Addition overflow"); }
    }

    int lcm1(long long num1, long long num2)
    {
        long long lcm = abs((num1 * num2) / __gcd(num1, num2));
        return lcm;
    }


}
