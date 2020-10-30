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
        std::cout << moved << " " << moved.getCount() << std::endl;
        str = std::move(moved);
        std::cout << str << " " << str.getCount()  << std::endl;
    }
    {//MyString append
        std::cout << "MyString append test:" << std::endl;
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

    return 0;
}
