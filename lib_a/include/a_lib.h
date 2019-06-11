#pragma once

__declspec(dllexport) int get_num_liba();

// bad functions

__declspec(dllexport) bool dereference_null();

__declspec(dllexport) bool never_return();

__declspec(dllexport) bool throw_an_exception();

// class definition (style guide)

class CMyClass
{
    double m_MyVariable;
    double m_MyVariable2;
    double m_MyVariable3;

  public:
    CMyClass();
};