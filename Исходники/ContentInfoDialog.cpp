//////////////////////////////////////////////////////////////////////////
//From CControl
//////////////////////////////////////////////////////////////////////////
void CContentInfoDialog::Draw(CGraphic& gc)const
{
	gc.SetPenColor(TRgb(255,255,255));
	gc.SetBrushColor(TRgb(64,61,90));
	gc.SetPenStyle(CBitmapContext::ESolidPen);
	gc.SetBrushStyle(CBitmapContext::ESolidBrush);

	gc.DrawRoundRect(iBackRect);

	TPoint point=iStartPoint;

	if(iBool&&iShowBmp==NULL)
	{
		gc.DrawRoundRect(TRect(iStartPoint-TPoint(2,2),TSize(iIconSize.iWidth+4,iIconSize.iHeight+4)));
		gc.DrawText(iMainEngine.GetDesById(ECoCoTextRes_GetImage),TRect(point,iIconSize),CGraphicsContext::ELeft);
		point.iY=point.iY+iIconSize.iHeight;
	}

	if(iShowBmp)
	{
		/*TPoint iconPoint(0,0);
		TSize iconSize=iIconSize;

		if(iSelectIndex<iAllLine)
		{
			iconPoint.iY=iconPoint.iY+iTextSize.iHeight*iSelectIndex;
			
			iconSize.iHeight=iIconSize.iHeight-iTextSize.iHeight*iSelectIndex;

			if(iconPoint.iY>=0&&iconSize.iHeight>0)
				gc.BitBlt(point,iShowBmp,TRect(iconPoint,iconSize));
		}*/
		gc.BitBlt(point,iShowBmp);
		point.iY=point.iY+iIconSize.iHeight;
	}

	TInt index=0;
	for(TInt i=0;i<iMaxLine;i++)
	{
		index=i+iFirstIndex;

		if(index>=iDesArray->Count())
			break;

		gc.DrawText((*iDesArray)[index],TRect(point+TPoint(0,i*iTextSize.iHeight),iTextSize),CGraphicsContext::ELeft);
	}	
	gc.SetBrushStyle(CGraphicsContext::ENullBrush);		
	
	if(iScrollbar)
		iScrollbar->Draw(gc);
}