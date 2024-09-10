void ExampleNLPObjGrad::imp_calc_f(const Vector& x, bool newx
  , const ZeroOrderInfo& zero_order_info) const
{
  using AbstractLinAlgPack::dot;
  assert_is_initialized();
  f(); // assert f is set
  TEUCHOS_TEST_FOR_EXCEPTION( n() != x.dim(), std::length_error, "ExampleNLPObjGrad::imp_calc_f(...)"  );
  // f(x) = (obj_scale/2) * sum( x(i)^2, for i = 1..n )
  *zero_order_info.f = obj_scale_ / 2.0 * dot(x,x);
}