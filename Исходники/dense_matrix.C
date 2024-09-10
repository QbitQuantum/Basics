void DenseMatrix<T>::right_multiply_transpose (const DenseMatrix<T>& B)
{
  if (this->use_blas_lapack)
    this->_multiply_blas(B, RIGHT_MULTIPLY_TRANSPOSE);
  else
    {
      //Check to see if we are doing B*(B^T)
      if (this == &B)
	{
	  //libmesh_here();
	  DenseMatrix<T> A(*this);

	  // Simple but inefficient way
	  // return this->right_multiply_transpose(A);

	  // More efficient, more code
	  // If B is mxn, the result will be a square matrix of Size m x m.
	  const unsigned int n_rows = B.m();
	  const unsigned int n_cols = B.n();

	  // resize() *this and also zero out all entries.
	  this->resize(n_rows,n_rows);

	  // Compute the lower-triangular part
	  for (unsigned int i=0; i<n_rows; ++i)
	    for (unsigned int j=0; j<=i; ++j)
	      for (unsigned int k=0; k<n_cols; ++k) // inner products are over n_cols
		(*this)(i,j) += A(i,k)*A(j,k);

	  // Copy lower-triangular part into upper-triangular part
	  for (unsigned int i=0; i<n_rows; ++i)
	    for (unsigned int j=i+1; j<n_rows; ++j)
	      (*this)(i,j) = (*this)(j,i);
	}

      else
	{
	  DenseMatrix<T> A(*this);

	  this->resize (A.m(), B.m());

	  libmesh_assert_equal_to (A.n(), B.n());
	  libmesh_assert_equal_to (this->m(), A.m());
	  libmesh_assert_equal_to (this->n(), B.m());

	  const unsigned int m_s = A.m();
	  const unsigned int p_s = A.n();
	  const unsigned int n_s = this->n();

	  // Do it this way because there is a
	  // decent chance (at least for constraint matrices)
	  // that B.transpose(k,j) = 0.
	  for (unsigned int j=0; j<n_s; j++)
	    for (unsigned int k=0; k<p_s; k++)
	      if (B.transpose(k,j) != 0.)
		for (unsigned int i=0; i<m_s; i++)
		  (*this)(i,j) += A(i,k)*B.transpose(k,j);
	}
    }
}