void FramesTest::TestFrame() {
	Vector   v(3,4,5); 
	Wrench   w(Vector(7,-1,3),Vector(2,-3,3)) ;
	Twist    t(Vector(6,3,5),Vector(4,-2,7)) ;
	Rotation R ;
	Frame F;
	Frame F2 ;
	F = Frame(Rotation::EulerZYX(10*deg2rad,20*deg2rad,-10*deg2rad),Vector(4,-2,1));
	F2=F   ;
	CPPUNIT_ASSERT_EQUAL(F,F2);
	CPPUNIT_ASSERT_EQUAL(F.Inverse(F*v),v);
	CPPUNIT_ASSERT_EQUAL(F.Inverse(F*t),t);
	CPPUNIT_ASSERT_EQUAL(F.Inverse(F*w),w);
	CPPUNIT_ASSERT_EQUAL(F*F.Inverse(v),v);
	CPPUNIT_ASSERT_EQUAL(F*F.Inverse(t),t);
	CPPUNIT_ASSERT_EQUAL(F*F.Inverse(w),w);
	CPPUNIT_ASSERT_EQUAL(F*Frame::Identity(),F);
	CPPUNIT_ASSERT_EQUAL(Frame::Identity()*F,F);
	CPPUNIT_ASSERT_EQUAL(F*(F*(F*v)),(F*F*F)*v);
	CPPUNIT_ASSERT_EQUAL(F*(F*(F*t)),(F*F*F)*t);
	CPPUNIT_ASSERT_EQUAL(F*(F*(F*w)),(F*F*F)*w);
	CPPUNIT_ASSERT_EQUAL(F*F.Inverse(),Frame::Identity());
	CPPUNIT_ASSERT_EQUAL(F.Inverse()*F,Frame::Identity());
	CPPUNIT_ASSERT_EQUAL(F.Inverse()*v,F.Inverse(v));
}