Matrix::pVector SymMatrix::GetEigenvalueRange(int indexOfLow, int indexOfHigh)
{
   assert(indexOfLow >= 0);
   assert(indexOfLow <= indexOfHigh);
   assert(indexOfHigh < GetSize());
     //lapack parameter list
   char jobz = 'N';//compute eigenvalues only
   char range = 'I';//all eigenvalues will be found
   char uplo = 'U';//upper triangle of A is stored
   int n = GetSize();
   int lda = GetSize();
   double vl, vu;//no referenced when range = 'A' or 'I'
   int il = indexOfLow + 1, iu = indexOfHigh + 1;//1<= il <= iu <= N
   double abstol = 0;//absolute error tolerance for the eigenvalues
   int m;//the total number of eigenvalues found
   vector<double> w(n);//the first m elements contain the selected
                       //eigenvalues in ascending order
   vector<double> z(n*n);//not referenced when jobz = 'N', but this
			 //reserved space
   int ldz = n;//the leading dimension of the array z
   vector<int> isuppz(2 * n);//the support of the eigenvectors in Z
   int info;
   //got the optimal size of workspace
   int lwork = -1;//the dimension of the array work
   int liwork = -1;//the dimension of the array iwork
   vector<double> work(26 * n);//workspace
   vector<int> iwork(10 * n);//workspace
   //query the optimal size
   dsyevr_(&jobz, &range, &uplo, &n, GetData(), &lda, &vl, &vu, &il, &iu, &abstol,
	   &m, w.data(), z.data(), &ldz, isuppz.data(), work.data(), &lwork,
	   iwork.data(), &liwork, &info);
   if(info == 0)
   {//succeed
      lwork = ceil(work[0]);
      liwork = iwork[0];
      //reallocate
      work.resize(lwork);
      iwork.resize(liwork);
   }
   else
   {
      return pVector();
   }
   //compute
   dsyevr_(&jobz, &range, &uplo, &n, GetData(), &lda, &vl, &vu, &il, &iu, &abstol,
	   &m, w.data(), z.data(), &ldz, isuppz.data(), work.data(), &lwork,
	   iwork.data(), &liwork, &info);
   if(info == 0)
   {
      pVector result(new Vector());
      result->assign(w.begin(), w.begin() + (indexOfHigh - indexOfLow) + 1);
      return result;
   }
   else
      return pVector();
}