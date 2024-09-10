Color LWPGradient::evaluateColor(double frac) const
{
	if (frac <= 0.0) return head->col;
	if (frac >= 1.0) return tail->col;
	for (LWPGradientKey * k = head; k->next; k = k->next)
	{
		if (k->frac <= frac && k->next->frac >= frac)
		{
			if (k->frac == k->next->frac) return k->col;
			double alpha = (frac - k->frac) / (k->next->frac - k->frac);
			Color col = pow(Lerp(pow(k->col, 2.2), pow(k->next->col, 2.2), alpha), 1.0/2.2);
			col.clamp(0.0, 1.0);	// bloody floating point precision
			return col;
		}
	}
	HLASSERT(0, "Bad gradient evaluation");
	return head->col;
}