void ObjectiveFunctionTests::compare_numerical_hessian( ObjectiveFunction* of,
                                                        bool diagonal_only )
{
  const double delta = 0.0001;

  MsqPrintError err(std::cout);
  PatchData pd;
  create_qm_two_tet_patch( pd, err ); 
  ASSERT_NO_ERROR( err );
  CPPUNIT_ASSERT( pd.num_free_vertices() != 0 );
  
    // get analytical Hessian from objective function
  std::vector<Vector3D> grad;
  std::vector<SymMatrix3D> diag;
  MsqHessian hess;
  hess.initialize( pd, err );
  ASSERT_NO_ERROR( err );
  double value;
  bool valid;
  if (diagonal_only)
    valid = of->evaluate_with_Hessian_diagonal( ObjectiveFunction::CALCULATE, pd, value, grad, diag, err );
  else
    valid = of->evaluate_with_Hessian( ObjectiveFunction::CALCULATE, pd, value, grad, hess, err );
  ASSERT_NO_ERROR(err); CPPUNIT_ASSERT(valid);

  
    // do numerical approximation of each block and compare to analytical value
  for (size_t i = 0; i < pd.num_free_vertices(); ++i) {
    const size_t j_end = diagonal_only ? i+1 : pd.num_free_vertices();
    for (size_t j = i; j < j_end; ++j) {
        // do numerical approximation for block corresponding to
        // coorindates for ith and jth vertices.
      Matrix3D block;    
      for (int k = 0; k < 3; ++k) {
        for (int m = 0; m < 3; ++m) {
          double dk, dm, dkm;
          Vector3D ik = pd.vertex_by_index(i);
          Vector3D im = pd.vertex_by_index(j);
          
          Vector3D delta_k(0.0); delta_k[k] = delta;
          pd.move_vertex( delta_k, i, err ); ASSERT_NO_ERROR(err);
          valid = of->evaluate( ObjectiveFunction::CALCULATE, pd, dk, true, err );
          ASSERT_NO_ERROR(err); CPPUNIT_ASSERT(valid);
          
          Vector3D delta_m(0.0); delta_m[m] = delta;
          pd.move_vertex( delta_m, j, err ); ASSERT_NO_ERROR(err);
          valid = of->evaluate( ObjectiveFunction::CALCULATE, pd, dkm, true, err );
          ASSERT_NO_ERROR(err); CPPUNIT_ASSERT(valid);
          
            // be careful here that we do the right thing if i==j
          pd.set_vertex_coordinates( ik, i, err ); ASSERT_NO_ERROR(err);
          pd.set_vertex_coordinates( im, j, err ); ASSERT_NO_ERROR(err);
          pd.move_vertex( delta_m, j, err ); ASSERT_NO_ERROR(err);
          valid = of->evaluate( ObjectiveFunction::CALCULATE, pd, dm, true, err );
          ASSERT_NO_ERROR(err); CPPUNIT_ASSERT(valid);
          
          pd.set_vertex_coordinates( ik, i, err ); ASSERT_NO_ERROR(err);
          pd.set_vertex_coordinates( im, j, err ); ASSERT_NO_ERROR(err);
          
          block[k][m] = (dkm - dk - dm + value)/(delta*delta);
        }
      }
        // compare to analytical value
      if (diagonal_only) {
        CPPUNIT_ASSERT(i == j); // see j_end above
        CPPUNIT_ASSERT(i < diag.size());
        CHECK_EQUAL_MATRICES( block, Matrix3D(diag[i]) );
      }
      else {
        Matrix3D* m = hess.get_block( i, j );
        Matrix3D* mt = hess.get_block( j, i );
        if (NULL != m) {
          CHECK_EQUAL_MATRICES( block, *m );
        }
        if (NULL != mt) {
          CHECK_EQUAL_MATRICES( transpose(block), *m );
        }
        if (NULL == mt && NULL == m) {
          CHECK_EQUAL_MATRICES( Matrix3D(0.0), block );
        }
      }
    }
  }
}