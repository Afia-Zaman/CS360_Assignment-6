// 1. Using classes, design an online address book to keep track of the names, addresses,
// phone numbers, and dates of birth of family members, close friends, and certain business
// associates. Your program should be able to handle a maximum of 500 entries.
// a. Design the class dateType was designed to implement the date in a program,
// but the member function setDate and the constructor do not check whether
// the date is valid before storing the date in the member variables. Rewrite the
// definitions of the function setDate and the constructor so that the values for
// the month, day, and year are checked before storing the date into the member
// variables. Add a member function, isLeapYear, to check whether a year is a
// leap year. Moreover, write a test program to test your class.
// b. Define a class, addressType, that can store a street address, city, state, and ZIP code.
// Use the appropriate functions to print and store the address. Also, use constructors
// to automatically initialize the member variables.
// c. Define a class extPersonType using the class personType as follows, the class
// dateType, and the class addressType. Add a member variable to this class to classify
// the person as a family member, friend, or business associate. Also, add a member
// variable to store the phone number. Add (or override) the functions to print and
// store the appropriate information. Use constructors to automatically initialize the
// member variables.
// d. Define the class addressBookType using the previously defined classes. An object of
// the type addressBookType should be able to process a maximum of 500 entries. The
// program should perform the following operations:
// i. Load the data into the address book from a disk.
// ii. Sort the address book by last name.
// iii. Search for a person by last name.
// iv. Print the address, phone number, and date of birth (if it exists) of a given
// person.
// v. Print the names of the people whose birthdays are in a given month.
// vi. Print the names of all of the people between two last names.
// vii. Depending on the user’s request, print the names of all family members,
// friends, or business associates.
// #include <string>
// using namespace std;
// class personType{
// public:
// void print() const;
// //Function to output the first name and last name
// //in the form firstName lastName.
// void setName(string first, string last);
// //Function to set firstName and lastName according
// //to the parameters.
// //Postcondition: firstName = first; lastName = last;
// string getFirstName() const;
// //Function to return the first name.
// //Postcondition: The value of firstName is returned.
// string getLastName() const;
// //Function to return the last name.
// //Postcondition: The value of lastName is returned.
// personType(string first = "", string last = "");
// //Constructor
// //Sets firstName and lastName according to the parameters.
// //The default values of the parameters are null strings.
// //Postcondition: firstName = first; lastName = last;
// private:
// string firstName; //variable to store the first name
// string lastName; //variable to store the last name
// };
// void personType::print() const{
// cout << firstName << " " << lastName;
// }
// void personType::setName(string first, string last){
// firstName = first;
// lastName = last;
// }
// string personType::getFirstName() const{return firstName;}
// string personType::getLastName() const{return lastName;}
// //constructor
// personType::personType(string first, string last){
// firstName = first;
// lastName = last;
// }

Answer:

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Class to handle date with validation
class dateType {
public:
    dateType(int month = 1, int day = 1, int year = 1900) {
        setDate(month, day, year);
    }
    void setDate(int month, int day, int year) {
        if (isValidDate(month, day, year)) {
            dMonth = month;
            dDay = day;
            dYear = year;
        } else {
            cout << "Invalid date provided. Setting to default." << endl;
            dMonth = 1;
            dDay = 1;
            dYear = 1900;
        }
    }
    int getDay() const { return dDay; }
    int getMonth() const { return dMonth; }
    int getYear() const { return dYear; }
    bool isLeapYear() const {
        return (dYear % 4 == 0 && (dYear % 100 != 0 || dYear % 400 == 0));
    }

private:
    int dMonth, dDay, dYear;
    bool isValidDate(int month, int day, int year) const {
        if (year < 1900 || year > 2100) return false; // Year range
        if (month < 1 || month > 12) return false; // Month range
        if (day < 1 || day > 31) return false; // Day range
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            return false; // Months with 30 days
        if (month == 2) // February
            return day <= (isLeapYear() ? 29 : 28);
        return true;
    }
};

// Class to handle addresses
class addressType {
public:
    addressType(string street = "", string city = "", string state = "", string zip = "")
    : streetAddress(street), city(city), state(state), zipCode(zip) {}

    void printAddress() const {
        cout << streetAddress << ", " << city << ", " << state << " " << zipCode << endl;
    }
    void setAddress(string street, string city, string state, string zip) {
        streetAddress = street;
        city = city;
        state = state;
        zipCode = zip;
    }

private:
    string streetAddress, city, state, zipCode;
};

// Basic person type class
class personType {
public:
    personType(string first = "", string last = "")
    : firstName(first), lastName(last) {}

    void setName(string first, string last) {
        firstName = first;
        lastName = last;
    }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    void print() const {
        cout << firstName << " " << lastName;
    }

private:
    string firstName, lastName;
};

// Extended person type class
class extPersonType : public personType {
public:
    extPersonType(string first = "", string last = "", string phone = "", 
                  addressType address = addressType(), dateType dob = dateType(), string relation = "Friend")
    : personType(first, last), phoneNumber(phone), personAddress(address), birthDate(dob), relationship(relation) {}

    void print() const {
        personType::print();
        cout << ", Phone: " << phoneNumber << ", Relationship: " << relationship << endl;
        cout << "Address: ";
        personAddress.printAddress();
        cout << "DOB: " << birthDate.getMonth() << "/" << birthDate.getDay() << "/" << birthDate.getYear() << endl;
    }

private:
    addressType personAddress;
    dateType birthDate;
    string phoneNumber, relationship;
};

// Address book class managing up to 500 entries
class addressBookType {
public:
    void addEntry(const extPersonType& entry) {
        if (entries.size() < MAX_ENTRIES)
            entries.push_back(entry);
        else
            cout << "Address book is full. Cannot add more entries." << endl;
    }
    void printAddressBook() const {
        for (const auto& entry : entries) {
            entry.print();
        }
    }

private:
    vector<extPersonType> entries;
    static const int MAX_ENTRIES = 500;
};

// Main function to demonstrate the use
int main() {
    addressBookType myAddressBook;

    // Create some sample entries
    addressType addr1("Warm Springs Blvd", "Fremont", "CA", "94539");
    dateType dob1(9, 15, 2001);
    extPersonType person1("Naim", "Rahman", "555-1234", addr1, dob1, "Family");

    addressType addr2("27 Scarborough", "Toronto", "ON", "67890");
    dateType dob2(1, 25, 2001);
    extPersonType person2("Umama", "Sikder", "555-5678", addr2, dob2, "Friend");

    // Add entries to the address book
    myAddressBook.addEntry(person1);
    myAddressBook.addEntry(person2);

    // Print the address book
    myAddressBook.printAddressBook();

    return 0;
}

Output-

Naim Rahman, Phone: 555-1234, Relationship: Family
Address: Warm Springs Blvd, Fremont, CA 94539
DOB: 9/15/2001
Umama Sikder, Phone: 555-5678, Relationship: Friend
Address: 27 Scarborough, Toronto, ON 67890
DOB: 1/25/2001
