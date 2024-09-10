void MakeTrees::Fill(ParticleSource const & source, Reconstruction const & reconstructor, std::vector<SensorRes> const & eventResults){
	v_T_x0  = source.x0();
	v_T_y0  = source.y0();
	v_T_t0  = source.t0();		
	v_T_tan = source.tan();
	v_T_off = source.off();
	tracksTree->Fill();

	v_R_reco      = reconstructor.isReco();
	v_R_nPoints   = reconstructor.getNPoints();		
	v_R_slope     = reconstructor.getSlope();
	v_R_offset    = reconstructor.getOffset();
	v_R_slopeErr  = reconstructor.getSlopeErr();
	v_R_offsetErr = reconstructor.getOffsetErr();					
	v_R_chi       = reconstructor.getChi();
	v_R_theta     = reconstructor.getTheta();
	v_R_thetaErr  = reconstructor.getThetaErr();
	recoTree->Fill();
	
	for( Int_t i = 0; i<m_layersNumber; i++){
		v_S_real     = eventResults[i].GetReal();
		v_S_blurry   = eventResults[i].GetBlurry();	
		v_S_observed = eventResults[i].GetObserved();	
		v_S_measured = eventResults[i].GetMeasured();			
		v_S_isReco   = eventResults[i].GetIsReco();		
		v_S_recoVal  = eventResults[i].GetRecoVal();	
		v_S_recoErr  = eventResults[i].GetRecoErr();	
		sensorsTree[i]->Fill();	
	}
}