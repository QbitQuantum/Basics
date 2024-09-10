MStatus MG_nurbsRivet::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
		


			
			//Get recompute value
			MDataHandle recomputeH = dataBlock.inputValue(recompute);
	  		bool recomputeV = recomputeH.asBool();





			//input mesh 
			MDataHandle inputNurbsH = dataBlock.inputValue(inputNurbSurface);
			MObject inputNurb = inputNurbsH.asNurbsSurfaceTransformed();
			MMatrix offsetMatrixV = dataBlock.inputValue(offsetMatrix).asMatrix(); 
			
			double U,V;
			MFnNurbsSurface nurbsFn ;
			nurbsFn.setObject(inputNurb);
			
			MStatus stat;

			if (recomputeV == true)
			{

			
				//input point 

				MDataHandle inputPointH = dataBlock.inputValue(inputPoint);
				MPoint inputP = inputPointH.asVector();
				

				
				
				MPoint closestP = nurbsFn.closestPoint(inputP,NULL,NULL,false,1e+99,MSpace::kObject);

				
				

				stat = nurbsFn.getParamAtPoint(closestP,U,V,MSpace::kObject);
				
				


				//Handle to U and V 
				MDataHandle uValueH =dataBlock.outputValue(uValue);
				MDataHandle vValueH =dataBlock.outputValue(vValue);
				
				uValueH.set(float(U));
				vValueH.set(float(V));
				uValueH.setClean();
				vValueH.setClean();



				MDataHandle recomputeOutH = dataBlock.outputValue(recompute);

	
			}  

			MDataHandle uH = dataBlock.inputValue(uValue);
			MDataHandle vH = dataBlock.inputValue(vValue);
			
			U = uH.asFloat(); 
			V = vH.asFloat();

			MPoint outPoint ;
			MVector uVec ;
			MVector vVec;
			MVector normal;
			//Get point
			stat = nurbsFn.getPointAtParam(U,V,outPoint,MSpace::kObject);
			
			//Since if getting both the U and V tangent was leading to some little rotation snapping 
			//of the rivet I only used the U tangent and calculated the next one by dot product
			//of the normal and U tangent leading to a 100% stable rivet 
			nurbsFn.getTangents(U,V,uVec,vVec,MSpace::kObject);
			
			uVec.normalize();
			vVec.normalize();
			MVector vVecCross;

	


			//Get normal



			

			normal = nurbsFn.normal(U,V,MSpace::kObject);
			normal.normalize();

			vVecCross =(uVec^normal);
			
			
			



			//Build the maya matrix 
			double myMatrix[4][4]={	{ uVec.x, uVec.y , uVec.z, 0},
									{ normal[0], normal[1] , normal[2], 0},
									{vVecCross.x, vVecCross.y , vVecCross.z, 0},
									{ outPoint[0], outPoint[1] , outPoint[2], 1}};
 
			
			MMatrix rotMatrix (myMatrix);
			MMatrix offsetMatrixV2 = offsetMatrixV*rotMatrix; 
			 
			MTransformationMatrix matrixFn(offsetMatrixV2);
			double angles[3];
			MTransformationMatrix::RotationOrder rotOrder;
			rotOrder =MTransformationMatrix::kXYZ;
			matrixFn.getRotation(angles,rotOrder,MSpace::kObject );
			//get back radians value
			double radX,radY,radZ;

			radX=angles[0]; 
			radY=angles[1];
			radZ=angles[2];
 
			

			//convert to degree

			double rotX,rotY,rotZ;

			rotX = radX*toDeg;
			rotY = radY*toDeg;
			rotZ = radZ*toDeg;
			

			MDataHandle outputRotateH = dataBlock.outputValue(outputRotate);
			
			outputRotateH.set3Double(rotX,rotY,rotZ);
			outputRotateH.setClean();

			//let set the output matrix too

			MDataHandle outMH= dataBlock.outputValue(outputMatrix);
			outMH.set(rotMatrix);
			outMH.setClean();

			MDataHandle outputH = dataBlock.outputValue(output);
			outputH.set(offsetMatrixV2[3][0],offsetMatrixV2[3][1],offsetMatrixV2[3][2]);
			outputH.setClean();

			 

 

		return MS::kSuccess;
	}