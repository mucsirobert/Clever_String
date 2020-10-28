#include "mystring.h"
#include <iostream>
#include <cstring>

//talán jó
MyString::MyString(const char *c){
//    std::cout << "str pointer memory address" << &str << std::endl;


    str = new char(strlen(c));
    strcpy(str, c);

    //str = const_cast<char *>(c);
    if(str){
        refcnt = new int(1);
//        std::cout<<&c<< ":  lol  :" <<&str<<std::endl;
    }
    else
        refcnt = nullptr;
};

//talán jó
MyString::MyString(MyString const &source): str{source.str}, refcnt{source.refcnt}{
  //  std::cout << "copy ctor\n";
    if(str){
        ++ *refcnt;
    }
}
// talán jó
MyString::MyString(MyString && the_other){
   // std::cout <<"move ctor\n";
   /* if(str != nullptr)
        delete[] str;*/
   //std::cout <<"move ctor e\n" << the_other.getStr();
    //str = new char[the_other.getLength()];
    //strcpy(str,the_other.str);
    //this->refcnt = the_other.refcnt;
    str = the_other.str;
    refcnt = the_other.refcnt;
    the_other.str = nullptr;
    the_other.refcnt = nullptr;
};

//elvileg jó
MyString::~MyString(){
    if(str != nullptr){
        -- *refcnt;
        if(*refcnt == 0) {
            delete refcnt;
            delete[] str;
        }
    }
}

MyString& MyString::operator= (MyString const &rhs){
    std::cout << "const value giver\n";
    if (this != &rhs) { // self-assignment check expected
        if(1 == *this->refcnt)
            delete[] this->str;              // destroy storage in this
        --*this->refcnt;
        this->str = nullptr;             // preserve invariants in case next line throws
        this->refcnt = nullptr;
        this->str = new char[strlen(rhs.str)]; // create storage in this
        refcnt = rhs.refcnt;
        ++*rhs.refcnt;
        this->str = rhs.str;
        //strcpy(this->str,rhs.str);
    }
    return *this;
}


MyString& MyString::operator= (MyString && the_other){
    //std::cout <<"move operator\n";
    if(&the_other != this  ){
           // std::cout <<"a 1 \n";
        this->~MyString();
        refcnt = the_other.refcnt;
        str = the_other.str;
        the_other.refcnt = nullptr;
        the_other.str = nullptr;
    }
    return *this;
};

//talán jó
MyString operator+ (MyString lhs, MyString rhs){
    char cat[lhs.getLength() + rhs.getLength()+1];
    strcpy(cat,lhs.getStr());
    strcat(cat,rhs.getStr());
    cat[lhs.getLength() + rhs.getLength()] = '\0';
    MyString my{cat};
    //std::cout << "+ operator new length: " << cat << " " << my.getLength();

    return MyString{cat};
};

MyString operator+ (MyString lhs, const char rhs){
    char cat[lhs.getLength()+2];
    strcpy(cat,lhs.getStr());
    cat[lhs.getLength()] = rhs;
    cat[lhs.getLength()+1] = '\0';
    return MyString{cat};
}

MyString& MyString::operator+= (MyString rhs){
    if(rhs.getLength() == 0){
        return *this;
    }
    if (1 < this->getCount()){
        char *new_str = new char(strlen(str)+rhs.getLength()+1);
        strcpy(new_str, this->getStr());
        strcat(new_str, rhs.getStr());
        new_str[strlen(str)+rhs.getLength()] = '\0';
//        std::cout << toCopyOnWrite << "  :asdfg\n";
        -- *this->refcnt;
        this->str = new_str;
        this->refcnt = new int(1);
    }
    else{
        char *new_str = new char(strlen(str)+rhs.getLength()+1);
        strcpy(new_str, this->getStr());
        strcat(new_str, rhs.getStr());
        new_str[strlen(str)+rhs.getLength()] = '\0';
        delete[] str;
        this->str = new_str;
    }
    return *this;
}

MyString& MyString::operator+= (char rhs){
    if(1 <this->getCount()){
        char* new_str = new char(strlen(str)+2);
            strcpy(new_str, this->getStr());
        new_str[this->getLength()] = rhs;
        new_str[this->getLength()+1] = '\0';
        -- *this->refcnt;
        this->str = new_str;
        this->refcnt = new int(1);
    }
    else{
        char *new_str = new char(strlen(str)+2);
        strcpy(new_str, this->getStr());
        new_str[this->getLength()] = rhs;
        new_str[this->getLength()+1] = '\0';
        delete[] str;
        this->str = new_str;
    }
    return *this;
};



//talán jó
std::ostream& operator<<(std::ostream& os, MyString& ms){
    os << ms.getStr();
    return os;
}

std::ostream& operator<<(std::ostream& os, MyString const& ms){
    os << ms.getStr();
    return os;
}

void MyString::set_str(char *c){
        str = new char(strlen(c));
        strcpy(str, c);
        if(str){
            refcnt = new int(1);
        }
        else
            refcnt = nullptr;
    }

std::istream& operator>>(std::istream& is, MyString &ms){
    /*char *c;
    is >> *c;
    ms.set_str(c);
    is.get();*/


    int n = 0;
    char c;
    char *a = new char[11];
    int allocated = 11;
    while( is.get(c) ){
        if( '\n' == c  ||  '\r' == c )
            break;

        a[n] = c;

        if ( n == allocated ){
            allocated *= 2;
            char *b = new char[allocated];
            for ( int i = 0; i <= n; ++i )
                b[i] = a[i];
            delete[] a;
            a = b;
        }

        ++n;
    }
    a[n] = '\0';

    ms.set_str(a);

    return is;
}

int MyString::getCount() const {return *refcnt;}

int MyString::getLength() const {return strlen(str);}



char& MyString::operator[](int i){
    if(i >= this->getLength() || i < 0){
        throw std::out_of_range("Index out of bound");
    }
    if(1 < *this->refcnt){
        std::cout <<"inside: copyOnWriteCall\n";
        char *toCopyOnWrite = new char(strlen(this->str));

        strcpy(toCopyOnWrite, this->str);
//        std::cout << toCopyOnWrite << "  :asdfg\n";
        -- *this->refcnt;
        this->str = toCopyOnWrite;
        this->refcnt = new int(1);
    }

        std::cout <<"copyOnWriteCall\n";
//        std::cout << "nope:\n";
    return str[i];
}

char const& MyString::operator[] (int i) const {
    std::cout << "const:\n";
    return str[i];
}

