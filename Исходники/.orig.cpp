int saveApost(Config &config)
{

 bool writeAllFeature=true; // Output a vector for all input vectors (selected and not selected vectors) - DEFAULT=on
 if (config.existsParam("writeAllFeatures")) writeAllFeature=config.getParam("writeAllFeatures").toBool();    // Define if all the feature     (selected or not) should be written

	String modelname = config.getParam("inputModelFilename");
	  String inputFeatureFileName =config.getParam("inputFeatureFilename");          // input feature - could be a simple feature file or a list of filenames
        XLine inputFeatureFileNameList;                                                // The (feature) input filename list
        if (inputFeatureFileName.endsWith(".lst")){                                   // If the file parameter is the name of a XList file
	   XList inputFileNameXList(inputFeatureFileName,config);                   // Read the filename list file
           inputFeatureFileNameList=inputFileNameXList.getAllElements();            // And put the filename in a list if the file is a list of feature filenames
			      }
      else {                                                                         // It was a simple feature file and not a filename list
	          inputFeatureFileNameList.addElement(inputFeatureFileName);                   // add the filename in the list
		    }

	try{

        // read UBM 
        MixtureServer _ms(config);
	StatServer _ss(config);
        _ms.loadMixtureGD(config.getParam("inputWorldFilename"));
        MixtureGD & UBM=_ms.getMixtureGD((unsigned long) 0);
        MixtureGDStat &acc=_ss.createAndStoreMixtureStat(UBM);

	unsigned long _vsize=UBM.getVectSize();
	unsigned long _mixsize=UBM.getDistribCount();
        // Loop over the list of feature files
	String *file;
	String labelSelectedFrames;
        unsigned long codeSelectedFrame;
	while ((file=inputFeatureFileNameList.getElement())!= NULL){         
	String & featureFilename=(*file);

	FeatureServer fs(config,featureFilename);
	FeatureServer fs_out(config,featureFilename);
        SegServer segmentsServer;
        LabelServer labelServer;
        initializeClusters(featureFilename,segmentsServer,labelServer,config);
        verifyClusterFile(segmentsServer,fs,config);
	labelSelectedFrames=config.getParam("labelSelectedFrames");
        codeSelectedFrame=labelServer.getLabelIndexByString(labelSelectedFrames);
        SegCluster& selectedSegments=segmentsServer.getCluster(codeSelectedFrame); 

	// Compute Occupations and Statistics
        acc.resetOcc();
        Seg *seg;
        selectedSegments.rewind();
        String currentSource="";
        while((seg=selectedSegments.getSeg())!=NULL){
                unsigned long begin=seg->begin()+fs.getFirstFeatureIndexOfASource(seg->sourceName());    // Idx of the first frame of the current file in the feature server
                if (currentSource!=seg->sourceName()) {
                currentSource=seg->sourceName();
                if (verbose)cout << "Processing speaker["<<currentSource<<"]"<< endl;
                }

                fs.seekFeature(begin);
                Feature f;

	for (unsigned long idxFrame=0;idxFrame<seg->length();idxFrame++){
                                fs.readFeature(f);
                                acc.computeAndAccumulateOcc(f);
                                RealVector <double> aPost=acc.getOccVect();

				Feature tmpF;
				for(unsigned long k=0;k<_mixsize;k++) {
				tmpF[k]=aPost[k];
				}

                                fs_out.addFeature(f);
}

}

// Writing apost probabilities to file 

	cout << "Writing to: " << featureFilename << endl;
		        FeatureFileWriter w(featureFilename, config);   // build a featurefile writer to output the features (real features)
			SegServer fakeSegServer;
		        if (writeAllFeature) {                  // Output all the features- feature count id the same SegServer fakeSegServer;                                          // Create a new fake segment server
		            fakeSegServer.createCluster(0);       // Create a new cluster
		            SegCluster& fakeSeg=fakeSegServer.getCluster(0);    // Get the cluster               
		            fakeSeg.add(fakeSegServer.createSeg(0,fs_out.getFeatureCount(),codeSelectedFrame, labelSelectedFrames,featureFilename));            // Add a segment with all the features
		            outputFeatureFile(config,fs_out,fakeSeg,w);   // output all the features - giving the same file length
		        }
		        else
		            outputFeatureFile(config,fs_out,selectedSegments, w);    // Output only the selected features - giving a shorter output 


}


	}	
	catch (Exception& e){cout << e.toString().c_str() << endl;}
return 0;
}