void CartTransformation::wgsToJTSK(const Point3DGeographic <T> *p1, Point3DCartesian <T> * p2)
{
	//Deg => rad
	const T PI = 4.0 * atan(1.0), Ro = 57.29577951;

	//WGS-84
	const T A_WGS = 6378137.0000, B_WGS = 6356752.3142;
	const T E2_WGS = (A_WGS * A_WGS - B_WGS * B_WGS) / (A_WGS * A_WGS);

	//Bessel
	const T A_Bes = 6377397.1550, B_Bes = 6356078.9633;
	const T E2_Bes = (A_Bes * A_Bes - B_Bes * B_Bes) / (A_Bes * A_Bes), E_Bes = sqrt(E2_Bes);

	//Scale, Translation, Rotation
	const T m = -3.5623e-6;
	const T X0 = -570.8285, Y0 = -85.6769, Z0 = -462.8420;
	const T OMX = 4.9984 / 3600 / Ro, OMY = 1.5867 / 3600 / Ro, OMZ = 5.2611 / 3600 / Ro;

	//JTSK
	const T  FI0 = 49.5 / Ro;
	const T U0 = (49.0 + 27.0 / 60 + 35.84625 / 3600) / Ro;
	const T ALFA = 1.000597498372;
	const T LA_FERRO = (17.0 + 40.0 / 60) / Ro;
	const T K = 0.9965924869;
	const T R = 6380703.6105;
	const T UK = (59.0 + 42.0 / 60 + 42.6969 / 3600) / Ro;
	const T VK = (42.0 + 31.0 / 60 + 31.41725 / 3600) / Ro;
	const T Ro0 = 1298039.0046;
	const T S0 = 78.5 / Ro;

	//Point parameters
	T W = sqrt(1 - E2_WGS * sin(p1->getLat() / Ro) * sin(p1->getLat() / Ro));
	T M = A_WGS * (1 - E2_WGS) / (W * W * W);
	T N = A_WGS / W;

	//Transformation (B,L,H)WGS => (X,Y,Z)WGS
	T X_WGS = (N + p1->getH()) * cos(p1->getLat() / Ro) * cos(p1->getLon() / Ro);
	T Y_WGS = (N + p1->getH()) * cos(p1->getLat() / Ro) * sin(p1->getLon() / Ro);
	T Z_WGS = (N * (1 - E2_WGS) + p1->getH()) * sin(p1->getLat() / Ro);

	//Transformation (X,Y,Z)WGS =>(X,Y,Z)Bes
	T X_Bes = X0 + (m + 1) * (X_WGS + Y_WGS * OMZ - Z_WGS * OMY);
	T Y_Bes = Y0 + (m + 1) * (-X_WGS * OMZ + Y_WGS + Z_WGS * OMX);
	T Z_Bes = Z0 + (m + 1) * (X_WGS * OMY - Y_WGS * OMX + Z_WGS);

	//Transformation (X,Y,Z)Bes => (BLH)Bess
	T rad = sqrt(X_Bes * X_Bes + Y_Bes * Y_Bes);
	T la = 2 * atan(Y_Bes / (rad + X_Bes));
	T p = atan((A_Bes * Z_Bes) / (B_Bes * rad));
	T t = (Z_Bes + E2_Bes * A_Bes * A_Bes / B_Bes * pow(sin(p), 3)) / (rad - E2_Bes * A_Bes * pow(cos(p), 3));
	T fi = atan(t);
	T H = sqrt(1 + t * t) * (rad - A_Bes / sqrt(1 + (1 - E2_Bes) * t * t));

	//Transformation (fi,la)Bes => (u,v)sphere  (Gauss conformal projection)
	la = la + LA_FERRO;
	T ro = 1 / K * pow(tan(fi / 2 + PI / 4) * pow((1 - E_Bes * sin(fi)) / (1 + E_Bes * sin(fi)), E_Bes / 2), ALFA);
	T u = 2 * atan(ro) - PI / 2;
	T v = ALFA * la;

	//Transformation (u,v)sphere => (s,d)sphere
	T s = asin(sin(UK) * sin(u) + cos(UK) * cos(u) * cos(VK - v));
	T d = asin(sin(VK - v) * cos(u) / cos(s));

	//Transformation (s,d)sphere => (Ro,Eps)plane (Lambert conformal projection)
	T n = sin(S0);
	T Ro_JTSK = Ro0 * pow((tan((S0 / 2 + PI / 4)) / (tan(s / 2 + PI / 4))), n);
	T eps_JTSK = n * d;

	//(Ro, eps) => (x,y)
	T X_JTSK = Ro_JTSK * cos(eps_JTSK);
	T Y_JTSK = Ro_JTSK * sin(eps_JTSK);

	//Set computed parameters to the projected point
	if (p1->getPointLabel() != NULL)
	{
		p2->setPointLabel(p1->getPointLabel());
	}

	p2->setX(X_JTSK);
	p2->setY(Y_JTSK);
	p2->setZ(H);
}