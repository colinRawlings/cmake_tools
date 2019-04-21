#include "two_lib.h"

#include <iostream>

int get_num_libtwo()
{
    std::cout << "called: " << __FUNCTION__ << std::endl;

    return 42;
}