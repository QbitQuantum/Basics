/// Compute Log Likelihood of the Factor Analysis model
double FactorAnalysisStat::getLLK(SegCluster &selectedSegments,MixtureGD &model,FeatureServer&fs,Config & config){
	if (verbose) cout << "(FactorAnalysisStat) Compute Likelihood" << endl;		
	double llk=0.0;
	MixtureGDStat &acc=_ss.createAndStoreMixtureStat(model);		
	Seg *seg;        
	selectedSegments.rewind(); 	
	while((seg=selectedSegments.getSeg())!=NULL){                           	
		unsigned long begin=seg->begin()+fs.getFirstFeatureIndexOfASource(seg->sourceName()); 
		fs.seekFeature(begin);
		Feature f;
		for (unsigned long idxFrame=0;idxFrame<seg->length();idxFrame++){
			fs.readFeature(f); 
			acc.computeAndAccumulateLLK(f,1.0,TOP_DISTRIBS_NO_ACTION);
		}		
	}				
	llk= acc.getMeanLLK();
	_ss.deleteMixtureStat(acc);		
return llk;
};