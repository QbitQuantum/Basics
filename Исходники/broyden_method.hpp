void broyden_good_method(const Vector& x_prev, Vector& x0, RootedFunction f, const T& tol = std::numeric_limits<T>::epsilon(), std::size_t max_iter = 50) 
{
  using std::fabs;
  typedef typename vect_traits<Vector>::value_type ValueType;
  typedef typename vect_traits<Vector>::size_type SizeType;
  
  Vector dx = x0 - x_prev;
  Vector y0 = f(x0);
  Vector dy = y0 - f(x_prev);
  std::size_t iter = 0;
  
  mat<ValueType, mat_structure::square> J_inv = mat<ValueType, mat_structure::identity>(dx.size());
  Vector Jdy = dy;
  ValueType denom = dx * dy;
  if( fabs(denom) < tol )
    throw singularity_error("Broyden's good method failed due to a stationary point!");
  Vector dxJ = dx;
  for(SizeType i = 0; i < dx.size(); ++i)
    for(SizeType j = 0; j < dx.size(); ++j)
      J_inv(i,j) += (dx[i] - dy[i]) * dx[j] / denom;
  
  while(true) {
    
    dx = -J_inv * y0;
    x0 += dx;
    
    if(norm_2(dx) < tol)
      return;
  
    if( ++iter > max_iter ) 
      throw maximum_iteration("Broyden's good method diverged, as detected by reaching the maximum iteration limit!");
  
    dy = f(x0) - y0;
    y0 += dy;
    
    Jdy = J_inv * dy;
    denom = dx * Jdy;
    if( fabs(denom) < tol )
      throw singularity_error("Broyden's good method failed due to a stationary point!");
    dxJ = dx * J_inv;
    
    for(SizeType i = 0; i < dx.size(); ++i)
      for(SizeType j = 0; j < dx.size(); ++j)
        J_inv(i,j) += (dx[i] - Jdy[i]) * dxJ[j] / denom;
    
  };
  
  return x0;
};