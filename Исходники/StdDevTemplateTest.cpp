void StdDevTemplateTest::test_hessian_fails_sqr()
{
  MsqError err;
  double value;
  bool rval;
  vector<Vector3D> grad;
  MsqHessian Hess;
  Hess.initialize( patch(), err );
  CPPUNIT_ASSERT(!MSQ_CHKERR(err));
  
  OFTestQM metric( &value, 1 );
  VarianceTemplate func( &metric );
  rval = func.evaluate_with_Hessian( ObjectiveFunction::CALCULATE, patch(), value, grad, Hess, err );
  CPPUNIT_ASSERT(err);
}