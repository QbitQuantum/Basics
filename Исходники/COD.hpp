    /* Solve min||Ax-b|| for a matrix A whose rank is given. */
    VectorXd solve( const VectorXd& b , bool inY=false)
    {
      if( rank==0 ) return VectorXd::Zero(NC);

      /* Approximate solution using no basis transfo (result is meanigless
       * appart from the computation time pov. */
      /*
	VectorXd sol = b.head(rank);
	matrixL().solveInPlace( sol );
	VectorXd res; res.setZero(NC);
	res.head(rank)=sol; return res;
      */

      /* With plain matrices. */
      /*
	VectorXd sol = matrixUr().transpose()*b;
	matrixL().solveInPlace( sol );
	return matrixVr()*sol;
      */

      /* Using the HH representation of V. */
      assert( m_computeThinU || m_computeFullU );
      VectorXd sol; 
      if( inY ) sol.setZero(rank); else sol.setZero(NC); 
      sol.head(rank) = matrixUr().transpose()*b; 
      matrixL().solveInPlace( sol.head(rank) );
      if( ! inY ) sol.applyOnTheLeft(qrv.householderQ());
      return sol;
   }