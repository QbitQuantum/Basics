void CImage::Draw(const TRect& aRect) const
{
   // Draw the parent control
   //CEikBorderedControl::Draw(aRect);
   // Get the standard graphics context 
   CWindowGc& gc = SystemGc();
   // Gets the control's extent - Don't encroach on the border
   TRect rect = Rect();//Border().InnerRect(Rect());
   // set the clipping region
   gc.SetClippingRect(rect);   
   if(iMask == NULL && iBitmap != NULL && rect.Intersects(aRect)){
      gc.BitBlt(rect.iTl, iBitmap);
   } else if(iMask != NULL && iBitmap != NULL && rect.Intersects(aRect)){
      TRect pictRect(TPoint(0,0), iBitmap->SizeInPixels());
      gc.BitBltMasked(rect.iTl, iBitmap, pictRect, iMask, EFalse);
   }
}