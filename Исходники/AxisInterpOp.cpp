void CAxisInterpOp::ComputeWeights
( 
	XSI::MATH::CQuaternion& qbone2, 
	unsigned long size,			// number of triggers
	double* aweights, 
	double* atriggers, 
	double* atolerances 
)
{
	XSI::MATH::CQuaternion q2;

#ifdef _DEBUG_COMPUTEWEIGHTS
	Application app;
	wchar_t wszBuf[256]; 

	swprintf( wszBuf, L"ComputeWeights qbone2->[%f V(%f,%f,%f)]",  qbone2.GetW(), qbone2.GetX(), qbone2.GetY(), qbone2.GetZ() );
	app.LogMessage( (const wchar_t*)wszBuf ); 

	double x, y, z;
	
	qbone2.GetXYZAnglesValues(x,y,z);

	swprintf( wszBuf, L"ComputeWeights qbone2->R(%f,%f,%f)]",  r2d(x),r2d(y),r2d(z) );
	app.LogMessage( (const wchar_t*)wszBuf ); 
#endif

	// dim tsec : tsec = timer
	// fntrace "ComputeWeights("&j&") bone2 angle: " & fnstr(q2rot(qbone2))

	double sumw(0), weight(0), dot_product(0), tolerance(0);
	
	for ( unsigned long j=0,i=0; i < size*3; i=i+3,j=j+1 )
	{
		tolerance = d2r(atolerances[j]);
#ifdef _DEBUG_COMPUTEWEIGHTS
		swprintf( wszBuf, L"trigger(%d) ori: (%f,%f,%f)", j, atriggers[i], atriggers[i+1], atriggers[i+2] );
		app.LogMessage( (const wchar_t*)wszBuf ); 

		swprintf( wszBuf, L"trigger(%d) tolerance: %f", j, tolerance );
		app.LogMessage( (const wchar_t*)wszBuf ); 
#endif

		q2.SetFromXYZAnglesValues( d2r(atriggers[i]), d2r(atriggers[i+1]), d2r(atriggers[i+2]) );

		// compute dot product of quaternion
		dot_product = 
			qbone2.GetX() * q2.GetX() + 
			qbone2.GetY() * q2.GetY() + 
			qbone2.GetZ() * q2.GetZ() + 
			qbone2.GetW() * q2.GetW();
#ifdef _DEBUG_COMPUTEWEIGHTS
		swprintf( wszBuf, L"trigger(%d) dot: %f", j, dot_product );
		app.LogMessage( (const wchar_t*)wszBuf ); 
#endif

		if ( tolerance == 0 ) {
			weight = 0;
		} else {
#ifdef _DEBUG_COMPUTEWEIGHTS
//		swprintf( wszBuf, L"ComputeWeights(%d) _acos(%f) = %f", j, fabs(dot_product), _acos(fabs(dot_product)) );
//		app.LogMessage( (const wchar_t*)wszBuf ); 
		swprintf( wszBuf, L"trigger(%d) acos(%f) = %f", j, fabs(dot_product), acos(fabs(dot_product)) );
		app.LogMessage( (const wchar_t*)wszBuf ); 
#endif
			weight = 1.0 - (2.0 * acos(fabs(dot_product)) / tolerance);
#ifdef _DEBUG_COMPUTEWEIGHTS
		swprintf( wszBuf, L"trigger(%d) weight: %f", j, weight );
		app.LogMessage( (const wchar_t*)wszBuf ); 
#endif
			if ( weight < 0 ) {
				weight = 0;
			}
		}
#ifdef _DEBUG_COMPUTEWEIGHTS
		swprintf( wszBuf, L"trigger(%d) computed weight: %f", j, weight );
		app.LogMessage( (const wchar_t*)wszBuf ); 
#endif

		aweights[j] = weight;
		// fntrace "ComputeWeights("&j&") raw: " & aW(j)

		sumw=sumw+aweights[j];
	}

	// make sure sum of weights totals 1
	if ( sumw != 0 ) 
	{
		for ( unsigned long i=0; i < size; i++ )
		{
			if ( aweights[i] != 0 ) {
				aweights[i] = aweights[i] / sumw;
				//fntrace "ComputeWeights("&i&") normalized: " & aW(i)
			}  
#ifdef _DEBUG_COMPUTEWEIGHTS
			swprintf( wszBuf, L"trigger(%d) normalized = %f", i, aweights[i] );
			app.LogMessage( (const wchar_t*)wszBuf ); 
#endif
		}
	}
	//fntrace "AxisInterpOp::ComputeWeights: took " & timer-tsec & " seconds"

}