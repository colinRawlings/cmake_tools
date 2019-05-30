#pragma once

int get_num_liba();

// bad functions

bool dereference_null();

bool never_return();

bool throw_an_exception();

// class definition (style guide)

class CMyClass
{
    double m_MyVariable;
    double m_MyVariable2;
    double m_MyVariable3;

  public:
    CMyClass();
};