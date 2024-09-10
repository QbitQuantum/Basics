nsresult Conv_FE_06_WithReverse(const nsString& aSrc, nsString& aDst)
{
  PRUnichar *aSrcUnichars = (PRUnichar *)aSrc.get();
  PRBool foundArabic = PR_FALSE;
  PRUint32 i, endArabic, beginArabic, size;
  beginArabic = 0;
  size = aSrc.Length();
  aDst.Truncate();
  for (endArabic=0;endArabic<size;endArabic++) {
    if (aSrcUnichars[endArabic] == 0x0000) 
      break; // no need to convert char after the NULL

    while( (IS_FE_CHAR(aSrcUnichars[endArabic]))||
           (IS_ARABIC_CHAR(aSrcUnichars[endArabic]))||
           (IS_ARABIC_DIGIT(aSrcUnichars[endArabic]))||
           (aSrcUnichars[endArabic]==0x0020)) 
    {
      if(! foundArabic ) {
        beginArabic=endArabic;
        foundArabic= PR_TRUE;
      }
      endArabic++;
    }
    if(foundArabic) {
      endArabic--;
      for (i=endArabic; i>=beginArabic; i--) {
        if(IS_FE_CHAR(aSrcUnichars[i])) {
          //ahmed for the bug of lamalf
          aDst += PresentationToOriginal(aSrcUnichars[i], 0);
          if (PresentationToOriginal(aSrcUnichars[i], 1)) {
            // Two characters, we have to resize the buffer :(
             aDst += PresentationToOriginal(aSrcUnichars[i], 1);
          } // if expands to 2 char
        } else {
          // do we need to check the following if ?
          if((IS_ARABIC_CHAR(aSrcUnichars[i]))||
             (IS_ARABIC_DIGIT(aSrcUnichars[i]))||
             (aSrcUnichars[i]==0x0020))
            aDst += aSrcUnichars[i];
        }     
      }
    } else {
      aDst += aSrcUnichars[endArabic]; 
    }
    foundArabic=PR_FALSE;
  }// for : loop the buffer
  return NS_OK;
}