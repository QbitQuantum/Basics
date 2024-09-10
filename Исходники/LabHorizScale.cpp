void CLabHorizScale::drawScale(CDC *pDC)
{
   int tickLength;
   
   CRgn rgn;
   CRect rect = bounds();
   rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
   pDC->SelectClipRgn(&rgn);
      
   for(double x=getTickMin(); x<=maximum(); x=x+tickIncrement())
   {
      double temp = x/(majorTickFrequency()*tickIncrement());
      if(temp == ceil(temp))
         tickLength = 7;
      else
         tickLength = 3;


      pDC->MoveTo(translateCoordinate(x), rect.top);
      pDC->LineTo(translateCoordinate(x), rect.top + tickLength);

      temp = x/(tickMarkFrequency() * tickIncrement());
      if(temp == ceil(temp))
      {
         CString tickMarkStr;
         tickMarkStr.Format("%.*f", precision(), x);
         
         pDC->TextOut(translateCoordinate(x) - _parent->getCharWidth() * tickMarkStr.GetLength()/2, 
                      rect.top + 7 /* _parent->getCharHeight()*/, 
                      tickMarkStr);

      }
   }
}