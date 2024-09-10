void IRWPCA(const Matrix<double>& data,
	    Vector<double>& weights,
	    Vector<double>& mu,
	    Matrix<double>& trans,
	    const double tol/*=1E-8*/,
	    const int max_iter/*=1000*/,
	    const bool quiet/* = true*/)
{
  int d_in = data.nrows();
  int d_out = trans.nrows();
  int N = data.ncols();
  
  //check on input data
  if (mu.size() != d_in)
    mu.reallocate(d_in);

  if (trans.ncols() != d_in)
    trans.reallocate(d_out,d_in);
  
  if (weights.size() != N)
    weights.reallocate(N,1.0);
  else
    weights.SetAllTo(1.0);

  if (max_iter<1)
    throw MatVecError("max_iter must be positive");
  
  //data needed for procedure
  Matrix<double,SYM> transcov(d_in,d_in);
  Vector<double> V;
  Vector<double> weights_old;
  Vector<double> V_minus_mu;
  Matrix<double> trans_old;

  PCA(data,mu,trans);

  //Now we iterate and find the optimal weights,
  // mean, and transformation
  for(int count=1;count<max_iter;count++)
    {
      weights_old.deep_copy(weights);
      trans_old.deep_copy(trans);

      transcov = trans.Transpose() * trans;
      
      //find errors and new weights
      for(int i=0;i<N;i++)
	{
	  V.deep_copy( data.col(i) );
	  V -= mu;
	  V_minus_mu.deep_copy(V);
	  V -= transcov * V_minus_mu;
	  weights(i) = pow( blas_NRM2(V), 2 );
	}     
      
      make_weights(weights);
      WPCA(data,weights,mu,trans);
      
      //check for convergence using residuals between
      //  new weights and old weights
      weights_old -= weights;
      double Wres = blas_NRM2(weights_old);
      //  and new trans and old trans
      //trans_old -= trans;
      //double Tres = blas_NRM2(trans_old);
	
      if ( ( Wres/sqrt(N) <tol) )
	{
	  if (!quiet)
	    std::cout << "IRWPCA: converged to tol = " << tol 
		      << " in " << count << " iterations\n";
	  return;
	}
    }//end for

  //if tolerance was not reached, return an error message
  throw IterException(max_iter,tol);
}