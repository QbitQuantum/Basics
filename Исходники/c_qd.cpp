void c_qd_sinh(const double *a, double *b) {
  qd_real bb;
  bb = sinh(qd_real(a));
  TO_DOUBLE_PTR(bb, b);
}