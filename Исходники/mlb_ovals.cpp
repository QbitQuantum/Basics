bool ASSISTANT::Oval::ContainsPoint(Gdiplus::PointF &ptMouse)
{
   if (!visible)
      return false; 

   CRect rcObject;
   GetBoundingBox(rcObject);

   CRgn rgnElliptic;

   double dMaxDistance = (double)lineWidth / 2 + 0.5;
   BOOL bRet = TRUE;
   if (IsFilled())
   {
      CRgn rgnElliptic;
      bRet = rgnElliptic.CreateEllipticRgnIndirect(rcObject);
      
      if (!bRet)
         return false;
      if (rgnElliptic.PtInRegion((int)ptMouse.X, (int)ptMouse.Y))
         return true;
      
   }
   else
   {
      CRect rcOutside = rcObject;
      rcOutside.InflateRect(dMaxDistance, dMaxDistance, dMaxDistance, dMaxDistance);
      bRet = rgnElliptic.CreateEllipticRgnIndirect(rcOutside);
      if (!bRet)
         return false;

      CRgn rgnElliptic2;
      CRect rcInside = rcObject;
      rcInside.DeflateRect(dMaxDistance, dMaxDistance, dMaxDistance, dMaxDistance);
      bRet = rgnElliptic2.CreateEllipticRgnIndirect(rcInside);
      if (!bRet)
         return false;

      rgnElliptic.CombineRgn(&rgnElliptic, &rgnElliptic2, RGN_DIFF);
      if (rgnElliptic.PtInRegion((int)ptMouse.X, (int)ptMouse.Y))
         return true;

   }

   return false;
}