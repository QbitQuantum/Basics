BOOL CViewerWnd::HitTest(const OgdcPoint2D& pntHitTest, OgdcElemRegion* pElemRegion, double dTolerance)	
{
	OGDCASSERT(pElemRegion != NULL);
	OgdcRect2D rcBounds = pElemRegion->GetBounds();
	rcBounds.Inflate(dTolerance, dTolerance);
	if (rcBounds.PtInRect(pntHitTest))
	{
		OgdcInt *plPolyCounts = pElemRegion->m_polyCounts.GetData();
		OgdcPoint2D *pPoints = pElemRegion->m_points.GetData();
		OgdcInt lCount = pElemRegion->m_polyCounts.GetSize();
		if(plPolyCounts == NULL || pPoints == NULL || lCount == 0)
		{
			return FALSE;
		}
	
		OgdcDouble dInter=0;
		OgdcInt nCount=0,counter = 0;		
		OgdcPoint2D* p1 = NULL;
		OgdcPoint2D* p2 = NULL;		
		for (OgdcInt k=0; k < lCount; k++)
		{
			nCount = plPolyCounts[k];
			///////////////////////////////////////////////////
			p1 = pPoints;
			for (OgdcInt i=1;i <= nCount; i++) 
			{
				p2 = pPoints+(i%nCount);
				if (OGDCIS0(pntHitTest.y - OGDCMIN(p1->y,p2->y)))
				{
					if (OGDCIS0(p1->y - p2->y))
					{
						if (( (pntHitTest.x < OGDCMAX(p1->x,p2->x) ) || OGDCEQUAL(pntHitTest.x,OGDCMAX(p1->x,p2->x))) 
							&& ( (pntHitTest.x > OGDCMIN(p1->x,p2->x) ) || OGDCEQUAL(pntHitTest.x,OGDCMIN(p1->x,p2->x))))
						{
							return TRUE;
						}
					}
					else
					{
						if ((pntHitTest == (*p1)) || (pntHitTest == (*p2)))
						{
							return TRUE;
						}
					}
				}			
				else if (pntHitTest.y > OGDCMIN(p1->y,p2->y)) 
				{
					//if (pntHitTest.y <= OGDCMAX(p1->y,p2->y)) 
					if ( (pntHitTest.y < OGDCMAX(p1->y,p2->y)) || OGDCEQUAL(pntHitTest.y , OGDCMAX(p1->y,p2->y))  )
					{        
						//if (pntHitTest.x <= OGDCMAX(p1->x,p2->x)) 
						if (  (pntHitTest.x < OGDCMAX(p1->x,p2->x)) || OGDCEQUAL(pntHitTest.x , OGDCMAX(p1->x,p2->x)) ) 
						{
							if (!OGDCIS0(p1->y - p2->y))
							{
								if (OGDCIS0(p1->x - p2->x))
								{
									if (OGDCIS0(pntHitTest.x - p1->x))
									{
										return TRUE;
									}
									counter++;
								}
								else
								{
									dInter = (pntHitTest.y-p1->y)*(p2->x-p1->x)/(p2->y-p1->y)+(p1->x-pntHitTest.x);
									dInter /= fabs((p2->x-p1->x));
									if (fabs(dInter) < 1.0e-8)
									{
										return TRUE;
									}
									if (dInter >  EP)
									{
										counter++;
									}
								}
							}
						}      
					}    
				}				
				p1 = p2;  
			}  
			///////////////////////////////////////////////////
			pPoints += nCount;
		}
		if (counter % 2 == 0)
		{
			return FALSE;  
		}
		return TRUE;
	}
	return FALSE;
}