#pragma once

#include <iostream>
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
        Fraction(int num, int den);
        Fraction(float);

        Fraction(const Fraction& other);
        Fraction(Fraction&& other) noexcept;
        
        //destructor
        ~Fraction() = default;

        Fraction& operator=(const Fraction& other);
        Fraction& operator=(Fraction&& other) noexcept;

        //Get & Set
        int getNumerator() const;
        int getDenominator() const;
        
        // Overloaded ++ and -- operators
        Fraction& operator++();
        const Fraction operator++(int);
        Fraction& operator--();
        const Fraction operator--(int);

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

        // Overloaded << and >> operators
        friend std::ostream& operator<<(std::ostream&, const Fraction& );
        friend std::istream& operator>>(std::istream&, Fraction&);

    };
    
    void overFlow(long long, long long, char);
    int lcm1(long long, long long);
}

