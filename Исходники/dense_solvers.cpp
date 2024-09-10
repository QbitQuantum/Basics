EIGEN_DONT_INLINE
void compute_norm_equation(Solver &solver, const MatrixType &A) {
  if(A.rows()!=A.cols())
    solver.compute(A.transpose()*A);
  else
    solver.compute(A);
}