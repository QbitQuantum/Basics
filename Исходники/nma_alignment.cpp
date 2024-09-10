// Compute fitness =========================================================
double ObjFunc_nma_alignment::eval(Vector X, int *nerror) {
	int dim = global_nma_prog->numberOfModes;

	for (int i = 0; i < dim; i++) {
		global_nma_prog->trial(i) = X[i];
	}

	int pyramidLevelDisc = 1;
	int pyramidLevelCont = (global_nma_prog->currentStage == 1) ? 1 : 0;

	FileName fnRandom = global_nma_prog->createDeformedPDB(pyramidLevelCont);
	const char * randStr = fnRandom.c_str();

	if (global_nma_prog->currentStage == 1) {
		global_nma_prog->performCompleteSearch(fnRandom, pyramidLevelDisc);
	} else {
		double rot, tilt, psi, xshift, yshift;
		MetaData DF;

		rot = global_nma_prog->bestStage1(
				VEC_XSIZE(global_nma_prog->bestStage1) - 5);
		tilt = global_nma_prog->bestStage1(
				VEC_XSIZE(global_nma_prog->bestStage1) - 4);
		psi = global_nma_prog->bestStage1(
				VEC_XSIZE(global_nma_prog->bestStage1) - 3);
		xshift = global_nma_prog->bestStage1(
				VEC_XSIZE(global_nma_prog->bestStage1) - 2);
		yshift = global_nma_prog->bestStage1(
				VEC_XSIZE(global_nma_prog->bestStage1) - 1);

		size_t objId = DF.addObject();
		FileName fnDown = formatString("%s_downimg.xmp", randStr);
		DF.setValue(MDL_IMAGE, fnDown, objId);
		DF.setValue(MDL_ENABLED, 1, objId);
		DF.setValue(MDL_ANGLE_ROT, rot, objId);
		DF.setValue(MDL_ANGLE_TILT, tilt, objId);
		DF.setValue(MDL_ANGLE_PSI, psi, objId);
		DF.setValue(MDL_SHIFT_X, xshift, objId);
		DF.setValue(MDL_SHIFT_Y, yshift, objId);

		DF.write(formatString("%s_angledisc.xmd", randStr));
		copyImage(global_nma_prog->currentImgName.c_str(), fnDown.c_str());
	}
	double fitness = global_nma_prog->performContinuousAssignment(fnRandom,
			pyramidLevelCont);

	runSystem("rm", formatString("-rf %s* &", randStr));

	global_nma_prog->updateBestFit(fitness, dim);
	return fitness;
}