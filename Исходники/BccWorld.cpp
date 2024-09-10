void BccWorld::createTestCurveGeometry()
{
	std::cout<<" gen 1 test curve";
	m_curves->create(1, 9);
	m_curves->counts()[0] = 9;
	
	Vector3F * cvs = m_curves->points();
	cvs[0].set(8.f + RandomFn11(), 1.f + RandomFn11(), 4.1f);
    cvs[1].set(2.f + RandomFn11(), 9.4f + RandomFn11(), 1.11f);
    cvs[2].set(14.f + RandomFn11(), 8.4f + RandomFn11(), -3.13f);
    cvs[3].set(12.f + RandomFn11(), 1.4f + RandomFn11(), 1.14f);
    cvs[4].set(19.f + RandomFn11(), 2.4f + RandomFn11(), 2.16f);
    cvs[5].set(20.f + RandomFn11(), 3.4f + RandomFn11(), 5.17f);
    cvs[6].set(18.f + RandomFn11(), 12.2f + RandomFn11(), 3.18f);
    cvs[7].set(12.f + RandomFn11(), 12.2f + RandomFn11(), 2.19f);
    cvs[8].set(13.f + RandomFn11(), 8.2f + RandomFn11(), -2.18f);
    
    for(unsigned i=0; i<9;i++) {
        cvs[i] -= Vector3F(12.f, 0.f, 0.f);
        cvs[i] *= 3.f;
    }
	
	m_allGeo = new GeometryArray;
	m_allGeo->create(1);
	
	CurveBuilder cb;
	
	unsigned i;
	for(i=0; i< 9; i++)
		cb.addVertex(cvs[i]);
	
	BezierCurve * c = new BezierCurve;
	cb.finishBuild(c);
	m_allGeo->setGeometry(c, 0);
}