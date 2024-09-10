void TerminationCriterionTest::test_absolute_vertex_movement_edge_length()
{
  MsqPrintError err(std::cout);
  
  // define two-tet mesh where tets share a face
  double coords[] = {  0, -5, 0,
                       0,  5, 0,
                       1,  0, 0,
                       0,  0, 0,
                       0,  0, 1 };
  const unsigned long conn[] = { 4, 3, 2, 0,
                                 2, 3, 4, 1 };
  int fixed[5] = {0};
  ArrayMesh mesh( 3, 5, coords, fixed, 2, TETRAHEDRON, conn );
  
    // calculate beta 
  const double LIMIT = 1e-4; // desired absolute limit
  MeshUtil tool(&mesh);
  SimpleStats len;
  tool.edge_length_distribution( len, err );
  ASSERT_NO_ERROR(err);
  const double beta = LIMIT / (len.average() - len.standard_deviation());
  
    // initialize termination criterion
  TerminationCriterion tc;
  tc.add_absolute_vertex_movement_edge_length( beta );
  MeshDomainAssoc mesh_and_domain2 = MeshDomainAssoc(&mesh, 0);
  tc.initialize_queue( &mesh_and_domain2, 0, err ); ASSERT_NO_ERROR(err);
  
    // get a patch data
  PatchData pd;
  pd.set_mesh( &mesh );
  pd.fill_global_patch( err ); ASSERT_NO_ERROR(err);

    // test termination criteiorn
  tc.reset_inner( pd, ofEval, err );
  ASSERT_NO_ERROR(err);
  tc.reset_patch( pd, err );
  ASSERT_NO_ERROR(err);
  CPPUNIT_ASSERT(!tc.terminate());

  const double FIRST_STEP=10.0;
    // move a vertex by 10 units and check that it did not meet criterion
  pd.move_vertex( Vector3D(FIRST_STEP,0,0), 0, err );
  ASSERT_NO_ERROR(err);
  tc.accumulate_inner( pd, 0.0, 0, err );
  ASSERT_NO_ERROR(err);
  tc.accumulate_patch( pd, err );
  ASSERT_NO_ERROR(err);
  CPPUNIT_ASSERT(!tc.terminate());
  
  double test_limit = LIMIT;
    
  int idx = 0;
  for (double step = FIRST_STEP; step > test_limit; step *= 0.09) {
    idx = (idx + 1) % pd.num_free_vertices();
    pd.move_vertex( Vector3D(step,0,0), idx, err );
    ASSERT_NO_ERROR(err);
    
    tc.accumulate_inner( pd, 0.0, 0, err );
    ASSERT_NO_ERROR(err);
    tc.accumulate_patch( pd, err );
    ASSERT_NO_ERROR(err);
    CPPUNIT_ASSERT(!tc.terminate());
  }
  
  idx = (idx + 1) % pd.num_free_vertices();
  pd.move_vertex( Vector3D(0.5*test_limit,0,0), idx, err );
  ASSERT_NO_ERROR(err);

  tc.accumulate_inner( pd, 0.0, 0, err );
  ASSERT_NO_ERROR(err);
  tc.accumulate_patch( pd, err );
  ASSERT_NO_ERROR(err);
  CPPUNIT_ASSERT(tc.terminate());
}