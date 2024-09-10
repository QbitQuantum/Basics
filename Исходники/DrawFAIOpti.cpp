void MapWindow::DrawFAIOptimizer(LKSurface& Surface, const RECT& rc, const POINT &Orig_Aircraft)
{

  LKColor whitecolor = RGB_WHITE;
  LKColor origcolor = Surface.SetTextColor(whitecolor);
  LKPen oldpen = Surface.SelectObject(hpStartFinishThick);
  LKBrush oldbrush = Surface.SelectObject(LKBrush_Hollow);


/********************************************************************/
  unsigned int ui;
  double lat1 = 0;
  double lon1 = 0;
  double lat2 = 0;
  double lon2 = 0;
  BOOL bFlat = false;
  BOOL bFAI = false;
  double fDist, fAngle;
  LockTaskData(); // protect from external task changes
    bFAI =  CContestMgr::Instance().FAI();
    CContestMgr::CResult result = CContestMgr::Instance().Result( CContestMgr::TYPE_FAI_TRIANGLE, true);
    const CPointGPSArray &points = result.PointArray();
    unsigned int iSize = points.size();
    CContestMgr::TType sType = result.Type();

    double lat_CP = CContestMgr::Instance().GetClosingPoint().Latitude();
    double lon_CP = CContestMgr::Instance().GetClosingPoint().Longitude();
    double fFAIDistance = result.Distance();
  UnlockTaskData(); // protect from external task changes
  if((sType ==  CContestMgr::TYPE_FAI_TRIANGLE) && iSize>0)
  {
    LKASSERT(iSize<100);
    for(ui=0; ui< iSize-1; ui++)
    {
      LockTaskData(); // protect from external task changes
      lat1 = points[ui].Latitude();
      lon1 = points[ui].Longitude();
      lat2 = points[ui+1].Latitude();
      lon2 = points[ui+1].Longitude();
      UnlockTaskData();

      DistanceBearing(lat1, lon1, lat2, lon2, &fDist, &fAngle);

      #if BUGSTOP
      LKASSERT(fFAIDistance!=0);
      #endif
      if (fFAIDistance==0) fFAIDistance=0.1;

      if(((fDist > FAI_MIN_DISTANCE_THRESHOLD) && (ui < 3) && !bFlat && (fDist/ fFAIDistance  > 0.05)) )
  	  {
  		LKColor rgbCol = RGB_BLUE;
  		switch(ui)
  		{
  		  case 0: rgbCol = RGB_YELLOW; break;
  		  case 1: rgbCol = RGB_CYAN  ; break;
  		  case 2: rgbCol = RGB_GREEN ; break;
  		  default:
  		  break;
  		}
  		RenderFAISector ( Surface, rc, lat1, lon1, lat2, lon2, 1, rgbCol );
  		RenderFAISector ( Surface, rc, lat1, lon1, lat2, lon2, 0, rgbCol );
  	  }
      if (fFAIDistance > 0)  /* check if triangle is too flat for second sector */
        if(fDist/ fFAIDistance  > 0.45)
    	  bFlat = true;
    }
/*********************************************************/


    if(ISPARAGLIDER && bFAI)
    {
      LKPen hpSectorPen(PEN_SOLID, IBLSCALE(2),  FAI_SECTOR_COLOR );
      LKPen hOldPen = Surface.SelectObject(hpSectorPen);
      POINT Pt1;
      MapWindow::LatLon2Screen(lon_CP, lat_CP,  Pt1);
      FindLatitudeLongitude(lat1, lon1, 0 , fFAIDistance* 0.20, &lat2, &lon2); /* 1000m destination circle */
      int iRadius = (int)((lat2-lat1)*zoom.DrawScale());
      Surface.Circle(Pt1.x, Pt1.y, iRadius  , rc, true ,  false);
      FindLatitudeLongitude(lat1, lon1, 0 , 500, &lat2, &lon2); /* 1000m destination circle */
      iRadius = (int)((lat2-lat1)*zoom.DrawScale());
      Surface.Circle(Pt1.x, Pt1.y, iRadius  , rc, true ,  false);
      Surface.SelectObject (hOldPen);
    }

/*********************************************************/

  }



    
/********************************************************************/
    // restore original color
    Surface.SetTextColor(origcolor);
    Surface.SelectObject(oldpen);
    Surface.SelectObject(oldbrush);

}