int main()
{
  std::array<int, 4> array = {1,2,3,4};

  // convert an array into a tuple
  auto tuple = a2t(array);
  static_assert(std::is_same<decltype(tuple),
      std::tuple<int, int, int, int>>::value, "");

  // print it to cout
  std::cout << tuple << '\n';
}