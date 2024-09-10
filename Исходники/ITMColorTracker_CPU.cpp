void ITMColorTracker_CPU::G_oneLevel(float *gradient, float *hessian, ITMPose *pose) const
{
	int noTotalPoints = trackingState->pointCloud->noTotalPoints;

	Vector4f projParams;
  if (type == ITMLibSettings::TRACKER_ODOMETRY_COLOR) {
    projParams.setValues(view->calib->intrinsics_d.projectionParamsSimple.all);
  } else {
    projParams.setValues(view->calib->intrinsics_rgb.projectionParamsSimple.all);
  }
	projParams.x /= 1 << levelId; projParams.y /= 1 << levelId;
	projParams.z /= 1 << levelId; projParams.w /= 1 << levelId;

	Matrix4f M = pose->GetM();

	Vector2i imgSize = viewHierarchy->levels[levelId]->rgb->noDims;

	float scaleForOcclusions;

	bool rotationOnly = iterationType == TRACKER_ITERATION_ROTATION;
	int numPara = rotationOnly ? 3 : 6, startPara = rotationOnly ? 3 : 0, numParaSQ = rotationOnly ? 3 + 2 + 1 : 6 + 5 + 4 + 3 + 2 + 1;

	float globalGradient[6], globalHessian[21];
	for (int i = 0; i < numPara; i++) globalGradient[i] = 0.0f;
	for (int i = 0; i < numParaSQ; i++) globalHessian[i] = 0.0f;

	Vector4f *locations = trackingState->pointCloud->locations->GetData(MEMORYDEVICE_CPU);
	Vector4f *colours = trackingState->pointCloud->colours->GetData(MEMORYDEVICE_CPU);
	Vector4u *rgb = viewHierarchy->levels[levelId]->rgb->GetData(MEMORYDEVICE_CPU);
	Vector4s *gx = viewHierarchy->levels[levelId]->gradientX_rgb->GetData(MEMORYDEVICE_CPU);
	Vector4s *gy = viewHierarchy->levels[levelId]->gradientY_rgb->GetData(MEMORYDEVICE_CPU);

	for (int locId = 0; locId < noTotalPoints; locId++)
	{
		float localGradient[6], localHessian[21];

		bool isValidPoint = computePerPointGH_rt_Color(localGradient, localHessian, locations, colours, rgb, imgSize, locId,
			projParams, M, gx, gy, numPara, startPara);

		if (isValidPoint)
		{
			for (int i = 0; i < numPara; i++) globalGradient[i] += localGradient[i];
			for (int i = 0; i < numParaSQ; i++) globalHessian[i] += localHessian[i];
		}
	}

	scaleForOcclusions = (float)noTotalPoints / countedPoints_valid;
	if (countedPoints_valid == 0) { scaleForOcclusions = 1.0f; }

	for (int para = 0, counter = 0; para < numPara; para++)
	{
		gradient[para] = globalGradient[para] * scaleForOcclusions;
		for (int col = 0; col <= para; col++, counter++) hessian[para + col * numPara] = globalHessian[counter] * scaleForOcclusions;
	}
	for (int row = 0; row < numPara; row++)
	{
		for (int col = row + 1; col < numPara; col++) hessian[row + col * numPara] = hessian[col + row * numPara];
	}
}