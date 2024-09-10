void CFpsView::Draw(CBitmapContext& aGc, const TRect& aTargetRect, const TSize& aSize)
    {
    ++iFps; 
    int nro = iFpsCount;
    const TSize sz = iNumbers->SizeInPixels();
    TPoint pos(iPos.iX + sz.iWidth * iDigits, iPos.iY);
    const TInt height = (sz.iHeight / 10);
    do  
        {
        const int digit = nro % 10;
        nro /= 10;
        TRect rect(0, digit * height, sz.iWidth, digit * height + height);
        aGc.BitBlt(pos, iNumbers, rect);
        pos.iX -= sz.iWidth;
        }while(nro > 0);
    }