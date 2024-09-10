  Basis_HGRAD_TRI_Cn_FEM<Scalar,ArrayScalar>::Basis_HGRAD_TRI_Cn_FEM( const int n ,
                                                                      const EPointType pointType ):
    Phis( n ),
    V((n+1)*(n+2)/2,(n+1)*(n+2)/2),
    Vinv((n+1)*(n+2)/2,(n+1)*(n+2)/2),
    latticePts( (n+1)*(n+2)/2 , 2 )
  {
    TEUCHOS_TEST_FOR_EXCEPTION( n <= 0, std::invalid_argument, "polynomial order must be >= 1");

    const int N = (n+1)*(n+2)/2;
    this -> basisCardinality_  = N;
    this -> basisDegree_       = n;
    this -> basisCellTopology_ = shards::CellTopology(shards::getCellTopologyData<shards::Triangle<3> >() );
    this -> basisType_         = BASIS_FEM_FIAT;
    this -> basisCoordinates_  = COORDINATES_CARTESIAN;
    this -> basisTagsAreSet_   = false;

    // construct lattice

    shards::CellTopology myTri_3( shards::getCellTopologyData< shards::Triangle<3> >() );  

    PointTools::getLattice<Scalar,FieldContainer<Scalar> >( latticePts ,
                                                            myTri_3 ,
                                                            n ,
                                                            0 ,
                                                            pointType );

    
    // form Vandermonde matrix.  Actually, this is the transpose of the VDM,
    // so we transpose on copy below.
  
    Phis.getValues( V , latticePts , OPERATOR_VALUE );

    // now I need to copy V into a Teuchos array to do the inversion
    Teuchos::SerialDenseMatrix<int,Scalar> Vsdm(N,N);
    for (int i=0;i<N;i++) {
      for (int j=0;j<N;j++) {
        Vsdm(i,j) = V(i,j);
      }
    }

    // invert the matrix
    Teuchos::SerialDenseSolver<int,Scalar> solver;
    solver.setMatrix( rcp( &Vsdm , false ) );
    solver.invert( );

    // now I need to copy the inverse into Vinv
    for (int i=0;i<N;i++) {
      for (int j=0;j<N;j++) {
        Vinv(i,j) = Vsdm(j,i);
      }
    }

  }  