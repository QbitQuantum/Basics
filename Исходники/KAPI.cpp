Kinect::~Kinect(){
	unInitialize();
	if(m_pColorBuffer){
		delete [] *m_pColorBuffer;
		delete m_pColorBuffer;
		m_pColorBuffer = NULL; 
	}
	if(m_pDepthBuffer){
		delete [] *m_pDepthBuffer;
		delete m_pDepthBuffer;
		m_pDepthBuffer = NULL; 
	}
	if(m_pSkeletonFrame){
		delete *m_pSkeletonFrame;
		delete m_pSkeletonFrame;
		m_pSkeletonFrame = NULL; 
	}
}