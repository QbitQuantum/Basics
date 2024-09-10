void RowEchelon<T>::getNullspace(MatrixT& N) const
{
  if(R.isEmpty()) {
    N.clear();
    return;
  }
  Assert((int)firstEntry.size() == R.m+1);

  int nullspace_dims=getNull();
  N.resize(R.n,nullspace_dims);

  //first get nullspace vectors from 0 to firstEntry[0]
  int i,j,numVecs=0;
  int m=R.m,n=R.n;
  for(j=0;j<firstEntry[0];j++) {
    N.setCol(numVecs,0); N(j,numVecs)=1;
    numVecs++;
  }
  for(i=0;i<m;i++) {
    //cancel out the i'th entry
    for(j=firstEntry[i]+1;j<firstEntry[i+1];j++) {
      if(numVecs >= N.n) {
	LOG4CXX_INFO(KrisLibrary::logger(),"Num nullspace vectors "<<numVecs);
	LOG4CXX_INFO(KrisLibrary::logger(),"Found more nullspace vectors than found dims, row "<<i);
	LOG4CXX_INFO(KrisLibrary::logger(),MatrixPrinter(R));
      }
      Assert(numVecs < N.n);
      VectorT xn; N.getColRef(numVecs,xn);
      xn.setZero();
      xn[firstEntry[i]] = R(i,j);
      xn[j] = -R(i,firstEntry[i]);

      //cancel out all the entries prior to i 
      int isave=i;
      i--;
      for(;i>=0;i--) {
        VectorT ri; R.getRowRef(i,ri);
	//calculate alpha
	int ji=firstEntry[i];
	Assert(ji != n);
	int ji2=firstEntry[i+1]; //(i+1==m?n:firstEntry[i+1]);
	T alpha;
	if(ji2 == n) alpha = Zero;
        else {
          VectorT rji2; rji2.setRef(ri,ji2,1,R.n-ji2);
          VectorT xji2; xji2.setRef(xn,ji2,1,R.n-ji2);
          alpha = xji2.dot(rji2);
        }
	xn[ji] = -alpha/ri[ji];
      }
      i=isave;
      numVecs++;
    }
  }
  if(numVecs != nullspace_dims) {
    LOG4CXX_ERROR(KrisLibrary::logger(),"Error in counting rank in row-eschelon decomposition");
    LOG4CXX_INFO(KrisLibrary::logger(),"Num nullspace vectors "<<numVecs);
    LOG4CXX_INFO(KrisLibrary::logger(),MatrixPrinter(R));
  }
  Assert(numVecs == nullspace_dims);

  /*
  VectorT temp;
  for(int i=0;i<numVecs;i++) {
    VectorT xi; N.getColRef(i,xi);
    xi.print();
    R.mul(xi,temp);
    if(temp.maxAbsElement() > 1e-4) {
      LOG4CXX_INFO(KrisLibrary::logger(),"Nullspace vector "<<i<<" not in null space!");
      xi.print();
      LOG4CXX_INFO(KrisLibrary::logger(),"Result = "); temp.print();
      KrisLibrary::loggerWait();
    }
  }
  */

  VectorT* N0 = new VectorT[nullspace_dims];
  for(int i=0;i<nullspace_dims;i++) N.getColRef(i,N0[i]);
  int num=OrthonormalBasis(N0,N0,nullspace_dims);
  Assert(num == nullspace_dims);
  delete [] N0;
}