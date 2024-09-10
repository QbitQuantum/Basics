MStatus MG_softIk::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
		
		//Get data 
		if ((plug == outputTranslate) ||(plug == downScale) ||(plug == upScale) )
		{
		
		MMatrix startMatrixV = dataBlock.inputValue(startMatrix).asMatrix();
		MMatrix endMatrixV = dataBlock.inputValue(endMatrix).asMatrix();
		double upInitLengthV = dataBlock.inputValue(upInitLength).asDouble();
		double downInitLengthV = dataBlock.inputValue(downInitLength).asDouble();
		double softDistanceV = dataBlock.inputValue(softDistance).asDouble();
		double stretchV= dataBlock.inputValue(stretch).asDouble();
		double slideV = dataBlock.inputValue(slide).asDouble();
		double globalScaleV  = dataBlock.inputValue(globalScale).asDouble();
		upInitLengthV = upInitLengthV*(slideV*2)*globalScaleV ;
		downInitLengthV = downInitLengthV*((1 - slideV)*2)*globalScaleV;
 		double chainLength = upInitLengthV + downInitLengthV ;
		
		
		MVector startVector (startMatrixV[3][0] , startMatrixV[3][1] , startMatrixV[3][2] );
		MVector endVector  (endMatrixV[3][0] , endMatrixV[3][1] , endMatrixV[3][2] );
		MVector currentLengthVector  = endVector -  startVector ;
		
		double  currentLength = currentLengthVector.length() ;
		double startSD = chainLength - softDistanceV;
		
		double stretchParam = 1;
		double upScaleOut = 1 ;
		double downScaleOut = 1 ;
		
		if (startSD <= currentLength)
		{
		
		  if (softDistanceV != 0 )
		  {
		  double expParam =  ( currentLength - startSD) / softDistanceV;
		  expParam*= -1 ;
		  double softLength = ( (softDistanceV *(1 - exp ( expParam)) )+  startSD );
		  currentLengthVector.normalize();
		  currentLengthVector*=softLength ;
		  
		   if (stretchV != 0 )
		  {
		    
		     stretchParam = (currentLength/softLength  );
		     double delta = (stretchParam - 1); 
		     delta*=stretchV;
		     stretchParam = 1*(1 + delta);
		     currentLengthVector  *=(1 + delta );
		      
		  }
		  }
		  
		  
		}
		

		//slide computing
		
		upScaleOut = (slideV*2) *stretchParam ;
		downScaleOut = ((1 - slideV)*2)*stretchParam;
		
		
		MVector outVec =  startVector + currentLengthVector;
		dataBlock.outputValue(outputTranslate).setMVector(outVec);
		dataBlock.outputValue(outputTranslate).setClean();
		
		dataBlock.outputValue(downScale).set(downScaleOut);
		dataBlock.outputValue(downScale).setClean();
		
		
		dataBlock.outputValue(upScale).set(upScaleOut);
		dataBlock.outputValue(upScale).setClean();
		
		

		}
		return MS::kSuccess;
	}