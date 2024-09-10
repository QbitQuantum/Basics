/*-----------------------------------------------[ private ]-----------------*/
static BOOL paintColumn(HPS hps,WINDOWINFO *pwi,POBJECT pObj, RECTL rclCol,int iMode)
{
   POINTL ptl1,ptl2;
   RECTL rcl;
   blocktext *pT = (blocktext *)pObj;

   ptl1.x = rclCol.xLeft;
   ptl1.y = rclCol.yBottom;
   ptl2.x = rclCol.xRight;
   ptl2.y = rclCol.yTop;

   rcl = rclCol;

   if (pT->bt.lPattern == PATSYM_DEFAULT && 
       pT->bt.line.LineType == LINETYPE_INVISIBLE)
      return FALSE;

   if (iMode == MODE_PREPPRINTING)
   {
      /*
      ** During the print preparation we do not draw the column but
      ** we return true so the column painting can take this square
      ** into account.
      */
      return TRUE;
   }
   GpiSetLineType(hps,pT->bt.line.LineType);
   GpiSetPattern(hps, PATSYM_SOLID);
   GpiSetColor(hps,pT->ulColColor);

   if (pT->bt.lPattern == PATSYM_DEFAULT)
   {
      /*
      ** No filling
      */
      GpiSetColor(hps,pT->bt.line.LineColor);
      GpiMove(hps,&ptl1);
      GpiBox(hps,DRO_OUTLINE,&ptl2,0,0);
   }
   else if ( pT->bt.lPattern != PATSYM_GRADIENTFILL && 
             pT->bt.lPattern != PATSYM_FOUNTAINFILL )
   {
      /*
      ** we have a standard OS/2 patternfill.
      */
      GpiMove(hps,&ptl1);

      if (pT->bt.line.LineColor == pT->ulColColor )
      {
         GpiBox(hps,DRO_OUTLINEFILL, 
                &ptl2,0,0);
      }
      else
      {
         GpiMove(hps,&ptl1);
         /*
         ** Draw the filling part
         */
         GpiBox(hps,DRO_FILL, 
                &ptl2,0,0);
         /*
         ** Draw the outline
         */
         GpiMove(hps,&ptl1);
         GpiSetColor(hps,pT->bt.line.LineColor);

         GpiBox(hps,DRO_OUTLINE, 
                &ptl2,0,0);
      }
   }
   else if (pT->bt.lPattern == PATSYM_GRADIENTFILL || 
            pT->bt.lPattern == PATSYM_FOUNTAINFILL)
   {
      GpiBeginPath( hps, 1L);  /* define a clip path    */

      GpiMove(hps,&ptl1);
      GpiBox(hps,DRO_OUTLINE, 
             &ptl2,0,0);

      GpiEndPath(hps);
      GpiSetClipPath(hps,1L,SCP_AND);
      GpiSetPattern(hps,PATSYM_SOLID);
      if (pT->bt.lPattern == PATSYM_GRADIENTFILL)
         GradientFill(pwi,hps,&rcl,&pT->bt.gradient);
      else
         FountainFill(pwi,hps,&rcl,&pT->bt.fountain);

       GpiSetClipPath(hps, 0L, SCP_RESET);  /* clear the clip path   */


       if (pT->bt.line.LineType !=  LINETYPE_INVISIBLE)
       {
         /*
         ** Draw the outline
         */
         GpiMove(hps,&ptl1);
         GpiSetColor(hps,pT->bt.line.LineColor);
         GpiBox(hps,DRO_OUTLINE, 
                &ptl2,0,0);
      }
   }
   return TRUE;
}