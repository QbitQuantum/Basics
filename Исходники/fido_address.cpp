int next_int(C& c, I& it, std::set<char> stop) {
  string s;
  while (it != std::end(c) && !contains(stop, *it)) {
    if (!std::isdigit(*it)) {
      throw bad_fidonet_address(StrCat("Missing Unexpected nondigit. address: ", c));
    }
    s.push_back(*it++);
  }
  if (it != std::end(c) && contains(stop, *it)) {
    // skip over last
    it++;
  }
  return StringToInt(s);
}