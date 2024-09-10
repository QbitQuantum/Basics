MStatus AimNode::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MStatus	status;
	if ((plug == aOutputRotate) || (plug == aOutputRotateX) ||
		(plug == aOutputRotateY) || (plug == aOutputRotateZ))
	{
		// the matrix to aim at 
		MMatrix driverMatrix = dataBlock.inputValue(aDriverMatrix).asMatrix();
		// the matrix to use as the upVector
		MMatrix upVectorMatrix = dataBlock.inputValue(aUpVectorMatrix).asMatrix();
		MVector inputTranslate = dataBlock.inputValue(aInputTranslate).asVector();
		MMatrix parentInverse = dataBlock.inputValue(aParentInverseMatrix).asMatrix();

		driverMatrix *= parentInverse;
		upVectorMatrix *= parentInverse;
		//extract the translation from the matrices
		MVector driverMatrixPos(driverMatrix[3][0],
			driverMatrix[3][1],
			driverMatrix[3][2]);

		MVector upVectorMatrixPos(upVectorMatrix[3][0],
			upVectorMatrix[3][1],
			upVectorMatrix[3][2]);

		//get the vectors
		MVector aimVector = driverMatrixPos - inputTranslate;
		MVector upVector = upVectorMatrixPos - inputTranslate;
		
		//upVector *= parentInverse;
		aimVector.normalize();
		upVector.normalize();

		//perpendicter vector
		MVector cross = aimVector ^ upVector;
		upVector = cross ^ aimVector;

		//build rotationMatrix
		double tmpMatrix[4][4]{{aimVector.x, aimVector.y, aimVector.z, 0},
									{upVector.x, upVector.y, upVector.z, 0},
									{cross.x, cross.y, cross.z, 0},
									{inputTranslate[0], inputTranslate[1], inputTranslate[2], 1}};

		//eulerRotations
		MMatrix rotationMatrix(tmpMatrix);
		MTransformationMatrix matrixfn(rotationMatrix);
		MEulerRotation eular = matrixfn.eulerRotation();

		dataBlock.outputValue(aOutputRotate).set(eular.x, eular.y, eular.z);
		dataBlock.outputValue(aOutputRotate).setClean();

	}

	return MS::kSuccess;

}