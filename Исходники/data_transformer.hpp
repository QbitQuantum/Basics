 /**
  * @brief Generates a random integer from Uniform({0, 1, ..., n-1}).
  *
  * @param n
  *    The upperbound (exclusive) value of the random number.
  * @return
  *    A uniformly random integer value from ({0, 1, ..., n-1}).
  */
 unsigned int Rand(int n) const {
   CHECK_GT(n, 0);
   return Rand() % n;
 }