int main () {
  typedef const double c_dbl;
  typedef const double * c_p_dbl;
  typedef const double * const c_p_c_dbl;
  typedef double * p_dbl;
  typedef double & r_dbl;

  cout << fixed << setprecision(3);

  double my_double = 123.456789;    // Set 1
  cout << "Set1: " << my_double;    // 123.457


  r_dbl r_my_dbl = my_double;       // Set 2  (ref. to my_double)
  r_my_dbl = 987.654321;            // 987.654
  cout << "\nSet2: " << my_double;

  p_dbl p_my_dbl = &my_double;     // Set 3 (pointer to my_double)
  my_double = 1.012345;            // 1.012
  cout << "\nSet3: " << *p_my_dbl;
  
  c_dbl pi = atan(1.0) * 4.0;     // Set 4
  //r_dbl r_pi = pi;              // error because pi is const
  //cout << r_pi;

  c_p_dbl c_p_pi = &pi;           // Set 5  (ptr. to a const double)
  c_p_pi = &my_double;            // adds const modifier
  cout << "\nSet5: " << *c_p_pi;  // 1.012


  c_p_c_dbl cpc_pi = &pi;        // Set 6 (const ptr to const double)
  //cpc_pi = &my_double;         // error, can't change what const ptr points to
  cout << "\nSet6: "<< *cpc_pi << endl;    // 3.142           
}