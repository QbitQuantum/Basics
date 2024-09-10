void getCuTransformParams(cu_param &para_trans, paramfile &params, vec3 &campos,
		vec3 &lookat, vec3 &sky) 
{
	int xres = params.find<int>("xres", 800), yres = params.find<int>("yres", xres);
	double fov = params.find<double>("fov", 45); //in degrees
	double fovfct = tan(fov * 0.5 * degr2rad);
	float64 xfac = 0.0, dist = 0.0;

	sky.Normalize();
	vec3 zaxis = (lookat - campos).Norm();
	vec3 xaxis = crossprod(sky, zaxis).Norm();
	vec3 yaxis = crossprod(zaxis, xaxis);
	TRANSFORM trans;
	trans.Make_General_Transform(TRANSMAT(xaxis.x, xaxis.y, xaxis.z, yaxis.x, yaxis.y, yaxis.z,
					zaxis.x, zaxis.y, zaxis.z, 0, 0, 0));
	trans.Invert();
	TRANSFORM trans2;
	trans2.Make_Translation_Transform(-campos);
	trans2.Add_Transform(trans);
	trans = trans2;
	bool projection = params.find<bool>("projection", true);

	if (!projection) 
	{
		float64 dist = (campos - lookat).Length();
		float64 xfac = 1. / (fovfct * dist);
		cout << " Field of fiew: " << 1. / xfac * 2. << endl;
	}

	float minrad_pix = params.find<float>("minrad_pix", 1.);

	//retrieve the parameters for transformation
	for (int i = 0; i < 12; i++)
		para_trans.p[i] = trans.Matrix().p[i];
	para_trans.projection = projection;
	para_trans.xres = xres;
	para_trans.yres = yres;
	para_trans.fovfct = fovfct;
	para_trans.dist = dist;
	para_trans.xfac = xfac;
	para_trans.minrad_pix = minrad_pix;
}