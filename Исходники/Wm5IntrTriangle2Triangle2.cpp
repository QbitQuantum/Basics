void IntrTriangle2Triangle2<Real>::ComputeTwo (Configuration& cfg,
        const Vector2<Real> V[3], const Vector2<Real>& D, int i0, int i1,
        int i2)
{
	cfg.Map = M12;
	cfg.Index[0] = i0;
	cfg.Index[1] = i1;
	cfg.Index[2] = i2;
	cfg.Min = D.Dot(V[i0] - V[i1]);
	cfg.Max = (Real)0;
}