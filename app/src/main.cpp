#include <iostream>
#include <string>

#include <a_lib.h>

int main()
{
    std::cout << "called: " << __FUNCTION__ << std::endl;

    int a = get_num_liba();

    std::string a_string("hello");

    std::cout << a_string << std::endl;

    int b(a);

    return 0;
}