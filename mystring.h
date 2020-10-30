#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED

#include <iostream>

class MyString {
public:
    MyString(const char *c="");
    MyString(MyString && the_other) noexcept;
    MyString(MyString const &source) ;
    ~MyString() noexcept;
    MyString& operator= (MyString && the_other) noexcept;
    MyString& operator= (MyString const &rhs);
    MyString& operator+= (MyString rhs);
    MyString& operator+= (char rhs);
    char& operator[](size_t i);
    char const& operator[](size_t i) const ;
    char& operator= (char rhs) const;
    int getLength() const noexcept;
    int getCount() const noexcept;
    char* getStr() const {return str;}
    friend std::istream& operator>>(std::istream& is, MyString &ms);
    friend std::ostream& operator<<(std::ostream& os, MyString const& ms);
private:
    char* str{nullptr};
    int* refcnt{nullptr};
    size_t len = 0;
    void destruct() noexcept;
};

MyString operator+ (MyString lhs, const MyString& rhs);

MyString operator+ (MyString lhs, const char rhs);

#endif // MYSTRING_H_INCLUDED
