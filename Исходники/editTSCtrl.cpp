void EditTSCtrl::renderCameraAxis()
{
   GFXDEBUGEVENT_SCOPE( Editor_renderCameraAxis, ColorI::WHITE );

   static MatrixF sRotMat(EulerF( (M_PI_F / -2.0f), 0.0f, 0.0f));

   MatrixF camMat = mLastCameraQuery.cameraMatrix;
   camMat.mul(sRotMat);
   camMat.inverse();

   MatrixF axis;
   axis.setColumn(0, Point3F(1, 0, 0));
   axis.setColumn(1, Point3F(0, 0, 1));
   axis.setColumn(2, Point3F(0, -1, 0));
   axis.mul(camMat);

   Point3F forwardVec, upVec, rightVec;
	axis.getColumn( 2, &forwardVec );
	axis.getColumn( 1, &upVec );
	axis.getColumn( 0, &rightVec );

   Point2I pos = getPosition();
	F32 offsetx = pos.x + 20.0;
	F32 offsety = pos.y + getExtent().y - 42.0; // Take the status bar into account
	F32 scale = 15.0;

   // Generate correct drawing order
   ColorI c1(255,0,0);
   ColorI c2(0,255,0);
   ColorI c3(0,0,255);
	ColorI tc;
	Point3F *p1, *p2, *p3, *tp;
	p1 = &rightVec;
	p2 = &upVec;
	p3 = &forwardVec;
	if(p3->y > p2->y)
	{
		tp = p2; tc = c2;
		p2 = p3; c2 = c3;
		p3 = tp; c3 = tc;
	}
	if(p2->y > p1->y)
	{
		tp = p1; tc = c1;
		p1 = p2; c1 = c2;
		p2 = tp; c2 = tc;
	}

   PrimBuild::begin( GFXLineList, 6 );
		//*** Axis 1
		PrimBuild::color(c1);
		PrimBuild::vertex3f(offsetx, offsety, 0);
		PrimBuild::vertex3f(offsetx+p1->x*scale, offsety-p1->z*scale, 0);

		//*** Axis 2
		PrimBuild::color(c2);
		PrimBuild::vertex3f(offsetx, offsety, 0);
		PrimBuild::vertex3f(offsetx+p2->x*scale, offsety-p2->z*scale, 0);

		//*** Axis 3
		PrimBuild::color(c3);
		PrimBuild::vertex3f(offsetx, offsety, 0);
		PrimBuild::vertex3f(offsetx+p3->x*scale, offsety-p3->z*scale, 0);
   PrimBuild::end();
}