void CWordTest::DrawBackground(const TParam& aParam,const TRgb& aBackground,TRect& aDrawn) const
{
    if (iBackgroundBitmap)
    {
        aParam.iGc.SetClippingRect(aParam.iDrawRect);
        aDrawn.SetRect(aParam.iTextLayoutTopLeft,iBackgroundBitmap->SizeInPixels());
        aParam.iGc.DrawBitmap(aDrawn,iBackgroundBitmap);
    }
    else
        MFormCustomDraw::DrawBackground(aParam,aBackground,aDrawn);
}