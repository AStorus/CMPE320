#include "fraction10103737.h"

using namespace std;

Fraction::Fraction() : num(0), den(1) { }

Fraction::Fraction(int n) : num(n), den(1) {}

Fraction::Fraction(int n, int d) {  

    if(d == 0)
        throw FractionException("Cannot divide by 0");

    if(n == 0) {
        num = 0;
        den = 1;
    }
    else
    {
        int top, bottom;
        top = n;
        bottom = d;
        if(n < 0)
            n *= -1;
        if(d < 0)
            d *= -1;
        reduce(n, d);

        if(!((top < 0) && (bottom < 0))) {
            if((top < 0) || (bottom < 0))
                n *= -1;
        }

        num = n;
        den = d;
    }
}

void Fraction::reduce(int &n, int &d) {
    int g;
    g = gcd(n, d);
    n = n / g;
    d = d / g;
}

int Fraction::gcd(int n, int d) {
    if((d <= n) && (n % d == 0))
        return d;
    else if(d > n)
        return gcd(d, n);
    else
        return gcd(d, n % d);
}

int Fraction::numerator() const{
    int n = num;
    return n;
}

int Fraction::denominator() const{
    return den;
}

Fraction operator+(const Fraction &left, const Fraction &right) {
    int n = left.numerator() * right.denominator() + right.numerator() * left.denominator();
    int d = right.denominator() * left.denominator();
    return Fraction(n, d);
}

Fraction operator-(const Fraction &left, const Fraction &right) {
    int n = left.numerator() * right.denominator() - right.numerator() * left.denominator();
    int d = right.denominator() * left.denominator();
    return Fraction(n, d);
}

Fraction operator*(const Fraction &left, const Fraction &right) {
    int n = left.numerator() * right.numerator();
    int d = left.denominator() * right.denominator();
    return Fraction(n, d);
}

Fraction operator/(const Fraction &left, const Fraction &right) {
    int n = left.numerator() * right.denominator();
    int d = left.denominator() * right.numerator();
    return Fraction(n,d);
}

bool operator==(const Fraction &left, const Fraction &right) {
    if((left.numerator() == right.numerator()) &&
            (left.denominator() == right.denominator()))
        return true;
    else
        return false;
}

bool operator!=(const Fraction &left, const Fraction &right) {
    return !(left == right);

}

bool operator>(const Fraction &left, const Fraction &right) {
    if((float)left.numerator()/left.denominator() > (float)right.numerator()/right.denominator())
        return true;
    else
        return false;
}

bool operator>=(const Fraction &left, const Fraction &right) {
    if((left > right) || (left == right))
        return true;
    else
        return false;
}

bool operator<(const Fraction &left, const Fraction &right) {
    if((float)left.numerator()/left.denominator() < (float)right.numerator()/right.denominator())
        return true;
    else
        return false;
}

bool operator<=(const Fraction &left, const Fraction &right) {
    if((left < right) || (left == right))
        return true;
    else
        return false;
}

Fraction &Fraction::operator-() {
    num *= -1;
    return *this;
}

//Pre increment
Fraction &Fraction::operator++() {
    num += den;
    return *this;
}

//Post increment
Fraction Fraction::operator++(int na) {
    Fraction f(num, den);
    num+= den;
    return f;
}

Fraction &Fraction::operator+=(const Fraction &right) {
    num = num * right.den + right.num * den;
    den = den * right.den;
    return *this;
}

ostream &operator<<(ostream &out, const Fraction &value) {
    out << value.num << "/" << value.den << endl;
    return out;
}

istream &operator>>(istream &in, Fraction &f) {
    //istream a();
    int b;
    in >> f.num >> b >> f.den;
    return in;
}

FractionException::FractionException(const string &message) : message(message) {}

string &FractionException::what() {
    return message;
}

