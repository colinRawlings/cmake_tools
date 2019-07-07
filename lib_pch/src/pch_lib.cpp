// #include "pch_header.h"

#include "..\include\pch_lib.h"

int get_num_lib_pch(void)
{
    std::vector<std::string> sv = {"hello", "pch", "world"};

    return static_cast<int>(sv.size());
}