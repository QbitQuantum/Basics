 void RandomSparseMatrix(SparseMatrix& A,int nnz,Real range)
 {
   A.setZero();
   for(int k=0;k<nnz;k++) {
     int i=RandInt(A.m);
     int j=RandInt(A.n);
     Real x=Rand(-range,range);
     A.insertEntry(i,j,x);
   }
 }