MStatus MG_curve::compute(const MPlug& plug,MDataBlock& dataBlock)
	{

		if (plug==output)
		{
			
			//MStatus
			MStatus stat;


			//Point array for the curve
			MPointArray pointArray ;

			//Get data from inputs
			MDataHandle degreeH = dataBlock.inputValue(degree);
			int degreeValue = degreeH.asInt();

			MDataHandle tmH = dataBlock.inputValue(transformMatrix);
			MMatrix tm = tmH.asMatrix();


			MArrayDataHandle inputMatrixH = dataBlock.inputArrayValue(inputMatrix);
			inputMatrixH.jumpToArrayElement(0);
			//Loop to get matrix data and convert in points

			for (int unsigned i=0;i<inputMatrixH.elementCount();i++,inputMatrixH.next())
			{
				

				MMatrix currentMatrix = inputMatrixH.inputValue(&stat).asMatrix() ;
				
				//Compensate the locator matrix
				
				MMatrix fixedMatrix = currentMatrix*tm.inverse();
				MPoint matrixP (fixedMatrix[3][0],fixedMatrix[3][1],fixedMatrix[3][2]);
				pointArray.append(matrixP);
				
			}
			
		MFnNurbsCurve curveFn;
		MFnNurbsCurveData curveDataFn;
		MObject curveData= curveDataFn.create();

		curveFn.createWithEditPoints(pointArray,degreeValue,MFnNurbsCurve::kOpen,0,0,0,curveData,&stat);
		
		MDataHandle outputH = dataBlock.outputValue(output);
		outputH.set(curveData);
		outputH.setClean();

		}


		return MS::kSuccess;
	}