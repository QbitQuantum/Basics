//////////////////////////////////////////////////////////////////////////
//From CControl
//////////////////////////////////////////////////////////////////////////
void CGradeDialog::Draw(CGraphic& gc)const
{
	gc.SetPenColor(TRgb(0,0,0));
	gc.SetPenStyle(CBitmapContext::ESolidPen);
	gc.SetBrushStyle(CBitmapContext::ENullBrush);

	gc.BitBlt(iStartPoint,iDialogBmp);

	gc.DrawText(iStartPoint+TPoint(iIconPoint.iX,iScreenLayout.FontHeight()/3),iTitle);

	for(TInt i=0;i<5;i++)
	{
		if(i<iGradeNum/2)
		{
			iBitmapFactory.DrawGradeBmpByID(gc,iStartPoint+iIconPoint+TPoint((iIconSize.iWidth+iIconPoint.iX)*i,0),0);	
		}
		else
		{
			if((iGradeNum-i*2)==1)
			{
				iBitmapFactory.DrawGradeBmpByID(gc,iStartPoint+iIconPoint+TPoint((iIconSize.iWidth+iIconPoint.iX)*i,0),1);	
			}
			else
			{
				iBitmapFactory.DrawGradeBmpByID(gc,iStartPoint+iIconPoint+TPoint((iIconSize.iWidth+iIconPoint.iX)*i,0),2);	
			}
		}
	}

}