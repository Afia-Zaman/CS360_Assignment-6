#ifndef HUGEINT_H
#define HUGEINT_H
#include <array>
#include <iostream>
#include <string>
class HugeInt {
 friend std::ostream& operator<<(std::ostream&, const HugeInt&);
 friend std::istream& operator>>(std::istream&, HugeInt&);
public:
 static const int digits = 30; 
 HugeInt(long = 0); 
 HugeInt(const std::string&); 
 // Arithmetic operators
 HugeInt operator+(const HugeInt&) const;
 HugeInt operator+(int) const;
 HugeInt operator+(const std::string&) const;
 HugeInt operator*(const HugeInt&) const;
 HugeInt operator/(int) const;
 // Relational and equality operators
 bool operator==(const HugeInt&) const;
 bool operator!=(const HugeInt&) const;
 bool operator<(const HugeInt&) const;
 bool operator<=(const HugeInt&) const;
 bool operator>(const HugeInt&) const;
 bool operator>=(const HugeInt&) const;
private:
 std::array<short, digits> integer; // stores the digits of the number
};
#endif

#include <cctype>
#include <cmath>
using namespace std;
// Constructor from long
HugeInt::HugeInt(long value) {
 integer.fill(0);
 for (int i = digits - 1; value != 0 && i >= 0; --i) {
 integer[i] = value % 10;
 value /= 10;
 }
}
// Constructor from string
HugeInt::HugeInt(const string& number) {
 integer.fill(0);
 int length = number.size();
 for (int i = digits - length, j = 0; i < digits; ++i, ++j) {
 if (isdigit(number[j]))
 integer[i] = number[j] - '0';
 }
}
// Addition operator: HugeInt + HugeInt
HugeInt HugeInt::operator+(const HugeInt& op2) const {
 HugeInt temp;
 int carry = 0;
 for (int i = digits - 1; i >= 0; --i) {
 int sum = integer[i] + op2.integer[i] + carry;
 temp.integer[i] = sum % 10;
 carry = sum / 10;
 }
 return temp;
}
// Addition operator: HugeInt + int
HugeInt HugeInt::operator+(int op2) const {
 return *this + HugeInt(op2);
}
// Addition operator: HugeInt + string
HugeInt HugeInt::operator+(const string& op2) const {
 return *this + HugeInt(op2);
}
// Multiplication operator
HugeInt HugeInt::operator*(const HugeInt& op2) const {
 HugeInt result;
 for (int i = 0; i < digits; ++i) {
 if (integer[i] == 0) continue;
 int carry = 0;
 for (int j = 0, k = digits - 1 - i; j < digits - i; ++j, ++k) {
 int product = integer[digits - 1 - i] * op2.integer[digits - 1 - j] + result.integer[k] + carry;
 result.integer[k] = product % 10;
 carry = product / 10;
 }
 }
 return result;
}

// Division operator
HugeInt HugeInt::operator/(int divisor) const {
 HugeInt result;
 int idx = 0;
 int remainder = 0;
 for (int i = 0; i < digits; ++i) {
 int current = remainder * 10 + integer[i];
 result.integer[i] = current / divisor;
 remainder = current % divisor;
 }
 return result;
}
// Relational and equality operators
bool HugeInt::operator==(const HugeInt& rhs) const {
 return integer == rhs.integer;
}
bool HugeInt::operator!=(const HugeInt& rhs) const {
 return !(*this == rhs);
}
bool HugeInt::operator<(const HugeInt& rhs) const {
 return std::lexicographical_compare(integer.begin(), integer.end(), rhs.integer.begin(),
rhs.integer.end());
}
bool HugeInt::operator<=(const HugeInt& rhs) const {
 return *this < rhs || *this == rhs;
}
bool HugeInt::operator>(const HugeInt& rhs) const {
 return !(*this <= rhs);
}
bool HugeInt::operator>=(const HugeInt& rhs) const {
 return !(*this < rhs);
}
// Stream insertion operator
ostream& operator<<(ostream& out, const HugeInt& num) {
 int i = 0;
 while (i < HugeInt::digits && num.integer[i] == 0) ++i;
 if (i == HugeInt::digits)
 out << 0;
 else
 for (; i < HugeInt::digits; ++i)
 out << num.integer[i];
 return out;
}
// Stream extraction operator
istream& operator>>(istream& in, HugeInt& num) {
 string input;
 in >> input;
 num = HugeInt(input);
 return in;
}

#include <iostream>
using namespace std;
int main() {
 HugeInt n1(7654321);
 HugeInt n2(7891234);
 HugeInt n3("99999999999999999999999999999");
 HugeInt n4("1");
 HugeInt result;
 cout << "n1 is " << n1 << "\nn2 is " << n2
 << "\nn3 is " << n3 << "\nn4 is " << n4 << "\n\n";
 result = n1 + n2;
 cout << n1 << " + " << n2 << " = " << result << "\n\n";
 result = n3 + n4;
 cout << n3 << " + " << n4 << " = " << result << "\n\n";
 result = n1 * n2;
 cout << n1 << " * " << n2 << " = " << result << "\n\n";
 result = n3 / 2;
 cout << n3 << " / " << "2" << " = " << result << "\n\n";
 return 0;
}

Output-

n1 is 7654321
n2 is 7891234
n3 is 99999999999999999999999999999
n4 is 1

7654321 + 7891234 = 15545555

99999999999999999999999999999 + 1 = 100000000000000000000000000000

7654321 * 7891234 = 0

99999999999999999999999999999 / 2 = 49999999999999999999999999999
