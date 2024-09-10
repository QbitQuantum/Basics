//===============================================================================================
// FUNCTION: CreateIdentityPalette
// PURPOSE:  Fills on output in pRGBIdentityOut with the identity based palette based on the RGB
//           values passed into this function. The colors given should be in order of importance, 
//           since the RGB colors at the end of the list will probably not be included in the
//           creation of the palette, since 20 static colors need to be preserved.      
//           If there is no system palette, the function fails.
// PARAMETERS:
//    pRGBEntryIn       The array of RGB values to be used to make an identity palette
//    pRGBIdentityOut   Pointer to PALETTEENTRYs. This array is filled with an 
//                      identity system palette. Number of elements must be the
//                      same as lNumRGBEntriesIn
//    lNumRGBEntriesIn  Number of elements in pRGBEntryIn
//
void CDisplaySurface::CreateIdentityPalette(const LPPALETTEENTRY pRGBEntryIn, LPPALETTEENTRY pRGBIdentityOut, int nNumEntries)
{   
   // make sure the # of RGB entries is at least as big as the size we're going to create
   RARRAYASSERT(pRGBEntryIn, nNumEntries);   
   WARRAYASSERT(pRGBIdentityOut, nNumEntries);   
  
   // get size of system palette, 256 for 8 bit display
   // if we are greater than 8 bits per pixel, we don't have a palette at all
   // m_nPaletteSize will be 0 for screen depths > 8
   ASSERT(m_nPaletteSize > 0);   // make sure we are in 8 bit display

   // get the system palette entries, since we need to make an identity palette   
   GetSystemPaletteEntries(m_hdcWin, 0, m_nPaletteSize, pRGBIdentityOut);

   // Get number of static colors and read entire system palette        
   // If the system has no static palette colors just copy everything   
   // the number of static colors in the first half (lower section) of the palette are
   // the number of static colors divided by 2, since the second half of the
   // static colors are located at the top (upper) section of the palette
   int nStaticColors = 0;
   if (GetSystemPaletteUse(m_hdcWin) == SYSPAL_NOSTATIC)
      nStaticColors = 0;
   else
      nStaticColors = max(GetDeviceCaps(m_hdcWin, NUMCOLORS) / 2, 0);
   
   // The palette goes something like this:
   //
   //   <--static colors--|------usuable colors-------|--static colors-->
   //   The static colors are usually from 0-9 and from 246-255 and the entries
   //   that we can use are in the range 10-245. So nStaticColors will usually equal 10
  
   // Set low part of static entry palette flags to zero   
   for (int i=0; i < nStaticColors; i++)      
      pRGBIdentityOut[i].peFlags = 0;

   // Now copy over the available part of the system palette
         
   // we need to find where the last usable color slot in the palette
   // is, this is usually at 256-nStaticColors-1=245 (256-10-1=245) slot, 
   // that is the palette size minus half of the static colors
   // (since half of them reside in the upper half of the palette)    
   // so nFirstUpperStaticColor = 256-10 = 246
   int nFirstUpperStaticColor = m_nPaletteSize-nStaticColors;      

   // we've dealt with the first section of the palette
   // so now we can look at the entries that we will fill up with the given
   // RGB colors (from 10-245)   

   int nColorIndex=0;         
   for (i=nStaticColors; i < nFirstUpperStaticColor && nColorIndex < nNumEntries; i++, nColorIndex++)
   {            
      BYTE nFlag = PC_NOCOLLAPSE;         
      pRGBIdentityOut[i] = pRGBEntryIn[nColorIndex];               

      // we need to look at the upper static colors (upper 10) to see if this color happens
      // to be a duplicate of one of these, if it is, we need to set this entry as PC_RESERVED 
      // so that we don't allow Windows to match the upper 10 matching color to this color later
      // if it is not a duplicate, we simply mark it as PC_NOCOLLAPSE so Windows doesn't match 
      // this color to another color in the palette      
      for (int n = nFirstUpperStaticColor; n < m_nPaletteSize; n++) 
      {
         if (pRGBIdentityOut[n].peRed   == pRGBEntryIn[nColorIndex].peRed &&
             pRGBIdentityOut[n].peGreen == pRGBEntryIn[nColorIndex].peGreen &&
             pRGBIdentityOut[n].peBlue  == pRGBEntryIn[nColorIndex].peBlue)              
         {
            nFlag = PC_RESERVED;                
            break;
         }
      }
      pRGBIdentityOut[i].peFlags = nFlag;             
   }
   
   // Finish by setting botton part of static entry's palette flags
   // Set the peFlags of the upper static colors to zero, to match it normally
   for (; i < m_nPaletteSize; i++)
      pRGBIdentityOut[i].peFlags = 0;                                   
}