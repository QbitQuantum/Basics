Scalar MASA::ad_cns_2d_crossterms<Scalar>::eval_exact_v(Scalar x, Scalar y)
{
  using std::cos;

  Scalar exact_v;
  exact_v = v_0 + v_x * cos(a_vx * PI * x / L) * v_y * cos(a_vy * PI * y / L);
  return exact_v;
}