void n_tentacle::computeSlerp(const MMatrix &matrix1, const MMatrix &matrix2, const MFnNurbsCurve &curve, double parameter, double blendRot, double iniLength, double curveLength, double stretch, double globalScale, int tangentAxis, MVector &outPos, MVector &outRot)
{
	//curveLength = curve.length()
        double lenRatio = iniLength / curveLength;

        MQuaternion quat1;
        quat1 = matrix1;

        MQuaternion quat2;
        quat2 = matrix2;

        this->bipolarityCheck(quat1, quat2);

    //need to adjust the parameter in order to maintain the length between elements, also for the stretch
		MVector tangent;
		MPoint pointAtParam;
		MPoint finaPos;
        double p = lenRatio * parameter * globalScale;
        double finalParam = p + (parameter - p) * stretch;
		
		if(curveLength * finalParam > curveLength)
		{
		  double lengthDiff = curveLength - (iniLength * parameter);

		  double param = curve.knot(curve.numKnots() - 1);
		  tangent = curve.tangent(param, MSpace::kWorld);
		  tangent.normalize();

		  curve.getPointAtParam(param, pointAtParam, MSpace::kWorld);
		  finaPos = pointAtParam;
		  pointAtParam += (- tangent) * lengthDiff;
		  //MGlobal::displayInfo("sdf");
		}
		else
		{
		  double param = curve.findParamFromLength(curveLength * finalParam);
		  tangent = curve.tangent(param, MSpace::kWorld);
		  tangent.normalize();
		  curve.getPointAtParam(param, pointAtParam, MSpace::kWorld);
		  
		}
                

        MQuaternion slerpQuat = slerp(quat1, quat2, blendRot);
        MMatrix slerpMatrix = slerpQuat.asMatrix();

        int axisId = abs(tangentAxis) - 1;
		MVector slerpMatrixYAxis = MVector(slerpMatrix(axisId, 0), slerpMatrix(axisId, 1), slerpMatrix(axisId, 2));
		slerpMatrixYAxis.normalize();
		if(tangentAxis < 0)
			slerpMatrixYAxis = - slerpMatrixYAxis;

		double angle = tangent.angle(slerpMatrixYAxis);
		MVector axis =  slerpMatrixYAxis ^ tangent;
		axis.normalize();

		MQuaternion rotationToSnapOnCurve(angle, axis);

		MQuaternion finalQuat = slerpQuat * rotationToSnapOnCurve;
		MEulerRotation finalEuler = finalQuat.asEulerRotation();

		outRot.x = finalEuler.x;
		outRot.y = finalEuler.y;
		outRot.z = finalEuler.z;
		outPos = pointAtParam;
}