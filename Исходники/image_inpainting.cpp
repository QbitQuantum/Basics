nTupleVolume * inpaint_image( nTupleVolume *imgVolIn, nTupleVolume *occVolIn,
patchMatchParameterStruct *patchMatchParams, inpaintingParameterStruct *inpaintingParams)
{
	
	// ******************************************************************** //
	// **** AUTOMATICALLY DETERMINE NUMBER OF LEVELS, IF NOT SPECIFIED **** //
	// ******************************************************************** //
	if (inpaintingParams->nLevels == -1)
	{
		inpaintingParams->nLevels =
			determine_multiscale_level_number(occVolIn,imgVolIn->patchSizeX,imgVolIn->patchSizeY);
	}
	display_inpainting_parameters(inpaintingParams);
	display_patch_match_parameters(patchMatchParams);
	
	nTupleVolume *imgVolOut;

	// ************************** //
	// **** CREATE PYRDAMIDS **** //
	// ************************** //
	nTupleVolumePyramid imgVolPyramid = create_nTupleVolume_pyramid(imgVolIn, inpaintingParams->nLevels);
	nTupleVolumePyramid occVolPyramid = create_nTupleVolume_pyramid_binary(occVolIn, inpaintingParams->nLevels);
	featurePyramid featuresVolPyramid;
	if (inpaintingParams->useFeatures == true)
	{
		double t1 = clock();
		featuresVolPyramid = create_feature_pyramid(imgVolIn, occVolIn, inpaintingParams->nLevels);
		MY_PRINTF("\n\nFeatures calculation time: %f\n",((double)(clock()-t1)) / CLOCKS_PER_SEC);
	}
	else
	{
		featuresVolPyramid.normGradX = NULL;
        featuresVolPyramid.normGradY = NULL;
        featuresVolPyramid.nLevels = -1;
	}

	//create structuring element
	nTupleVolume *structElDilate = create_structuring_element("rectangle", imgVolIn->patchSizeX, imgVolIn->patchSizeY);
	
	//show_patch_match_parameters(patchMatchParams);
	
	// ****************************************** //
	// ************* START INPAINTING *********** //
	// ****************************************** //
	
	nTupleVolume *imgVol,*normGradXvol,*normGradYvol;
	nTupleVolume *shiftVol=NULL;
	for (int level=( (inpaintingParams->nLevels)-1); level>=0; level--)
	{
		printf("Current pyramid level : %d\n",level);
		nTupleVolume *imgVolPrevious,*occVol,*occVolDilate;

		if (patchMatchParams->maxShiftDistance != -1)		
			patchMatchParams->maxShiftDistance =
			(float)( (patchMatchParams->maxShiftDistance)/( pow((float)SUBSAMPLE_FACTOR,(float)level) ));
		
		imgVol = copy_image_nTuple(imgVolPyramid[level]);
		occVol = copy_image_nTuple(occVolPyramid[level]);
		//create dilated occlusion
		occVolDilate = imdilate(occVol, structElDilate);
		
		if (featuresVolPyramid.nLevels >= 0)
		{
			normGradXvol = copy_image_nTuple((featuresVolPyramid.normGradX)[level]);
			normGradYvol = copy_image_nTuple((featuresVolPyramid.normGradY)[level]);
			//attach features to patchMatch parameters
			patchMatchParams->normGradX = normGradXvol;
			patchMatchParams->normGradY = normGradYvol;
		}
					
		//initialise solution
		if (level == ((inpaintingParams->nLevels)-1))
		{
			shiftVol = new nTupleVolume(4,imgVol->xSize,imgVol->ySize,imgVol->patchSizeX,imgVol->patchSizeY,IMAGE_INDEXING);
			shiftVol->set_all_image_values(0);
			printf("\nInitialisation started\n\n\n");
			initialise_inpainting(imgVol,occVol,featuresVolPyramid,shiftVol,patchMatchParams);
			patchMatchParams->partialComparison = 0;
			printf("\nInitialisation finished\n\n\n");
			
			if (featuresVolPyramid.nLevels >= 0)	//retrieve features from the pointers in the patchMatch parameters
			{
				normGradXvol = patchMatchParams->normGradX;
				normGradYvol = patchMatchParams->normGradY;
			}
		}
		else	//reconstruct current solution
		{
			if (featuresVolPyramid.nLevels >= 0)
			{
				reconstruct_image_and_features(imgVol, occVol,
				normGradXvol, normGradYvol,
				shiftVol, SIGMA_COLOUR);
			}
			else
			{
				reconstruct_image(imgVol,occVol,shiftVol,SIGMA_COLOUR);
				//write_shift_map(shiftVol,fileOut);
			}
		}
		
		calclulate_patch_distances(imgVol,imgVol,shiftVol,occVolDilate,patchMatchParams);
		
		//iterate ANN search and reconstruction
		int iterationNb = 0;
		imageDataType residual = FLT_MAX;
		while( (residual > (inpaintingParams->residualThreshold) ) && (iterationNb < (inpaintingParams->maxIterations) ) )
		{
			//copy current imgVol
			imgVolPrevious = copy_image_nTuple(imgVol);
			patch_match_ANN(imgVol,imgVol,shiftVol,occVolDilate,occVolDilate,patchMatchParams);
			if (featuresVolPyramid.nLevels >= 0)
			{
				reconstruct_image_and_features(imgVol, occVol,
        			normGradXvol, normGradYvol,
        			shiftVol, SIGMA_COLOUR);
			}
			else
				reconstruct_image(imgVol,occVol,shiftVol,SIGMA_COLOUR);
			residual = calculate_residual(imgVol,imgVolPrevious,occVol);
			if (patchMatchParams->verboseMode == true)
				printf("Iteration number %d, residual = %f\n",iterationNb,residual);
			iterationNb++;
		}
		//upsample shift volume, if we are not on the finest level
		if (level >0)
		{	
			nTupleVolume * shiftVolTemp = up_sample_image(shiftVol, SUBSAMPLE_FACTOR,imgVolPyramid[level-1]);
			delete(shiftVol);
			shiftVol = copy_image_nTuple(shiftVolTemp);
			shiftVol->multiply((imageDataType)SUBSAMPLE_FACTOR);
			delete(shiftVolTemp);
		}
		else
		{
			reconstruct_image(imgVol,occVol,shiftVol,SIGMA_COLOUR,3);
			imgVolOut = new nTupleVolume(imgVol);
		}
		//destroy structures
		delete(imgVol);
		delete(imgVolPrevious);
		delete(occVol);
		delete(occVolDilate);
		if (featuresVolPyramid.nLevels >= 0)
		{
			delete normGradXvol;
			delete normGradYvol;
		}
	}
	
	// ************************** //
	// **** DELETE STRUCTURES *** //
	// ************************** //
	for (int i=0; i< (inpaintingParams->nLevels); i++)
	{
		delete(imgVolPyramid[i]);
		delete(occVolPyramid[i]);
	}
	delete(imgVolPyramid);
	delete(occVolPyramid);
	delete(shiftVol);
	delete_feature_pyramid(featuresVolPyramid);
	delete(patchMatchParams);
	
	printf("Inpainting finished !\n");

	return(imgVolOut);
}