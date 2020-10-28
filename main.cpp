#include <iostream>
#include "mystring.h"


int main()
{
    {//Constructors
        std::cout << "Constructor test:" << std::endl;
        MyString emp{};
        std::cout << emp << " " << emp.getCount() << std::endl;
        MyString str{"cica"};
        std::cout << str << " " << str.getCount() << std::endl;
        MyString my = "kutya";
        std::cout << my << " " << my.getCount() << std::endl;
    }
    {//Copy
        std::cout << "Copy constructor test:" << std::endl;
        MyString to_copy{"to_copy"};
        MyString copied{to_copy};
        std::cout << to_copy << " " << to_copy.getCount() << std::endl;
        std::cout << copied << " " << copied.getCount() << std::endl;
    }
    {//operator=
        std::cout << "Operator= test:" << std::endl;
        MyString to_copy{"to="};
        MyString copied = to_copy;
        std::cout << to_copy << " " << to_copy.getCount() << std::endl;
        std::cout << copied << " " << copied.getCount() << std::endl;
    }
    {//move
        std::cout << "Move constructor test:" << std::endl;
        MyString str{"str"};
        MyString moved{std::move(str)};
       // std::cout << str << " " << str.getCount() << std::endl;
        std::cout << moved << " " << moved.getCount() << std::endl;
        str = std::move(moved);
        std::cout << str << " " << str.getCount()  << std::endl;
    }
    {//MyString append
        std::cout << "MyString append test:" << std::endl;
//        MyString cica{"cica"};
//        MyString kutya{"kutya"};
//        MyString cica2{cica};
//        MyString allatok = cica+kutya;
//        cica += cica;
//        std::cout << cica << " " << cica.getCount() << std::endl;
//        std::cout << cica2 << " " << cica2.getCount() << std::endl;
//        std::cout << kutya << " " << kutya.getCount() << std::endl;
//        std::cout << allatok << " " << allatok.getCount() << std::endl;
//        std::cout << cica << " " << cica.getCount() << std::endl;
//        cica += MyString{};
//        std::cout << cica << " " << cica.getCount() << std::endl;
//        std::cout << "----------------"<< std::endl;
        MyString str1{"alma"};
        MyString str2{"fa"};
        MyString str3 = str2;
        MyString osszeg = str1 + str2;
        std::cout << osszeg << " " << osszeg.getCount() << std::endl;
        str1 += str2;
        std::cout << str1 << " " << str1.getCount() << std::endl;
        str2 += MyString{};
        std::cout << str2 << " " << str2.getCount() << std::endl;
        str2 += MyString{"haz"};
        std::cout << str2 << " " << str2.getCount() << std::endl;
        std::cout << str3 << " " << str3.getCount() << std::endl;
    }
    {//char append
        std::cout << "Char append test:" << std::endl;
        MyString dob{"dob"};
        MyString dobok{dob};
        dob += 'i';
        std::cout << dob << " " << dob.getCount() << std::endl;
        std::cout << dobok << " " << dobok.getCount() << std::endl;
        MyString str = dobok + '5';
        std::cout << dobok << " " << dobok.getCount() << std::endl;
        std::cout << str << " " << str.getCount() << std::endl;
    }
    {//index
        std::cout << "Index test:" << std::endl;
        MyString dobberman{"kutya"};
        MyString husky = dobberman;
        dobberman[4] = 'u';
        std::cout << dobberman << " " << dobberman.getCount() << std::endl;
        std::cout << husky << " " << husky.getCount() << std::endl;
        MyString const constant{"Konstans"};
        char o = constant[1];
        std::cout << "constant[1]: " << o << std::endl;
        try{
            std::cout<<dobberman[5]<<std::endl;
        } catch (std::out_of_range& e){
            std::cout << e.what() << " kivetel elkapva" << std::endl;
        }
    }
    {//input and length
        std::cout << "Input and legth test:\n (write smthng)" << std::endl;
        MyString str;
        std::cin >> str;
        std::cout << str << " " << str.getLength() << std::endl;
    }
/*
    const char * c = "IIIIIIIIIIIIIII";
    MyString s{c};
    //std::cin >> s;
    MyString text = "text";
    //MyString a,b,c;
   // MyString a{s};
    MyString copied{text};
    MyString cica = "cica";
    MyString cic2{cica};
    MyString kutya = "kutya";
    char x = 'x';
    std::cout << " x create: \n";

    kutya = kutya +x;
    std::cout<<kutya <<std::endl;



   // a = s;
//    std::cout <<"mem: "<< *s.refcnt << " " << *a.refcnt;
//    std::cout <<"mem: "<< s.str << " " << a.str;
//    s += 'x';
//    std::cout <<"mem: "<< s.str << " " << a.str;
//    s.~MyString();

   // a = s;

    std::cout << "str: "<< s << " cnt: " << s.getCount() << " len: " << s.getLength() << std::endl;

    std::cout << "str: "<< text << " cnt: " << text.getCount() << " len: " <<  text.getLength() << "\n = happen " << std::endl;

    s = text;

    std::cout << "text.str: "<< text << " cnt: " << text.getCount() << " len: " <<  text.getLength() << std::endl;
    s[1] = 'O';
    std::cout << "s.str: "<< s << " cnt: " << s.getCount() << " len: " << s.getLength() << std::endl;

    std::cout << "text.str: "<< text << " cnt: " << text.getCount() << " len: " <<  text.getLength() << std::endl;*/
  //  std::cout<<a<<*a.refcnt<<std::endl;

//    const char *o = "poiuz";
//    const char *i;
//    i=o;
//    std::cout<< o<<std::endl;
//    std::cout<< i;

    //std::cout << a <<std::endl;

    return 0;


//    MyString a, b, c;
//    a = b = c = "helló világ";

//    MyString x = "hello";
//    MyString y = x;
//    y[0] = 'c';
//    std::cout << x;     /* hello */
//    std::cout << y;     /* cello */
}
