matrix<T,N> transformation(matrix<T,N> lhs, 
                           const matrix<T,N>& rhs,
                           bool& success)
{
  return rhs*(lhs.inverse(success)); 
}