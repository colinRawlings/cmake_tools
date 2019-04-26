#include "b_lib.h"

#include <iostream>

int get_num_libb()
{
    std::cout << "called: " << __FUNCTION__ << std::endl;

    return 42;
}