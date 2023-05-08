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
    Fraction::Fraction(const Fraction &other) : numerator(other.getNumerator()), denominator(other.getDenominator()) {}

    /**
     * Move constructor, creates a new fraction by moving data from another fraction
    */
    Fraction::Fraction(Fraction &&other) noexcept : numerator(other.getNumerator()), denominator(other.getDenominator()) {}

    /**
     * Copy assignment operator, assigns a new value to an existing fraction
    */
    Fraction &Fraction::operator=(const Fraction &other)
    {
        numerator = other.getNumerator();
        denominator = other.getDenominator();
        return (*this);
    }

    /**
     * Move assignment operator, assigns a new value to an existing fraction by moving data from another fraction
    */
    Fraction &Fraction::operator=(Fraction &&other) noexcept
    {
        numerator = other.getNumerator();
        denominator = other.getDenominator();
        return (*this);
    }

    // Get & Set
    int Fraction::getNumerator() const { return numerator; }
    int Fraction::getDenominator() const { return denominator; }
    void Fraction::setNumerator(int num)
    {
        numerator = num;
        reduce(); // Reduce the fraction to its lowest terms
    }
    void Fraction::setDenominator(int den)
    {
        if (den == 0)
        {
            throw runtime_error("Denominator can't be zero!\n");
        }
        denominator = den;
        reduce(); // Reduce the fraction to its lowest terms
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

    // Friend operators for arithmetic operations,
    // the functions can handle with casting case. 
    const Fraction operator+(const Fraction &frac1, const Fraction &frac2)
    {
        int lcm = abs((frac1.getDenominator() * frac2.getDenominator()) / __gcd(frac1.getDenominator(), frac2.getDenominator()));
        int num1 = frac1.getNumerator() * (lcm / frac1.getDenominator());
        int num2 = frac2.getNumerator() * (lcm / frac2.getDenominator());
        overFlow(num1, num2, '+');
        int num = num1 + num2;
        return Fraction(num, lcm);
    }

    const Fraction operator-(const Fraction &frac1, const Fraction &frac2)
    {
        int lcm = abs((frac1.getDenominator() * frac2.getDenominator()) / __gcd(frac1.getDenominator(), frac2.getDenominator()));
        int num1 = frac1.getNumerator() * (lcm / frac1.getDenominator());
        int num2 = frac2.getNumerator() * (lcm / frac2.getDenominator());
        overFlow(num1, num2, '-');
        int num = num1 - num2;
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

        if (fraction.denominator == 0)
        {
            throw runtime_error("Denominator can't be zero!\n");
        }
        // Make sure the fraction is reduce;
        int gcd = abs(__gcd(num, den));
        num = (num / gcd);
        den = (den / gcd);
        if (den < 0)
        {
            den *= -1;
            num *= -1;
        }
        fraction.setNumerator(num);
        fraction.setDenominator(den);
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

    void overFlow2(int num1, int num2, char opertor)
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


     void overFlow(int num1, int num2, char opertor)
    {
        int max_int = numeric_limits<int>::max();
        int min_int = numeric_limits<int>::min();
        int den = 0;
        bool err = false;
        switch (opertor)
        {
        case '+':
            if (num2 > 0)
            {
                if(num1 > (max_int-num2) ){err = true;}
            }
            else if(num2 < 0)
            {
                if(num1 < (min_int-num2) ){err = true;}
            }
            if (err)
            {
                throw overflow_error("Addition overflow");
            }
            break;

        case '-':
            if (num2 < 0)
            {
                if(num1 > (max_int+num2) ){err = true;}
            }
            else if (num2 > 0)
            {
                if(num1 < (min_int+num2) ){err = true;}
            }
            if (err)
            {
                throw overflow_error("Addition overflow");
            }
            break;

        case '*':
              if (num2 > 0)
            {
                if(num1 > (max_int/num2) ){err = true;}
            }
            else if (num2 < 0)
            {
                if(num1 < (max_int/num2)){err= true;}
            }
            if (err)
            {
                throw overflow_error("Addition overflow");
            }
            break;
        }
    }


}
