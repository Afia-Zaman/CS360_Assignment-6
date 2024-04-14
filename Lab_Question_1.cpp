// 1. Consider class Complex shown as follows. The class enables operations on so-called
// complex numbers. These are numbers of the form realPart + imaginaryPart*i, where i
// has the value ―1
// a. Modify the class to enable input and output of complex numbers via
// overloaded >> and << operators, respectively (you should remove the print
// function from the class).
// b. Overload the multiplication operator to enable multiplication of two complex
// numbers as in algebra.
// c. Overload the == and != operators to allow comparisons of complex numbers.
// // Complex.h
// // Complex class definition.
// #ifndef COMPLEX_H
// #define COMPLEX_H
// class Complex{
// public:
// explicit Complex( double = 0.0, double = 0.0 ); // constructor
// Complex operator+( const Complex & ) const; // addition
// Complex operator-( const Complex & ) const; // subtraction
// void print() const; // output
// private:
// double real; // real part
// double imaginary; // imaginary part
// }; // end class Complex
// #endif
// // Complex.cpp
// // Complex class member-function definitions.
// #include <iostream>
// #include "Complex.h" // Complex class definition
// using namespace std;
// // Constructor
// Complex::Complex( double realPart, double imaginaryPart ):
// real( realPart ),imaginary( imaginaryPart ){
// // empty body
// } // end Complex constructor
// // addition operator
// Complex Complex::operator+( const Complex &operand2 ) const{
// return Complex( real + operand2.real,imaginary +
// operand2.imaginary );
// } // end function operator+
// // subtraction operator
// Complex Complex::operator-( const Complex &operand2 ) const{
// return Complex( real - operand2.real,imaginary - operand2.imaginary );
// } // end function operator-
// // display a Complex object in the form: (a, b)
// void Complex::print() const{
// cout << '(' << real << ", " << imaginary << ')';
// } // end function print
// // main.cpp
// // Complex class test program.
// #include <iostream>
// #include "Complex.h"
// using namespace std;
// int main(void){
// Complex x;
// Complex y( 4.3, 8.2 );
// Complex z( 3.3, 1.1 );
// cout << "x: ";
// x.print();
// cout << "\ny: ";
// y.print();
// cout << "\nz: ";
// z.print();
// x = y + z;
// cout << "\n\nx = y + z:" << endl;
// x.print();
// cout << " = ";
// y.print();
// cout << " + ";
// z.print();
// x = y - z;
// cout << "\n\nx = y - z:" << endl;
// x.print();
// cout << " = ";
// y.print();
// cout << " - ";
// z.print();
// cout << endl;
// } // end main


ANSWER:

Code in Complex.h file-----
https://replit.com/@zamanafia3/CS360LabAssignment6#Ques-1/Complex.h


#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
public:
    explicit Complex(double = 0.0, double = 0.0); // constructor
    Complex operator+(const Complex &) const; // addition
    Complex operator-(const Complex &) const; // subtraction
    Complex operator*(const Complex &) const; // multiplication
    bool operator==(const Complex &) const; // equality comparison
    bool operator!=(const Complex &) const; // inequality comparison

    friend std::ostream &operator<<(std::ostream &, const Complex &);
    friend std::istream &operator>>(std::istream &, Complex &);

private:
    double real; // real part
    double imaginary; // imaginary part
};

#endif

Code in Complex.cpp file-----
https://replit.com/@zamanafia3/CS360LabAssignment6#Ques-1/Complex.cpp
#include "Complex.h"
using namespace std;

// Constructor
Complex::Complex(double realPart, double imaginaryPart) : real(realPart), imaginary(imaginaryPart) {}

// Addition operator
Complex Complex::operator+(const Complex &operand2) const {
    return Complex(real + operand2.real, imaginary + operand2.imaginary);
}

// Subtraction operator
Complex Complex::operator-(const Complex &operand2) const {
    return Complex(real - operand2.real, imaginary - operand2.imaginary);
}

// Overloaded Multiplication operator
Complex Complex::operator*(const Complex &operand2) const {
    return Complex(real * operand2.real - imaginary * operand2.imaginary,
                   real * operand2.imaginary + imaginary * operand2.real);
}

// Overloaded Equality operator
bool Complex::operator==(const Complex &operand2) const {
    return real == operand2.real && imaginary == operand2.imaginary;
}

// Overloaded Inequality operator
bool Complex::operator!=(const Complex &operand2) const {
    return !(*this == operand2);
}

// Insertion operator for output
std::ostream &operator<<(std::ostream &output, const Complex &c) {
    output << '(' << c.real << ", " << c.imaginary << ')';
    return output;
}

// Extraction operator for input
std::istream &operator>>(std::istream &input, Complex &c) {
    input >> c.real >> c.imaginary;
    return input;
}

Code in main.cpp file-------
https://replit.com/@zamanafia3/CS360LabAssignment6#Ques-1/main.cpp
#include <iostream>
#include "Complex.h"

using namespace std;

int main() {
    Complex x, y(4.3, 8.2), z(3.3, 1.1);

    cout << "Enter complex number x: ";
    cin >> x;

    cout << "x: " << x << "\ny: " << y << "\nz: " << z << endl;

    Complex result = y + z;
    cout << "\nx = y + z: " << result << " = " << y << " + " << z << endl;

    result = y - z;
    cout << "\nx = y - z: " << result << " = " << y << " - " << z << endl;

    // Demonstrating multiplication
    result = y * z;
    cout << "\nx = y * z: " << result << " = " << y << " * " << z << endl;

    // Comparing complex numbers
    cout << "\nIs y == z? " << (y == z ? "Yes" : "No") << endl;
    cout << "Is y != z? " << (y != z ? "Yes" : "No") << endl;

    return 0;
}


OUTPUT-

Enter complex number x: 5.7, 8.55
x: (5.7, 8.55)
y: (4.3, 8.2)
z: (3.3, 1.1)

x = y + z: (7.6, 9.3) = (4.3, 8.2) + (3.3, 1.1)

x = y - z: (1, 7.1) = (4.3, 8.2) - (3.3, 1.1)

x = y * z: (5.17, 31.79) = (4.3, 8.2) * (3.3, 1.1)

Is y == z? No
Is y != z? Yes

