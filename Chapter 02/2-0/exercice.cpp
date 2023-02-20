#include <iostream>
#include <type_traits>

template <typename T>
struct add_const_ref
{
  typedef const T &type;
};

template <typename T>
struct add_const_ref<T &>
{
  typedef const T &type;
};

int main()
{
  std::cout << std::is_same<add_const_ref<int>::type, const int &>::value
            << std::endl;
  std::cout << std::is_same<add_const_ref<const int>::type, const int &>::value
            << std::endl;
  std::cout << std::is_same<add_const_ref<const int &>::type, const int &>::value
            << std::endl;
  std::cout << std::is_same<add_const_ref<int &>::type, const int &>::value
            << std::endl;
}
