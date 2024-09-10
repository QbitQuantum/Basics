double CalculateDistanceMinPlane(const sParamRender &params, const cNineFractals &fractals,
	const CVector3 planePoint, const CVector3 direction, const CVector3 orthDirection,
	bool *stopRequest)
{
	// the plane is defined by the 'planePoint' and the orthogogonal 'direction'
	// the method will return the minimum distance from the plane to the fractal
	double distStep = 0.0;
	CVector3 point = planePoint;
	const double detail = 0.5;
	const int transVectorAngles = 5;

	CVector3 rotationAxis = planePoint;
	rotationAxis.Normalize();

	while (distStep == 0 || distStep > 0.00001)
	{
		CVector3 pointNextBest(0, 0, 0);
		double newDistStepMin = 0;
		for (int i = 0; i <= transVectorAngles; i++)
		{
			const double angle = (double(i) / transVectorAngles) * 2.0 * M_PI;
			CVector3 transversalVect = orthDirection;
			transversalVect = transversalVect.RotateAroundVectorByAngle(rotationAxis, angle);
			transversalVect.Normalize();
			CVector3 pointNext = point + direction * distStep;
			if (i > 0) pointNext += transversalVect * distStep / 2.0;
			const sDistanceIn in(pointNext, 0, false);
			sDistanceOut out;
			const double dist = CalculateDistance(params, fractals, in, &out);
			const double newDistStep = dist * detail * 0.5;
			if (newDistStep < newDistStepMin || newDistStepMin == 0)
			{
				pointNextBest = pointNext;
				newDistStepMin = newDistStep;
			}
		}
		if (newDistStepMin > 1000) newDistStepMin = 1000;
		if (distStep != 0 && newDistStepMin > distStep) break;
		distStep = newDistStepMin;
		point = pointNextBest;
		// qDebug() << "pointNextBest" << pointNextBest.Debug();
		if (point.Length() > 1000000)
		{
			WriteLog("CalculateDistanceMinPlane(): surface not found!", 1);
			return 0;
		}
		gApplication->processEvents();
		if (*stopRequest)
		{
			return 0;
		}
	}
	return CVector3(point - planePoint).Dot(direction);
}