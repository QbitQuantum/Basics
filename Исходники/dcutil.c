COLORREF FASTCALL
IntSetDCBrushColor(HDC hdc, COLORREF crColor)
{
   COLORREF OldColor = CLR_INVALID;
   PDC dc;
   if (!(dc = DC_LockDc(hdc)))
   {
      EngSetLastError(ERROR_INVALID_HANDLE);
      return CLR_INVALID;
   }
   else
   {
      OldColor = (COLORREF) dc->pdcattr->ulBrushClr;
      dc->pdcattr->ulBrushClr = (ULONG) crColor;

      if ( dc->pdcattr->crBrushClr != crColor )
      {
         dc->pdcattr->ulDirty_ |= DIRTY_FILL;
         dc->pdcattr->crBrushClr = crColor;
      }
   }
   DC_UnlockDc(dc);
   return OldColor;
}