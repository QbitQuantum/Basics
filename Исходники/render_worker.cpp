//main render engine function called as multiple threads
void cRenderWorker::doWork(void)
{
	// here will be rendering thread
	QTextStream out(stdout);

	int width = image->GetWidth();
	int height = image->GetHeight();
	double aspectRatio = (double) width / height;

	PrepareMainVectors();
	PrepareReflectionBuffer();
	if (params->ambientOcclusionEnabled && params->ambientOcclusionMode == params::AOmodeMultipeRays) PrepareAOVectors();

	//init of scheduler
	cScheduler *scheduler = threadData->scheduler;

	//start point for ray-marching
	CVector3 start = params->camera;

	scheduler->InitFirstLine(threadData->id, threadData->startLine);

	bool lastLineWasBroken = false;

	//main loop for y
	for (int ys = threadData->startLine; scheduler->ThereIsStillSomethingToDo(threadData->id); ys =
			scheduler->NextLine(threadData->id, ys, lastLineWasBroken))
	{
		//skip if line is out of region
		if (ys < 0) break;
		if (ys < data->screenRegion.y1 || ys > data->screenRegion.y2) continue;

		//main loop for x
		for (int xs = 0; xs < width; xs += scheduler->GetProgressiveStep())
		{

			//break if by coincidence this thread started rendering the same line as some other
			lastLineWasBroken = false;
			if (scheduler->ShouldIBreak(threadData->id, ys))
			{
				lastLineWasBroken = true;
				break;
			}

			if (scheduler->GetProgressivePass() > 1 && xs % (scheduler->GetProgressiveStep() * 2) == 0
					&& ys % (scheduler->GetProgressiveStep() * 2) == 0) continue;

			//skip if pixel is out of region;
			if (xs < data->screenRegion.x1 || xs > data->screenRegion.x2) continue;

			//calculate point in image coordinate system
			CVector2<int> screenPoint(xs, ys);
			CVector2<double> imagePoint = data->screenRegion.transpose(data->imageRegion, screenPoint);
			imagePoint.x *= aspectRatio;

			//full dome shemisphere cut
			bool hemisphereCut = false;
			if (params->perspectiveType == params::perspFishEyeCut
					&& imagePoint.Length() > 0.5 / params->fov) hemisphereCut = true;

			//calculate direction of ray-marching
			CVector3 viewVector = CalculateViewVector(imagePoint,
																								params->fov,
																								params->perspectiveType,
																								mRot);

			//---------------- 1us -------------

			//Ray marching
			CVector3 point;
			CVector3 startRay = start;
			sRGBAfloat resultShader;
			sRGBAfloat objectColour;
			CVector3 normal;
			double depth = 1e20;
			double opacity = 1.0;

			//raymarching loop (reflections)

			if (!hemisphereCut) //in fulldome mode, will not render pixels out of the fulldome
			{
				sRayRecursionIn recursionIn;

				sRayMarchingIn rayMarchingIn;
				CVector3 direction = viewVector;
				direction.Normalize();
				rayMarchingIn.binaryEnable = true;
				rayMarchingIn.direction = direction;
				rayMarchingIn.maxScan = params->viewDistanceMax;
				rayMarchingIn.minScan = params->viewDistanceMin;
				rayMarchingIn.start = startRay;
				rayMarchingIn.invertMode = false;
				recursionIn.rayMarchingIn = rayMarchingIn;
				recursionIn.calcInside = false;
				recursionIn.resultShader = resultShader;
				recursionIn.objectColour = objectColour;

				sRayRecursionInOut recursionInOut;
				sRayMarchingInOut rayMarchingInOut;
				rayMarchingInOut.buffCount = &rayBuffer[0].buffCount;
				rayMarchingInOut.stepBuff = rayBuffer[0].stepBuff;
				recursionInOut.rayMarchingInOut = rayMarchingInOut;
				recursionInOut.rayIndex = 0;

				sRayRecursionOut recursionOut = RayRecursion(recursionIn, recursionInOut);

				resultShader = recursionOut.resultShader;
				objectColour = recursionOut.objectColour;
				depth = recursionOut.rayMarchingOut.depth;
				if (!recursionOut.found) depth = 1e20;
				opacity = recursionOut.fogOpacity;
				normal = recursionOut.normal;
			}

			sRGBfloat pixel2;
			pixel2.R = resultShader.R;
			pixel2.G = resultShader.G;
			pixel2.B = resultShader.B;
			unsigned short alpha = resultShader.A * 65535;
			unsigned short opacity16 = opacity * 65535;

			sRGB8 colour;
			colour.R = objectColour.R * 255;
			colour.G = objectColour.G * 255;
			colour.B = objectColour.B * 255;

			sRGBfloat normalFloat;
			if(image->GetImageOptional()->optionalNormal)
			{
				CVector3 normalRotated = mRotInv.RotateVector(normal);
				normalFloat.R = (1.0 + normalRotated.x) / 2.0;
				normalFloat.G = (1.0 + normalRotated.z) / 2.0;
				normalFloat.B = 1.0 - normalRotated.y;
			}

			for (int xx = 0; xx < scheduler->GetProgressiveStep(); ++xx)
			{
				for (int yy = 0; yy < scheduler->GetProgressiveStep(); ++yy)
				{
					image->PutPixelImage(screenPoint.x + xx, screenPoint.y + yy, pixel2);
					image->PutPixelColour(screenPoint.x + xx, screenPoint.y + yy, colour);
					image->PutPixelAlpha(screenPoint.x + xx, screenPoint.y + yy, alpha);
					image->PutPixelZBuffer(screenPoint.x + xx, screenPoint.y + yy, (float) depth);
					image->PutPixelOpacity(screenPoint.x + xx, screenPoint.y + yy, opacity16);
					if(image->GetImageOptional()->optionalNormal)
						image->PutPixelNormal(screenPoint.x + xx, screenPoint.y + yy, normalFloat);
				}
			}

			data->statistics.numberOfRenderedPixels++;
		}
	}

	//emit signal to main thread when finished
	emit finished();
	return;
}