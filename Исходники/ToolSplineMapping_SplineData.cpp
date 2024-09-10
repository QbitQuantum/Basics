BOOL SplineData::HitTestSpline(GraphicsWindow *gw,HitRegion *hr, int &hitSplineIndex, float &u)
{
	DWORD limit = gw->getRndLimits();
	gw->setRndLimits(( limit | GW_PICK) & ~GW_ILLUM);
	//loop through splines
	gw->setTransform(Matrix3(1));
	int numLines = mShapeCache.numLines;
	gw->setHitRegion(hr);
	gw->clearHitCode();
	
	for (int splineIndex = 0; splineIndex < numLines;splineIndex++)
	{
		if (mSplineElementData[splineIndex]->IsSelected())
		{		
			PolyLine *line = &mShapeCache.lines[splineIndex];
			Point3 plist[2];
			
			u = 0.0f;		
			for (int i = 0; i < 100; i++)
			{
				plist[0] = line->InterpCurve3D(u,POLYSHP_INTERP_NORMALIZED);
				plist[1] = line->InterpCurve3D(u+0.01f,POLYSHP_INTERP_NORMALIZED);
				u += 0.01f;
				gw->polyline(2, plist, NULL, NULL, 0);
				if (gw->checkHitCode()) 
				{
					hitSplineIndex = splineIndex;
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}