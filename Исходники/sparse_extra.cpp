bool test_random_setter(SparseMatrix<Scalar,Options>& sm, const DenseType& ref, const std::vector<Vector2i>& nonzeroCoords)
{
  {
    sm.setZero();
    SetterType w(sm);
    std::vector<Vector2i> remaining = nonzeroCoords;
    while(!remaining.empty())
    {
      int i = internal::random<int>(0,static_cast<int>(remaining.size())-1);
      w(remaining[i].x(),remaining[i].y()) = ref.coeff(remaining[i].x(),remaining[i].y());
      remaining[i] = remaining.back();
      remaining.pop_back();
    }
  }
  return sm.isApprox(ref);
}