std::vector<SensorRes> SiDetector::getResults(ParticleSource const & particle) const {
	
	std::vector<SensorRes> sensors = std::vector<SensorRes>();
	
	Float_t real;
	Float_t blurry;	
	Bool_t  observed;	
	Float_t measured;
			
	for( Int_t i =0; i<m_layersNumber; i++){
		
		// Real Value
		real = particle.tan() * ( m_firstLayer + i*m_deltaLayer ) + particle.off();

		// Blurry Value		
		switch( m_blurryOpt ){
			case('u'):
			case('U'):
				blurry = randomsForBlurry[i]->Uniform(real-m_blurryPar,real+m_blurryPar);
				break;
			default:
				blurry = randomsForBlurry[i]->Gaus(real,m_blurryPar);			
		}	

		// Is observed?			
		observed = blurry > -m_acceptance && blurry < m_acceptance && randomsForObserved[i]->Rndm() < m_pixelEfficiency;

		// Where is measured?						
		if( observed ){
			Int_t pixelNum = blurry / m_pixelSize;
			if( blurry > 0 ){
				measured = ( 0.5 + pixelNum ) * m_pixelSize;
			} else {
				measured = ( -0.5 + pixelNum ) * m_pixelSize;
			}
		} else {
			measured = 9999.0;
		}
		
		sensors.push_back( SensorRes( real, blurry, observed, measured ) );
	}
		
		
	return sensors;
}