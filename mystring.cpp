#include "mystring.h"
#include <iostream>
#include <cstring>

MyString::MyString(const char *c){
    if (c) {
        len = strlen(c);
        str = new char[len + 1];
        strcpy(str, c);
        refcnt = new int{1};
    }
}

MyString::MyString(MyString const &source): str{source.str}, refcnt{source.refcnt}, len{source.len}{
    if(str){
        ++ *refcnt;
    }
}

MyString::MyString(MyString && the_other) noexcept{
    str = the_other.str;
    refcnt = the_other.refcnt;
    len = the_other.len;
    the_other.str = nullptr;
    the_other.refcnt = nullptr;
    the_other.len = 0;
}

void MyString::destruct() noexcept{
    if(str != nullptr){
        -- *refcnt;
        if(*refcnt == 0) {
            delete refcnt;
            delete[] str;
        }
    }
}

MyString::~MyString(){
    destruct();
}

MyString& MyString::operator= (MyString const &rhs){
    if (this != &rhs) {
        destruct();
        refcnt = rhs.refcnt;
        ++*rhs.refcnt;
        this->str = rhs.str;
        this->len = rhs.len;
    }
    return *this;
}


MyString& MyString::operator= (MyString && the_other) noexcept{
    if(&the_other != this  ){
        this->destruct();
        refcnt = the_other.refcnt;
        str = the_other.str;
        len = the_other.len;
        the_other.refcnt = nullptr;
        the_other.str = nullptr;
        the_other.len = 0;
    }
    return *this;
}

MyString operator+ (MyString lhs, const MyString& rhs){
    return lhs += rhs;
}

MyString operator+ (MyString lhs, const char rhs){
    return lhs += rhs;
}

MyString& MyString::operator+= (const MyString rhs){
    if(rhs.getLength() == 0){
        return *this;
    }
    char *new_str = new char[len+rhs.getLength()+1];
    strcpy(new_str, this->getStr());
    strcat(new_str, rhs.getStr());
    new_str[len+rhs.getLength()] = '\0';
    destruct();
    this->str = new_str;
    this->refcnt = new int{1};
    this->len = strlen(str);
    return *this;
}
MyString& MyString::operator+= (const char rhs){
    char* new_str = new char[len+2];
    strcpy(new_str, this->getStr());
    new_str[len] = rhs;
    new_str[len+1] = '\0';
    destruct();
    this->str = new_str;
    this->refcnt = new int {1};
    this->len = strlen(str);
    return *this;
}

std::ostream& operator<<(std::ostream& os, MyString const& ms){
    os << ms.str;
    return os;
}

std::istream& operator>>(std::istream& is, MyString &ms){
    int th = 0;
    char c;
    int allocated = 11;
    char *input = new char[allocated];
    while( is.get(c) ){
        if( '\n' == c  ||  '\r' == c )
            break;
        input[th] = c;

        if ( th >= allocated-1 ){
            allocated *= 2;
            char *new_place = new char[allocated];
            strcpy(new_place,input);
            delete[]input;
            input = new_place;
        }
        ++th;
    }
    input[th] = '\0';
    ms = MyString{input};
    delete[] input;
    return is;
}

int MyString::getCount() const noexcept {return *refcnt;}

int MyString::getLength() const noexcept {return len;}

char& MyString::operator[](size_t i){
    if(i >= len || i < 0){
        throw std::out_of_range("Index out of bound");
    }
    if(1 < *this->refcnt){
        char *toCopyOnWrite = new char[len+1];
        strcpy(toCopyOnWrite, this->str);
        -- *this->refcnt;
        this->str = toCopyOnWrite;
        this->refcnt = new int{1};
    }
    return str[i];
}

char const& MyString::operator[] (size_t i) const {
    if(i >= len || i < 0){
        throw std::out_of_range("Index out of bound");
    }
    return str[i];
}

