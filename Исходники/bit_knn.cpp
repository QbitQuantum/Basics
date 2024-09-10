size_t
BitKNN::inner_prod (std::vector<uint64_t> &x_vec1, std::vector<uint64_t> &x_vec2)
{
  /*
  if (x_vec1.size() != x_vec2.size()) {
    std::cerr << "ERROR: The size of two vectors are inconsistent." << std::endl;
    exit(1);
  }
  */

  size_t c = 0;
  for (int i = 0; i < (int)x_vec1.size(); i++) {
    uint64_t x = x_vec1[ i ] & x_vec2[ i ];
    c += _mm_popcnt_u64( x );
  }
  return c;
}