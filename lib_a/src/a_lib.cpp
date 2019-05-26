#include "a_lib.h"

#include <iostream>

int get_num_liba()
{
    std::cout << "called: " << __FUNCTION__ << std::endl;

    return 42;
}

// zmt style guide cases

// STYLEGUIDE: Enumeration Names
enum eResult { kNone, kAll, kSomeAvailable };

// STYLEGUIDE: (???) namespaces should be nested on a single line with a single
// indent
namespace XTest { namespace XNest {

    bool IsThatAwesome() { return true; }

    // STYLEGUIDE: Curly Braces
    bool IsThatFuncAwesome(bool condition, bool another_condition)
    {
        if (condition)
        {
            if (another_condition)
            {
            }
        }

        return false;
    }
}} // namespace XTest::XNest

// STYLEGUIDE: Class Member Initialisation

CMyClass::CMyClass()
    : m_MyVariable(1.23)
    , m_MyVariable2(1.17)
    , m_MyVariable3(3.21){};