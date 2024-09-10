/**
Completes a pass of this render stage.
*/
void CTestRenderStage::End()
	{
	CFbsBitGc* gc =  iBackBuffer->GetBitGcCurrent();
	gc->SetPenSize(TSize(2,2));
	gc->SetPenColor(KRgbRed);
	gc->DrawLine(TPoint(50,0),TPoint(0,50));
	gc->SetPenColor(KRgbGreen);
	gc->DrawLine(TPoint(60,0),TPoint(0,60));
	
	if (Next())
		{
		gc = Next()->Begin();
		const TRegion* region = iScreenRedraw->AnimationRegion();
		if(region && !region->IsEmpty() && !region->CheckError())
			{
			if (iBackBuffer->Observer())
				iBackBuffer->Observer()->BeforeUpdate(*iBackBuffer,*region);
			
			gc->SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha);
			gc->SetClippingRegion(region);
			gc->BitBlt(-iScreenConfig->ScaledOrigin(),iBackBuffer->GetBitmap());
			gc->SetDrawMode(CGraphicsContext::EDrawModePEN);
			gc->CancelClipping();
			
			if (iBackBuffer->Observer())
				iBackBuffer->Observer()->AfterUpdate(*iBackBuffer,*region);
			}
		Next()->End();
		}
	}