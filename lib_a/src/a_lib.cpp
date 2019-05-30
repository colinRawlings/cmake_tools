#include "a_lib.h"

#include <boost/filesystem.hpp>

#include <iostream>
#include <string>

#include <chrono>
#include <thread>

int get_num_liba()
{
    boost::filesystem::path p(__FILE__);

    return 42;
}

bool dereference_null()
{
    int *a = nullptr;
    int b(0);
    b = *a;

    return false;
}

bool never_return()
{
    std::chrono::seconds wait_duration(3);

    while (true)
    {
        std::this_thread::sleep_for(wait_duration);
        std::cout << "." << std::endl;
    }

    return true;
}

bool throw_an_exception()
{
    throw 42;

    return true;
}

// Class Member Initialisation

CMyClass::CMyClass()
    : m_MyVariable(1.23)
    , m_MyVariable2(1.17)
    , m_MyVariable3(3.21){};