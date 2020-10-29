#include "mystring.h"
#include <iostream>
#include <cstring>

MyString::MyString(const char *c){
    /*if (c) {
        str = new char[strlen(c) + 1];
        strcpy(str, c);
        refcnt = new int{1};
    }*/
    strlen(c) > 0 ? str = new char[strlen(c)+1] : str = new char[5];
    strcpy(str, c);
    if(str!=nullptr){
        refcnt = new int {1};
    }
    else
        refcnt = nullptr;

};

MyString::MyString(MyString const &source): str{source.str}, refcnt{source.refcnt}{
    if(str){
        ++ *refcnt;
    }
}

MyString::MyString(MyString && the_other) noexcept{
    str = the_other.str;
    refcnt = the_other.refcnt;
    the_other.str = nullptr;
    the_other.refcnt = nullptr;
};

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
        //this->str = new char[strlen(rhs.str)];
        refcnt = rhs.refcnt;
        ++*rhs.refcnt;
        this->str = rhs.str;
    }
    return *this;
}


MyString& MyString::operator= (MyString && the_other) noexcept{
    if(&the_other != this  ){
        this->destruct();
        refcnt = the_other.refcnt;
        str = the_other.str;
        the_other.refcnt = nullptr;
        the_other.str = nullptr;
    }
    return *this;
};

MyString operator+ (MyString lhs, const MyString& rhs){
    return lhs += rhs;
};

MyString operator+ (MyString lhs, const char rhs){
    return lhs += rhs;
}

MyString& MyString::operator+= (const MyString rhs){
    if(rhs.getLength() == 0){
        return *this;
    }
    char *new_str = new char[strlen(str)+rhs.getLength()+1];
    strcpy(new_str, this->getStr());
    strcat(new_str, rhs.getStr());
    new_str[strlen(str)+rhs.getLength()] = '\0';
    destruct();
    this->str = new_str;
    this->refcnt = new int{1};
    return *this;
}
MyString& MyString::operator+= (const char rhs){
    char* new_str = new char[strlen(str)+2];
    strcpy(new_str, this->getStr());
//    strncat(new_str, rhs, 1);
    new_str[this->getLength()] = rhs;
    new_str[this->getLength()+1] = '\0';
    destruct();
    this->str = new_str;
    this->refcnt = new int {1};
    return *this;
};
/*
std::ostream& operator<<(std::ostream& os, MyString& ms){
    os << ms.getStr();
    return os;
}*/

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

int MyString::getLength() const noexcept {return strlen(str);}

char& MyString::operator[](size_t i){
    if(i >= strlen(str) || i < 0){
        throw std::out_of_range("Index out of bound");
    }
    if(1 < *this->refcnt){
        char *toCopyOnWrite = new char[strlen(this->str)+1];
        strcpy(toCopyOnWrite, this->str);
        -- *this->refcnt;
        this->str = toCopyOnWrite;
        this->refcnt = new int{1};
    }
    return str[i];
}

char const& MyString::operator[] (size_t i) const {
    if(i >= strlen(str) || i < 0){
        throw std::out_of_range("Index out of bound");
    }
    return str[i];
}


/*std::ostream& operator<<(std::ostream& os, const MyString& ms){
    os << ms.getStr();
    return os;
}*/
