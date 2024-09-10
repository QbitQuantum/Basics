FastArc::FastArc(gp_Pnt A,gp_Pnt B, gp_Pnt C, bool cw, gp_Circ circ)
{
	if(!cw)
	{
		gp_Pnt temp = A;
		A = B;
		B = temp;
		circ.SetAxis(circ.Axis().Reversed());
	}


	this->A = A;
	this->B = B;
	this->C = C;
	this->cw = cw;
	this->m_circ = circ;
	this->m_flipped = false;


	a1 = atan2(A.Y()-C.Y(), A.X()-C.X());
	a2 = atan2(B.Y()-C.Y(), B.X()-C.X());
	if(a2<a1)
		a2+=2*M_PI;

	da = a2 - a1;
	rad = C.Distance(A);
	//TODO: compute how far apart the angles are, signed!
	//da = fmod(a2-a1,2*Pi);

#ifdef CHECKFASTARC
	double tax = GetXatU(0);
	double tay = GetYatU(0);
	double tbx = GetXatU(1);
	double tby = GetYatU(1);
	if(tax != A.X() || tay != A.Y() || tbx != B.X() || tby != B.Y())
	{
		int x=0;
		x++;
	}
#endif
}