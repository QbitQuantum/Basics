/* checks if a matrix is symmetric. */
bool isSymmetric(Matrix &A)
{
    // not square, so definitely not symmetric.
    if (A.rows() != A.cols()) return false;
    
    if (A.transpose() == A) return true;
    
    return false;
}