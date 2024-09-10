 /**
  * Add integer \e k to the RandomNumber.
  *
  * @param[in] k the integer to add.
  **********************************************************************/
 void AddInteger(int k) throw() {
   k += Floor();             // The new floor
   int ns = k < 0 ? -1 : 1;  // The new sign
   if (ns != _s)             // If sign changes, set f = 1 - f
     for (size_t k = 0; k < Size(); ++k)
       _f[k] = ~_f[k] & mask;
   _n = ns > 0 ? k : -(k + 1);
 }