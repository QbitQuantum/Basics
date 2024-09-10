void ObjectiveFunctionTest::test_compute_ana_hessian_tet_scaled()
{
    MsqPrintError err(cout);
    PatchData tetPatch;
    create_qm_two_tet_patch(tetPatch,err);
    ASSERT_NO_ERROR(err);

    // creates a mean ratio quality metric ...
    IdealWeightInverseMeanRatio* mean_ratio = new IdealWeightInverseMeanRatio(err);
    CPPUNIT_ASSERT(!err);
    mean_ratio->set_averaging_method(QualityMetric::SUM);

    // ... and builds an objective function with it
    LPtoPTemplate LP2(mean_ratio, 2, err);
    LP2.set_dividing_by_n(true);

    MsqHessian H;
    std::vector<Vector3D> g;
    double dummy;
    H.initialize(tetPatch, err);
    CPPUNIT_ASSERT(!err);
    LP2.evaluate_with_Hessian(ObjectiveFunction::CALCULATE, tetPatch, dummy, g, H, err);
    CPPUNIT_ASSERT(!err);
    CPPUNIT_ASSERT_EQUAL( tetPatch.num_free_vertices(), g.size() );

    Matrix3D mat00(" 2.44444  0.2566   0.181444 "
                   " 0.2566   2.14815  0.104757 "
                   " 0.181444 0.104757 2.07407 ");

    mat00*=.5;

    Matrix3D mat13(" 5.47514 3.16659    9.83479 "
                   " -1.11704 -5.29718 -3.67406 "
                   " 10.3635 -13.5358  -15.5638 ");

    mat13*=.5;

    CPPUNIT_ASSERT_MATRICES_EQUAL( mat00, *H.get_block(0,0), 1e-4 );
    CPPUNIT_ASSERT_MATRICES_EQUAL( mat13, *H.get_block(1,3), 1e-4 );

//    cout << H <<endl;
    delete mean_ratio;
}