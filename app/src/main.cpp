#include <iostream>

#include <a_lib.h>

int main()
{
    std::cout << "called: " << __FUNCTION__ << std::endl;

    int a = get_num_liba();

    int b(a);

    return 0;
}