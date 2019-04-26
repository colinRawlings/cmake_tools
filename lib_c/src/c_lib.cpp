#include "c_lib.h"

#include "one_lib.h"

#include <iostream>

int get_num_libc()
{
    std::cout << "called: " << __FUNCTION__ << std::endl;

    return get_num_libone();
}