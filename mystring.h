#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED

#include <iostream>

class MyString {
public:
    MyString(const char *c="");
   // MyString(char const * c);
    MyString(MyString && the_other);
    MyString(MyString const &source);
    ~MyString();
//    MyString& operator= (const char * rhs);
    MyString& operator= (MyString && the_other);
    MyString& operator= (MyString const &rhs);
    MyString& operator+= (MyString rhs);
    MyString& operator+= (char rhs);
    char& operator[](int i);
    char const& operator[](int i) const ;
    char& operator= (char rhs) const;
//    char operator= (const char rhs){
//    return rhs;
//}
    int getLength() const;
    int getCount() const;
    char* getStr() const {return str;}
    friend std::istream& operator>>(std::istream& is, MyString &ms);
private:
    char* str = nullptr;
    int* refcnt = 0;

    void set_str(char *c);
};



MyString operator+ (MyString lhs, MyString rhs);

MyString operator+ (MyString lhs, const char rhs);

//MyString& operator+= (MyString& lhs, const char rhs);

std::ostream& operator<<(std::ostream& os, MyString& ms);
std::ostream& operator<<(std::ostream& os, MyString const& ms);



#endif // MYSTRING_H_INCLUDED
