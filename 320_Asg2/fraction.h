#pragma once

#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <ctype.h>
using namespace std;

class Fraction {
private:
    int num;
    int den;
public:
    Fraction();
    Fraction(int);
    Fraction(int, int);
    int numerator() const;
    int denominator() const;
    void reduce(int &, int &);
    int gcd(int, int);

    Fraction &operator+=(const Fraction &right);
    Fraction &operator-();
    Fraction &operator++();
    Fraction operator++(int);

friend Fraction operator+(const Fraction &left, const Fraction &right);
friend Fraction operator-(const Fraction &left, const Fraction &right);

friend Fraction operator*(const Fraction &left, const Fraction &right);
friend Fraction operator/(const Fraction &left, const Fraction &right);

friend bool operator==(const Fraction &left, const Fraction &right);
friend bool operator!=(const Fraction &left, const Fraction &right);

friend bool operator>(const Fraction &left, const Fraction &right);
friend bool operator>=(const Fraction &left, const Fraction &right);

friend bool operator<(const Fraction &left, const Fraction &right);
friend bool operator<=(const Fraction &left, const Fraction &right);

friend ostream &operator<<(ostream &out, const Fraction &value);
friend istream &operator>>(istream &in, Fraction &value);
};

class FractionException {
public:
    FractionException(const string &message);
    string &what();
private:
    string message;
};
