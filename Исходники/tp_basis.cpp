  void
  TensorProductBasis<BASIS0,BASIS1>::apply_Tjinv(const int j, const V& x, V& y) const
  { 
    // T_j^{-1}=diag(G_{j0},I)*...*diag(G_{j-1},I)*G_j
    V z(x);
    apply_Gj(j, x, y);
    for (int k = j-1; k >= j0(); k--) {
      z.swap(y);
      apply_Gj(k, z, y);
      for (int i = Deltasize(k+1); i < Deltasize(j+1); i++)
	y[i] = z[i];
    }
  }