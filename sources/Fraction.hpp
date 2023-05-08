#pragma once

#include <iostream>
//***************
#include <limits>


namespace ariel
{

    class Fraction 
    {
    private:
        int numerator;
        int denominator;
        void reduce();


    public:
        // Constructors
       Fraction();
        // Fraction(int num = 0, int den = 1);
        Fraction(int num, int den);
        Fraction(float);

        Fraction(const Fraction& other);
        Fraction(Fraction&& other) noexcept;
        
        //destructor
        ~Fraction() = default;

        Fraction& operator=(const Fraction& other);
        Fraction& operator=(Fraction&& other) noexcept;

        bool valid_is(std::istream&) const;

        //Get & Set
        int getNumerator() const;
        int getDenominator() const;
        void setNumerator(int);
        void setDenominator(int);

        // Overloaded operators for arithmetic operations
        const friend Fraction operator+(const Fraction&,const Fraction&);
        const friend Fraction operator-(const Fraction&,const Fraction&);
        const friend Fraction operator*(const Fraction&,const Fraction&);
        const friend Fraction operator/(const Fraction&,const Fraction&);

        // Overloaded comparison operators
        friend bool operator==(const Fraction&,const Fraction&);
        friend bool operator!=(const Fraction&,const Fraction&);
        friend bool operator>(const Fraction&,const Fraction&);
        friend bool operator<(const Fraction&,const Fraction&);
        friend bool operator>=(const Fraction&,const Fraction&);
        friend bool operator<=(const Fraction&,const Fraction&);

        // Overloaded ++ and -- operators
        Fraction& operator++();
        const Fraction operator++(int);
        Fraction& operator--();
        const Fraction operator--(int);

        // Overloaded << and >> operators
        friend std::ostream& operator<<(std::ostream&, const Fraction& );
        friend std::istream& operator>>(std::istream&, Fraction&);
    };
    
    void overFlow(int, int, char);

}

