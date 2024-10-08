  Basis_HDIV_TRI_In_FEM<Scalar,ArrayScalar>::Basis_HDIV_TRI_In_FEM( const int n ,
                                                                    const EPointType pointType ):
    Phis( n ),
    coeffs( (n+1)*(n+2) , n*(n+2) )
  {
    const int N = n*(n+2);
    this -> basisCardinality_  = N;
    this -> basisDegree_       = n;
    this -> basisCellTopology_ = shards::CellTopology(shards::getCellTopologyData<shards::Triangle<3> >() );
    this -> basisType_         = BASIS_FEM_FIAT;
    this -> basisCoordinates_  = COORDINATES_CARTESIAN;
    this -> basisTagsAreSet_   = false;


    const int littleN = n*(n+1);   // dim of (P_{n-1})^2 -- smaller space
    const int bigN = (n+1)*(n+2);  // dim of (P_{n})^2 -- larger space
    const int scalarSmallestN = (n-1)*n / 2;
    const int scalarLittleN = littleN/2;
    const int scalarBigN = bigN/2;

    // first, need to project the basis for RT space onto the
    // orthogonal basis of degree n
    // get coefficients of PkHx

    Teuchos::SerialDenseMatrix<int,Scalar> V1(bigN, N);

    // basis for the space is 
    // { (phi_i,0) }_{i=0}^{scalarLittleN-1} ,
    // { (0,phi_i) }_{i=0}^{scalarLittleN-1} ,
    // { (x,y) . phi_i}_{i=scalarLittleN}^{scalarBigN-1}
    // columns of V1 are expansion of this basis in terms of the basis
    // for P_{n}^2

    // these two loops get the first two sets of basis functions
    for (int i=0;i<scalarLittleN;i++) {
      V1(i,i) = 1.0;
      V1(scalarBigN+i,scalarLittleN+i) = 1.0;
    }

    // now I need to integrate { (x,y) phi } against the big basis
    // first, get a cubature rule.
    CubatureDirectTriDefault<Scalar,ArrayScalar > myCub( 2 * n );
    ArrayScalar cubPoints( myCub.getNumPoints() , 2 );
    ArrayScalar cubWeights( myCub.getNumPoints() );
    myCub.getCubature( cubPoints , cubWeights );

    // tabulate the scalar orthonormal basis at cubature points
    ArrayScalar phisAtCubPoints( scalarBigN , myCub.getNumPoints() );
    Phis.getValues( phisAtCubPoints , cubPoints , OPERATOR_VALUE );

    // now do the integration
    for (int i=0;i<n;i++) {
      for (int j=0;j<scalarBigN;j++) { // int (x,y) phi_i \cdot (phi_j,0)
        V1(j,littleN+i) = 0.0;
        for (int k=0;k<myCub.getNumPoints();k++) {
          V1(j,littleN+i) += 
            cubWeights(k) * cubPoints(k,0) 
            * phisAtCubPoints(scalarSmallestN+i,k) 
            * phisAtCubPoints(j,k);
        }
      }
      for (int j=0;j<scalarBigN;j++) {  // int (x,y) phi_i \cdot (0,phi_j)
        V1(j+scalarBigN,littleN+i) = 0.0;
        for (int k=0;k<myCub.getNumPoints();k++) {
          V1(j+scalarBigN,littleN+i) += 
            cubWeights(k) * cubPoints(k,1) 
            * phisAtCubPoints(scalarSmallestN+i,k) 
            * phisAtCubPoints(j,k);
        }
      }
    }

    //std::cout << V1 << "\n";

    
    // next, apply the RT nodes (rows) to the basis for (P_n)^2 (columns)
    Teuchos::SerialDenseMatrix<int,Scalar> V2(N , bigN);

    // first 3 * degree nodes are normals at each edge
    // get the points on the line
    ArrayScalar linePts( n , 1 );
    if (pointType == POINTTYPE_WARPBLEND) {
      CubatureDirectLineGauss<Scalar> edgeRule( n );
      ArrayScalar edgeCubWts( n );
      edgeRule.getCubature( linePts , edgeCubWts );
    }
    else if (pointType == POINTTYPE_EQUISPACED ) {
      shards::CellTopology linetop(shards::getCellTopologyData<shards::Line<2> >() );

      PointTools::getLattice<Scalar,ArrayScalar >( linePts , 
                                                              linetop ,
                                                              n+1 , 1 ,
                                                              POINTTYPE_EQUISPACED );
    }
    // holds the image of the line points 
    ArrayScalar edgePts( n , 2 );
    ArrayScalar phisAtEdgePoints( scalarBigN , n );

    // these are scaled by the appropriate edge lengths.
    const Scalar nx[] = {0.0,1.0,-1.0};
    const Scalar ny[] = {-1.0,1.0,0.0};
    
    for (int i=0;i<3;i++) {  // loop over edges
      CellTools<Scalar>::mapToReferenceSubcell( edgePts ,
                                                linePts ,
                                                1 ,
                                                i ,
                                                this->basisCellTopology_ );

      Phis.getValues( phisAtEdgePoints , edgePts , OPERATOR_VALUE );

      // loop over points (rows of V2)
      for (int j=0;j<n;j++) {
        // loop over orthonormal basis functions (columns of V2)
        for (int k=0;k<scalarBigN;k++) {
          V2(n*i+j,k) = nx[i] * phisAtEdgePoints(k,j);
          V2(n*i+j,k+scalarBigN) = ny[i] * phisAtEdgePoints(k,j);
        }
      }
    }

    // next map the points to each edge


    // remaining nodes are divided into two pieces:  point value of x
    // components and point values of y components.  These are
    // evaluated at the interior of a lattice of degree + 1, For then
    // the degree == 1 space corresponds classicaly to RT0 and so gets
    // no internal nodes, and degree == 2 corresponds to RT1 and needs
    // one internal node per vector component.
    const int numInternalPoints = PointTools::getLatticeSize( this->getBaseCellTopology() ,
                                                              n + 1 ,
                                                              1 );

    if (numInternalPoints > 0) {
      ArrayScalar internalPoints( numInternalPoints , 2 );
      PointTools::getLattice<Scalar,ArrayScalar >( internalPoints ,
                                                              this->getBaseCellTopology() , 
                                                              n + 1 ,
                                                              1 ,
                                                              pointType );
      
      ArrayScalar phisAtInternalPoints( scalarBigN , numInternalPoints );
      Phis.getValues( phisAtInternalPoints , internalPoints , OPERATOR_VALUE );
      
      // copy values into right positions of V2
      for (int i=0;i<numInternalPoints;i++) {
        for (int j=0;j<scalarBigN;j++) {
          // x component
          V2(3*n+i,j) = phisAtInternalPoints(j,i);
          // y component
          V2(3*n+numInternalPoints+i,scalarBigN+j) = phisAtInternalPoints(j,i);
        }
      }
    }
//     std::cout << "Nodes on big basis\n";
//     std::cout << V2 << "\n";
//     std::cout << "End nodes\n";

    Teuchos::SerialDenseMatrix<int,Scalar> Vsdm( N , N );

    // multiply V2 * V1 --> V
    Vsdm.multiply( Teuchos::NO_TRANS , Teuchos::NO_TRANS , 1.0 , V2 , V1 , 0.0 );

//     std::cout << "Vandermonde:\n";
//     std::cout << Vsdm << "\n";
//     std::cout << "End Vandermonde\n";
    
    Teuchos::SerialDenseSolver<int,Scalar> solver;
    solver.setMatrix( rcp( &Vsdm , false ) );
    solver.invert( );

    Teuchos::SerialDenseMatrix<int,Scalar> Csdm( bigN , N );
    Csdm.multiply( Teuchos::NO_TRANS , Teuchos::NO_TRANS , 1.0 , V1 , Vsdm , 0.0 );

    //    std::cout << Csdm << "\n";

    for (int i=0;i<bigN;i++) {
      for (int j=0;j<N;j++) {
        coeffs(i,j) = Csdm(i,j);
      }
    }
  }  