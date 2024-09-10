Vec<2> ExplicitCurve2d :: Normal (double t) const
{
  Vec<2> tan = EvalPrime (t);
  tan.Normalize();
  return Vec<2> (tan(1), -tan(0));
}