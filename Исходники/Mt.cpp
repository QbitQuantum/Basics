int main() {
	
	/* Set up module test environment */
	
	std::ofstream  ofs ("./output/mt_results.txt", std::ofstream::out);
	
	/* TC_1: Open two random MIT-BIH measurements */
	ofs<<"**************** MT TC 1 ****************"<<std::endl;
	ofs<<"testcase 1: open two random MIT-BIH measurements"<<std::endl;
	
	EcgSigPrep esp_1(MT_MIT_BIH_MEASUREMENT_NAME_1_STR, MT_NUM_OF_LEADS_INT, MT_NUM_OF_SAMPLES_1_INT);
	EcgSigPrep esp_2(MT_MIT_BIH_MEASUREMENT_NAME_2_STR, MT_NUM_OF_LEADS_INT, MT_NUM_OF_SAMPLES_2_INT);
	
	ofs<<"testcase 1: DONE"<<std::endl<<std::endl;
	
	/* TC_2: Print out the first loaded beat from the first recording. Then load the next beat and print that out as well. */
	
	ofs<<"**************** MT TC 2 ****************"<<std::endl;
	ofs<<"testcase 2: Print out the first loaded beat from the first recording"<<std::endl;
	
	Eigen::MatrixXd signal = *(esp_1.getSignal());
	
	ofs<<signal.transpose()<<std::endl;
	
	ofs<<"testcase 2: Load next beat and print it"<<std::endl;
	
	esp_1.getNextSegment();
	signal = *(esp_1.getSignal());
	ofs<<signal.transpose()<<std::endl;
	
	ofs<<"testcase 2: DONE"<<std::endl<<std::endl;	
	
	/* TC_3: Set the dilatation and translation of the second beat. Print out results. */
	
	ofs<<"**************** MT TC 3 ****************"<<std::endl;
	ofs<<"testcase 3: Apply dilatation and translation to signal. Print results."<<std::endl;
	
	Hermite H(signal.cols());
	Eigen::MatrixXd dilatTransSig = signal;
	dilatTransSig = esp_1.setDilatTrans(MT_SAMPLE_DILATATION_DOUBLE, MT_SAMPLE_TRANSLATION_DOUBLE, H.get_ort_fun_roots(), dilatTransSig);
	
	ofs<<dilatTransSig.transpose()<<std::endl;
	
	ofs<<"testcase 3: DONE"<<std::endl<<std::endl;	
	
	/* TC_4: Test getter functions. Print results. */
	
	ofs<<"**************** MT TC 4 ****************"<<std::endl;
	ofs<<"testcase 4: Test getter functions."<<std::endl;
	
	ofs<<"sigPrep::getSignal()"<<std::endl;
	ofs<<esp_1.getSignal()->transpose()<<std::endl<<std::endl;
	
	ofs<<"sigPrep::getEntireSignal()"<<std::endl;
	ofs<<esp_1.getEntireSignal()->transpose()<<std::endl<<std::endl;
	
	ofs<<"sigPrep::getSigFirstVal()"<<std::endl;
	ofs<<esp_1.getSigFirstVal()<<std::endl<<std::endl;
	
	ofs<<"sigPrep::getSigLastVal()"<<std::endl;
	ofs<<esp_1.getSigLastVal()<<std::endl<<std::endl;
	
	ofs<<"sigPrep::getSigMaxVal()"<<std::endl;
	ofs<<esp_1.getSigMaxVal()<<std::endl<<std::endl;
	
	ofs<<"EcgsigPrep::getDilat()"<<std::endl;
	ofs<<esp_1.getDilat()<<std::endl<<std::endl;
	
	ofs<<"EcgsigPrep::getTrans()"<<std::endl;
	ofs<<esp_1.getTrans()<<std::endl<<std::endl;
	
	ofs<<"testcase 4: DONE"<<std::endl<<std::endl;	
	
	/* Clear up module test environment */
	ofs.close();
	
	return 0;
}