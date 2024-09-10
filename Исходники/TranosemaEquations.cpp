	//Compute daily development rate for table lookup
	double CTranosemaEquations::ComputeRate(size_t s, double T)const
	{
		ASSERT(s >= 0 && s < NB_STAGES);

		//reltive developement
		double Rt = 0;

		switch (s)
		{
		case EGG:
		case PUPA: Rt = Equation1(s, T); break;
		case ADULT:	Rt = Equation2(s, T); break;
		default: ASSERT(false);
		}


		_ASSERTE(!_isnan(Rt) && _finite(Rt));
		ASSERT(Rt >= 0);
		return Rt;
	}