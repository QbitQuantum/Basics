void DrawColorCol (PLEGEND pLegend,
                   PLINE pLine,
                   int iCol,
                   HDC hDC,
                   int yPos)
/*
   Effect:        Draw the "color" column of a legend entry. The color 
                  column displays a small sample of the line drawing.

                  For charts, the sample is a line of the correct style,
                  color, and width.  Since we are using wide lines, 
                  the round endcaps of the lines will breach the column.
                  Therefore we need to set the clip region. We could
                  remove this clipping if we find a way to change the
                  end cap design.  

                  For alerts, the sample is a small circle which echos
                  the design in the alert log itself.
*/      
   {  // DrawColorCol
   HBRUSH         hBrush, hBrushPrevious ;
   RECT           rect ;
   int            yMiddle ;
   int            iCircle ;



   rect.left = pLegend->aCols[iCol].xPos - LegendLeftMargin () + 2 ;
   rect.top = yPos + 1 ;
   rect.right = rect.left + pLegend->aCols[iCol].xWidth - LegendHorzMargin () ;
   rect.bottom = yPos + pLegend->yItemHeight - 1 ;

   yMiddle = rect.top + (rect.bottom - rect.top) / 2 ;
   iCircle = rect.bottom - rect.top - 2 ;
 
  switch (pLegend->iLineType)
      {  // switch
      case LineTypeChart:
   
         if (pLine->Visual.iWidth == 1)
            {
            // simple case with thin pen
//            hBrush = SelectBrush (hDC, hbLightGray) ;
            hBrush = SelectBrush (hDC, hBrushFace) ;
            Rectangle (hDC, rect.left, rect.top, rect.right, rect.bottom) ;
   
            HLine (hDC, pLine->hPen, 
                   rect.left + 1, rect.right - 1, yMiddle) ;
            SelectBrush (hDC, hBrush) ;
            }
         else
            {
            // thicker pen width, have to set ClipRect so
            // it will not draw otherside the rect.
            SaveDC (hDC) ;
//            hBrush = SelectBrush (hDC, hbLightGray) ;
            hBrush = SelectBrush (hDC, hBrushFace) ;
            Rectangle (hDC, rect.left, rect.top, rect.right, rect.bottom) ;
   
            IntersectClipRect (hDC, 
                               rect.left + 1,
                               rect.top + 1,
                               rect.right - 1,
                               rect.bottom - 1) ;
            HLine (hDC, pLine->hPen, 
                   rect.left + 1, rect.right - 1, yMiddle) ;
            SelectBrush (hDC, hBrush) ;
            RestoreDC (hDC, -1) ;
            }
         break ;


      case LineTypeAlert:
         hBrushPrevious = SelectBrush (hDC, pLine->hBrush) ;

         Ellipse (hDC,
                  rect.left + 2,
                  rect.top + 2,
                  rect.left + 2 + iCircle,
                  rect.top + 2 + iCircle) ;

         SelectBrush (hDC, hBrushPrevious) ;
         break ;
      }  // switch

   }  // DrawColorCol