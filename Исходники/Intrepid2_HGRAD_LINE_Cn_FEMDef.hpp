  Basis_HGRAD_LINE_Cn_FEM<Scalar,ArrayScalar>::Basis_HGRAD_LINE_Cn_FEM( const int n ,
									const ArrayScalar &pts ):
    latticePts_( n+1 , 1 ),
    Phis_( n ),
    V_(n+1,n+1),
    Vinv_(n+1,n+1)
  {
    const int N = n+1;
    this -> basisCardinality_  = N;
    this -> basisDegree_       = n;
    this -> basisCellTopology_ = shards::CellTopology(shards::getCellTopologyData<shards::Line<2> >() );
    this -> basisType_         = BASIS_FEM_FIAT;
    this -> basisCoordinates_  = COORDINATES_CARTESIAN;
    this -> basisTagsAreSet_   = false;


    // check validity of points
    for (int i=0;i<n;i++) {
      TEUCHOS_TEST_FOR_EXCEPTION( pts(i,0) >= pts(i+1,0) ,
			  std::runtime_error ,
			  "Intrepid2::Basis_HGRAD_LINE_Cn_FEM Illegal points given to constructor" );
    }

    // copy points int latticePts, correcting endpoints if needed
    if (std::abs(pts(0,0)+1.0) < INTREPID_TOL) {
      latticePts_(0,0) = -1.0;
    }
    else {
      latticePts_(0,0) = pts(0,0);
    }
    for (int i=1;i<n;i++) {
      latticePts_(i,0) = pts(i,0);
    }
    if (std::abs(pts(n,0)-1.0) < INTREPID_TOL) {
      latticePts_(n,0) = 1.0;
    }
    else {
      latticePts_(n,0) = pts(n,0);
    }
    
    // form Vandermonde matrix.  Actually, this is the transpose of the VDM,
    // so we transpose on copy below.
  
    Phis_.getValues( V_ , latticePts_ , OPERATOR_VALUE );

    // now I need to copy V into a Teuchos array to do the inversion
    Teuchos::SerialDenseMatrix<int,Scalar> Vsdm(N,N);
    for (int i=0;i<N;i++) {
      for (int j=0;j<N;j++) {
        Vsdm(i,j) = V_(i,j);
      }
    }

    // invert the matrix
    Teuchos::SerialDenseSolver<int,Scalar> solver;
    solver.setMatrix( rcp( &Vsdm , false ) );
    solver.invert( );

    // now I need to copy the inverse into Vinv
    for (int i=0;i<N;i++) {
      for (int j=0;j<N;j++) {
        Vinv_(i,j) = Vsdm(j,i);
      }
    }

  }  