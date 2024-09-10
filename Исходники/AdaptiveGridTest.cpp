bool AdaptiveGridTest::init()
{
	float gz = 128.f;
	setColorScale(.43f / gz);
	setNodeDrawSize(gz * .008f);
	m_msh.fillBox(BoundingBox(-250.f, -50.f, -250.f,
								 250.f,  50.f,  250.f), gz);
	
	m_distFunc.addSphere(Vector3F(    9.f, 17.f, -1.f), 27.f );
	m_distFunc.addSphere(Vector3F(-54.f, -13.f, -1.f), 64.f );
	m_distFunc.addSphere(Vector3F(38.f, -10.f, -22.f), 21.1f );
	m_distFunc.addSphere(Vector3F(-100.f, -3420.1f, -100.f), 3400.f );
	
#define MAX_BUILD_LEVEL 5
#define MAX_BUILD_ERROR .5f
	m_msh.adaptiveBuild<BDistanceFunction>(&m_distFunc, MAX_BUILD_LEVEL, MAX_BUILD_ERROR);
	std::cout<<"\n triangulating"<<std::endl;
	m_msh.triangulateFront();
	
#if 0
	checkTetraVolumeExt<DistanceNode, ITetrahedron>(m_msh.nodes(), m_msh.numTetrahedrons(),
						m_msh.tetrahedrons() );
#endif

	std::cout.flush();
	return true;
}