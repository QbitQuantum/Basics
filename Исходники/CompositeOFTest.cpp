void CompositeOFTest::test_multiply_hessian()
{
    MsqError err;
    PatchData pd;
    create_twelve_hex_patch( pd, err );
    ASSERT_NO_ERROR( err );

    // this should always fail because the Hessian is not sparse
    CompositeOFMultiply OF( &LP1, &LP2 );
    double value;
    MsqHessian hess;
    hess.initialize( pd, err );
    ASSERT_NO_ERROR(err);
    std::vector<Vector3D> grad;
    OF.evaluate_with_Hessian( ObjectiveFunction::CALCULATE, pd, value, grad, hess, err );
    CPPUNIT_ASSERT(err);
}