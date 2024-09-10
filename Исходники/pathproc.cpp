INT32 ProcessPathDistance::GetCoordAndTangentWithCache(DocCoord* pCoord, 
													  double* pTangent, BOOL* pFound,
											          double Dist, Path* pPath, UINT32* pPressure)
{
	ERROR2IF(pCoord==NULL && pTangent==NULL,FALSE,"ProcessPathDistance::GetCoordAndTangent() - no output pointers specified!");
	ERROR2IF(pFound==NULL,FALSE,"ProcessPathDistance::GetCoordAndTangent() - pFound==NULL");
	ERROR2IF( pPath==NULL,FALSE,"ProcessPathDistance::GetCoordAndTangent() - pPath==NULL");
 
	// we wish to continue processing from the last point that we found
	INT32 PrevCoordIndex = m_LastFoundIndex;
	INT32 NumProcessed = m_LastFoundIndex;

	DesiredDist   = Dist;
	CurrentDist   = m_LastFoundDistance;
	Found         = FALSE;
	CoordAtDist   = DocCoord(0,0);
	TangentAtDist = 0;
	PressureAtDist = 0;
	m_bDrawingBrush = TRUE;
	// set up the processpath process.
	ProcessFlags PFlags;
	
	BOOL bPressure = (pPressure != NULL && pPath->HasWidth());
	// if we are already partway along the path then we need to get the
	// previous point as it is needed in NewPoint
	if (NumProcessed > 0)
	{
		DocCoord* pCoords = pPath->GetCoordArray();
		PrevCoord = pCoords[PrevCoordIndex];
		if (bPressure)
		{
			UINT32* pPressureArray = pPath->GetWidthArray();
			if (pPressureArray != NULL)
				m_PrevPressure = pPressureArray[PrevCoordIndex];
			else
			{
				ERROR3("Wheres the pressure array?");
				m_PrevPressure = (UINT32)(MAXPRESSURE / 2);
			}
		}
	}
	
	BOOL ok=ProcessPath::Init(pPath);
	//TRACEUSER( "Diccon", _T("Desired    = %f\n"), Dist);
	//TRACEUSER( "Diccon", _T("Starting   = %f\n"), CurrentDist);

	if (ok)	NumProcessed = Process(PFlags, NumProcessed);

	if (NumProcessed != -1)
	{
		if (Found==FALSE) // this can happen if we are on the first couple of points
		{
			// get last 2 points on line
			DocCoord* pPathCoords=pPath->GetCoordArray();
			ERROR2IF(pPathCoords==NULL,FALSE,"ProcessPathDistance::GetCoordAndTangent() - pPathCoords==NULL");
			INT32 NumPathCoords=pPath->GetNumCoords();
			//ERROR2IF(NumPathCoords<2,FALSE,"ProcessPathDistance::GetCoordAndTangent() - NumPathCoords < 2");
			if (NumPathCoords >= 2)
			{
				DocCoord LastCoord=pPathCoords[NumPathCoords-1];
				DocCoord PrevCoord=pPathCoords[NumPathCoords-2];

				double dx=LastCoord.x-PrevCoord.x;
				double dy=LastCoord.y-PrevCoord.y;
				double LineLength=sqrt(dx*dx+dy*dy);

				if (LineLength>0)
				{
					double FractOfLine = (DesiredDist-CurrentDist)/LineLength;
					double x = LastCoord.x+dx*FractOfLine;
					double y = LastCoord.y+dy*FractOfLine;

					CoordAtDist   = DocCoord((MILLIPOINT)x,(MILLIPOINT)y);
					TangentAtDist = atan2(dy,dx);
					Found = TRUE;
				}
				else
				{
					CoordAtDist	  =	LastCoord;
					TangentAtDist = 0;
					Found = TRUE;
				}
			}
			else //if we only have one coordinate so far
			{
				CoordAtDist=pPathCoords[0];
				TangentAtDist = 0;
				Found = TRUE;
			}
		}
		else
		{
			if (Dist<0) Found=FALSE;	// if not actually on path, flag not found on path
			
		}
		*pFound = Found;
		if (pCoord)   *pCoord   = CoordAtDist;
		if (pTangent) *pTangent = TangentAtDist;
		if (pPressure != NULL)
			*pPressure = PressureAtDist;
	}
	//m_LastFoundDistance = CurrentDist;
	//TRACEUSER( "Diccon", _T("Last Index = %d\n"), m_LastFoundIndex);
	//TRACEUSER( "Diccon", _T("Last Dist  = %f\n"), m_LastFoundDistance);

	//TRACEUSER( "Diccon", _T("FOUND      = %d\n"), Found);

	return NumProcessed;
}