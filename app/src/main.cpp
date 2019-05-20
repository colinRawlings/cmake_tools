#include <iostream>
#include <string>

#include <a_lib.h>

int my_function(int arg, int arg2, int arg_with_a_very_long_name, int arg4)
{
  return 0;
}

int main()
{
  std::cout << "called: " << __FUNCTION__ << std::endl;

  int a_long_variable_name = get_num_liba();

  int b = my_function(a_long_variable_name, a_long_variable_name,
                      a_long_variable_name, a_long_variable_name);

  int c = my_function(a_long_variable_name, a_long_variable_name,
                      a_long_variable_name, a_long_variable_name);

  std::string a_string("hello");

  std::cout << a_string << std::endl;

  int d(b);

  return 0;
}