  Basis_HCURL_TRI_In_FEM<Scalar,ArrayScalar>::Basis_HCURL_TRI_In_FEM( const int n ,
                                                                      const EPointType pointType ):
    Phis_( n ),
    coeffs_( (n+1)*(n+2) , n*(n+2) )
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

    // first, need to project the basis for Nedelec space onto the
    // orthogonal basis of degree n
    // get coefficients of PkHx

    Teuchos::SerialDenseMatrix<int,Scalar> V1(bigN, N);

    // basis for the space is 
    // { (phi_i,0) }_{i=0}^{scalarLittleN-1} ,
    // { (0,phi_i) }_{i=0}^{scalarLittleN-1} ,
    // { (x,y) \times phi_i}_{i=scalarLittleN}^{scalarBigN-1}
    // { (x,y) \times phi = (y phi , -x \phi)
    // columns of V1 are expansion of this basis in terms of the basis
    // for P_{n}^2

    // these two loops get the first two sets of basis functions
    for (int i=0;i<scalarLittleN;i++) {
      V1(i,i) = 1.0;
      V1(scalarBigN+i,scalarLittleN+i) = 1.0;
    }

    // now I need to integrate { (x,y) \times phi } against the big basis
    // first, get a cubature rule.
    CubatureDirectTriDefault<Scalar,ArrayScalar > myCub( 2 * n );
    ArrayScalar cubPoints( myCub.getNumPoints() , 2 );
    ArrayScalar cubWeights( myCub.getNumPoints() );
    myCub.getCubature( cubPoints , cubWeights );

    // tabulate the scalar orthonormal basis at cubature points
    ArrayScalar phisAtCubPoints( scalarBigN , myCub.getNumPoints() );
    Phis_.getValues( phisAtCubPoints , cubPoints , OPERATOR_VALUE );

    // now do the integration
    for (int i=0;i<n;i++) {
      for (int j=0;j<scalarBigN;j++) { // int (x,y) phi_i \cdot (phi_j,0)
        V1(j,littleN+i) = 0.0;
        for (int k=0;k<myCub.getNumPoints();k++) {
          V1(j,littleN+i) -= 
            cubWeights(k) * cubPoints(k,1) 
            * phisAtCubPoints(scalarSmallestN+i,k) 
            * phisAtCubPoints(j,k);
        }
      }
      for (int j=0;j<scalarBigN;j++) {  // int (x,y) phi_i \cdot (0,phi_j)
        V1(j+scalarBigN,littleN+i) = 0.0;
        for (int k=0;k<myCub.getNumPoints();k++) {
          V1(j+scalarBigN,littleN+i) += 
            cubWeights(k) * cubPoints(k,0) 
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
      CubatureDirectLineGauss<Scalar> edgeRule( 2*n - 1 );
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


    ArrayScalar edgePts( n , 2 );
    ArrayScalar phisAtEdgePoints( scalarBigN , n );
    ArrayScalar edgeTan(2);
    
    for (int i=0;i<3;i++) {  // loop over edges
      CellTools<Scalar>::getReferenceEdgeTangent( edgeTan , 
                                                  i , 
                                                  this->basisCellTopology_ );
      /* multiply by 2.0 to account for a Jacobian in Pavel's definition */
      for (int j=0;j<2;j++) {
        edgeTan(j) *= 2.0;
      }

      CellTools<Scalar>::mapToReferenceSubcell( edgePts ,
                                                linePts ,
                                                1 ,
                                                i ,
                                                this->basisCellTopology_ );

      Phis_.getValues( phisAtEdgePoints , edgePts , OPERATOR_VALUE );

      // loop over points (rows of V2)
      for (int j=0;j<n;j++) {
        // loop over orthonormal basis functions (columns of V2)
        for (int k=0;k<scalarBigN;k++) {
          V2(n*i+j,k) = edgeTan(0) * phisAtEdgePoints(k,j);
          V2(n*i+j,k+scalarBigN) = edgeTan(1) * phisAtEdgePoints(k,j);
        }
      }
    }

    // remaining nodes are x- and y- components at internal points, if n > 1
    // this code is exactly the same as it is for HDIV

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
      Phis_.getValues( phisAtInternalPoints , internalPoints , OPERATOR_VALUE );

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
        coeffs_(i,j) = Csdm(i,j);
      }
    }

    initializeTags();
    this->basisTagsAreSet_ = true;
  }  