//Background drawing function
void CTestRectGc::Draw(CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect) const
	{		
		if (iBmpBackground) 
		{
						
			TPoint a = PositionRelativeToScreen();
			TPoint b = aControl.PositionRelativeToScreen();

			//The source rect of the background is the relationship between this control and the control being drawn (child)
			//plus the subrect (aRect) to be drawn.
			TRect SourceRect(b-a+aRect.iTl, aRect.Size());

			aGc.SetDrawMode(CGraphicsContext::EDrawModePEN);
			aGc.BitBlt(aRect.iTl, iBmpBackground, SourceRect);			
			aGc.SetDrawMode(CGraphicsContext::EDrawModePEN);
		}
		else
		{
			TRect rc;
			aGc.SetClippingRect(aRect);
			aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    		aGc.SetBrushColor(iBrushColor);
    		aGc.SetBrushStyle(iBrushStyle);
			aGc.DrawRect(rc);
			aGc.CancelClippingRect();

		}		
	}