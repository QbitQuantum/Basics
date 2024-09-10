typename boost::enable_if_c< is_readable_matrix<Matrix>::value, 
 bool >::type is_diagonal(const Matrix& A, typename mat_traits<Matrix>::value_type NumTol = typename mat_traits<Matrix>::value_type(1E-8) ) {
  if(A.get_row_count() != A.get_col_count())
    return false;
  
  typedef typename mat_traits< Matrix >::size_type SizeType;
  using std::fabs;
  
  for(SizeType i=0;i<A.get_row_count();i++)
    for(SizeType j=0;j<i;j++)
      if((fabs(A(j,i)) > NumTol) || (fabs(A(i,j)) > NumTol))
        return false;
  
  return true;
};