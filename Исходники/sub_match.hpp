inline bool operator >= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) <= 0; }