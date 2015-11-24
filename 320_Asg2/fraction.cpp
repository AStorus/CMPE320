#include "fraction.h"

using namespace std;

//No parameter constructor,sets numerator to 0 and denominator to 1
Fraction::Fraction() : num(0), den(1) { }

Fraction::Fraction(int n) : num(n), den(1) {}

Fraction::Fraction(int n, int d) {  

    //Check for divide by 0
    if(d == 0)
        throw FractionException("Cannot divide by 0");

    //if the numerator is 0, disregard what d is set to and set d to 0
    if(n == 0) {
        num = 0;
        den = 1;
    }
    else
    {
        //This takes care of the numerator sign convention
        //Store the original values of the numerator and denominator
        int top, bottom;
        top = n;
        bottom = d;
        if(n < 0)
            n *= -1;
        if(d < 0)
            d *= -1;
        reduce(n, d);

        //If only one of the top or bottom is negative, make only the numerator negative
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
    //Using the gcd algorithm supplied by the assignment description
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

//The following operators are all handeled by considering the numerator and denominator seperately
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
    if((left.numerator() != right.numerator()) ||
            (left.denominator() != right.denominator()))
            return true;
    else
            return false;
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
    int n, d;
    n = num * right.den + right.num * den;
    d = den * right.den;
    reduce(n, d);
    num = n;
    den = d;
    return *this;
}

ostream &operator<<(ostream &out, const Fraction &value) {
    out << value.num << "/" << value.den << endl;
    return out;
}

istream &operator>>(istream &in, Fraction &f) {
    char c;
    int n, d;
    //set numerator
    in >> n;
    f.num = n;
    f.den = 1;

    //check for slash
    c = in.peek();
    if(c == '/')
        in >> c;
    else
        return in;
    //check denominator
    c = in.peek();
    if(c == '0')
        throw FractionException("Cannot divide by 0");
    else if(isdigit(c)) {
        in >> d;
        f.reduce(n, d);
        f.num = n;
        f.den = d;
    }
    return in;
}

FractionException::FractionException(const string &message) : message(message) {}

string &FractionException::what() {
    return message;
}

