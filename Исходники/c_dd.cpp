 void c_dd_tanh(const double *a, double *b) {
     dd_real bb;
     bb = tanh(dd_real(a));
     TO_DOUBLE_PTR(bb, b);
 }