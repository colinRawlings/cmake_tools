#include "a_lib.h"

#include <iostream>

int get_num_liba()
{
    std::cout << "called: " << __FUNCTION__ << std::endl;

    return 42;
}