bool HornRegistrationTools::FindAbsoluteOrientation(GenericCloud* lCloud,
													GenericCloud* rCloud,
													ScaledTransformation& trans,
													bool fixedScale/*=false*/)
{
    //resulting transformation (R is invalid on initialization and T is (0,0,0))
    trans.R.invalidate();
    trans.T = CCVector3(0,0,0);
	trans.s = (PointCoordinateType)1.0;

	assert(rCloud && lCloud);
	if (!rCloud || !lCloud || rCloud->size() != lCloud->size() || rCloud->size()<3)
		return false;
	unsigned count = rCloud->size();
	assert(count>2);

	//determine best scale?
	if (!fixedScale)
	{
		CCVector3 Gr = GeometricalAnalysisTools::computeGravityCenter(rCloud);
		CCVector3 Gl = GeometricalAnalysisTools::computeGravityCenter(lCloud);

		//we determine scale with the symmetrical form as proposed by Horn
		double lNorm2Sum = 0.0;
		{		
			lCloud->placeIteratorAtBegining();
			for (unsigned i=0;i<count;i++)
			{
				CCVector3 Pi = *lCloud->getNextPoint()-Gl;
				lNorm2Sum += Pi.dot(Pi);
			}
		}

		if (lNorm2Sum >= ZERO_TOLERANCE)
		{
			double rNorm2Sum = 0.0;
			{
				rCloud->placeIteratorAtBegining();
				for (unsigned i=0;i<count;i++)
				{
					CCVector3 Pi = *rCloud->getNextPoint()-Gr;
					rNorm2Sum += Pi.dot(Pi);
				}
			}

			//resulting scale
			trans.s = (PointCoordinateType)sqrt(rNorm2Sum/lNorm2Sum);
		}
		//else
		//{
		//	//shouldn't happen!
		//}
	}

	return RegistrationProcedure(lCloud,rCloud,trans,0,0,trans.s);
}