BendDeformer::BendDeformer(
		TimeValue t, ModContext &mc,
		float angle, float dir, int naxis, 
		float from, float to, int doRegion,
		Matrix3& modmat, Matrix3& modinv) 
	{	
	this->doRegion = doRegion;
	this->from = from;
	this->to   = to;
	Matrix3 mat;
	Interval valid;	
	time   = t;	

	tm = modmat;
	invtm = modinv;
	mat.IdentityMatrix();
	
	switch (naxis) {
		case 0: mat.RotateY( -HALFPI );	 break; //X
		case 1: mat.RotateX( HALFPI );  break; //Y
		case 2: break;  //Z
		}
	mat.RotateZ(DegToRad(dir));	
	SetAxis(mat);	
	assert (mc.box);
	bbox = *mc.box;
	CalcR(naxis,DegToRad(angle));
	
	// Turn this off for a sec.
	this->doRegion = FALSE;
		
	float len  = to-from;
	float rat1, rat2;
	if (len==0.0f) {
		rat1 = rat2 = 1.0f;
	} else {
		rat1 = to/len;
		rat2 = from/len;
		}
	Point3 pt;
	tmAbove.IdentityMatrix();
	tmAbove.Translate(Point3(0.0f,0.0f,-to));
	tmAbove.RotateY(DegToRad(angle * rat1));
	tmAbove.Translate(Point3(0.0f,0.0f,to));
	pt = Point3(0.0f,0.0f,to);
	tmAbove.Translate((Map(0,pt*invtm)*tm)-pt);

	tmBelow.IdentityMatrix();
	tmBelow.Translate(Point3(0.0f,0.0f,-from));
	tmBelow.RotateY(DegToRad(angle * rat2));	
	tmBelow.Translate(Point3(0.0f,0.0f,from));
	pt = Point3(0.0f,0.0f,from);
	tmBelow.Translate((Map(0,pt*invtm)*tm)-pt);	
	
	this->doRegion = doRegion;

	} 