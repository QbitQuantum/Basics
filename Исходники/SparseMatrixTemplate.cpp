void SparseMatrixTemplate_RM<T>::mulTranspose(const VectorT& a,VectorT& x) const
{
  if(x.n == 0) x.resize(n);
  if(x.n != n) {
    FatalError("Destination vector has incorrect dimensions");
  }
  if(a.n != m) {
    FatalError("Source vector has incorrect dimensions");
  }
  x.setZero();
  for(int i=0;i<m;i++) {
    for(ConstRowIterator it=rows[i].begin();it!=rows[i].end();it++)
      x(it->first) += it->second*a(i);
  }
}