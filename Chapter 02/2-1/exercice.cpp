#include <iostream>
#include <type_traits>

template <class C, class X, bool value>
struct replace
{
  typedef C type;
};

template <class C, class X>
struct replace<C, X, true>
{
  typedef X type;
};

template <typename c, typename x, typename y>
struct replace_type
{
  typedef typename replace<c, y, std::is_same_v<c, x>>::type type;
};

// template <typename c, typename x, typename y>
// struct replace_type<c &, x, y>
// {
//   typedef typename replace_type<c, x, y>::type &type;
// };

// template <typename c, typename x, typename y>
// struct replace_type<c *, x, y>
// {
//   typedef typename replace_type<c, x, y>::type *type;
// };

template <typename c, int N, typename x, typename y>
struct replace_type<c[N], x, y>
{
  typedef typename replace_type<c, x, y>::type type[N];
};

template <typename c1, typename c2, typename x, typename y>
struct replace_type<c1 (*)(c2), x, y>
{
  typedef typename replace_type<c1, x, y>::type (*type)(typename replace_type<c2, x, y>::type);
};

int main()
{
  std::cout << std::is_same<replace_type<void, void, int>::type, int>::value
            << std::endl;
  std::cout << std::is_same<replace_type<char, void, int>::type, char>::value
            << std::endl;
  std::cout << std::is_same<replace_type<void *, void *, int *>::type, int *>::value
            << std::endl;
  std::cout << std::is_same<replace_type<char &, char &, long &>::type, long &>::value
            << std::endl;
  std::cout << std::is_same<replace_type<int const *[10], int const *, long *>::type, long *[10]>::value
            << std::endl;

  std::cout << std::is_same<replace_type<char (*)(char), char, long>::type, long (*)(long)>::value
            << std::endl;
  std::cout << std::is_same<replace_type<void (*)(int), void, long>::type, long (*)(int)>::value
            << std::endl;
  std::cout << std::is_same<replace_type<char &(*)(char &), char &, long &>::type, long &(*)(long &)>::value
            << std::endl;
}
