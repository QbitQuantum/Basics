 inline void pcg_atxpy(const MatrixType& A, const VectorXD& x, int xoff, VectorXD& y, int yoff)
 {
   y.segment<MatrixType::ColsAtCompileTime>(yoff) += A.transpose() * x.segment<MatrixType::RowsAtCompileTime>(xoff);
 }