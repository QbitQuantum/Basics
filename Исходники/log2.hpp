 /**
  * Returns the base two logarithm of the argument (C99, C++11).
  *
  * The function is defined by:
  *
  * <code>log2(a) = log(a) / std::log(2.0)</code>.
  *
  * @param[in] u argument
  * @return base two logarithm of argument
  */
 inline double log2(double u) {
   using std::log;
   return log(u) / LOG_2;
 }