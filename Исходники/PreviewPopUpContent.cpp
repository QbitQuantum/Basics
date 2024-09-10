void CPreviewPopUpContent::SetTextL(const TDesC& aFirstText, 
                                    const TDesC& aSecondText, 
                                    const TDesC& aThirdText)
{
   TBuf<256> wrappedText;
   AknTextUtils::WrapToStringL(aSecondText, *iStringLengths, 
                               *iLabelContainer[1].iLabel->Font(), 
                               wrappedText);
   
   iLabelContainer[0].iLabel->SetTextL(aFirstText);
   iLabelContainer[0].iLabel->CropText();

   _LIT(KNewLine, "\n");
   TInt pos = wrappedText.Find(KNewLine);
   if (pos != KErrNotFound) {
      TPtrC leftText = wrappedText.Left(pos);
      iLabelContainer[1].iLabel->SetTextL(leftText);
      TPtrC rightText = wrappedText.Mid(pos + 1);
      if (rightText.Length() < 1) {
         // WrapToStringL always seems to add a newline so we need to 
         // check for length as well.
         iLabelContainer[2].iLabel->SetTextL(aThirdText);
         iLabelContainer[2].iLabel->CropText();
         iLabelContainer[3].iLabel->SetTextL(KDefaultText);
      } else {
         iLabelContainer[2].iLabel->SetTextL(rightText);
         iLabelContainer[2].iLabel->CropText();
         iLabelContainer[3].iLabel->SetTextL(aThirdText);
         iLabelContainer[3].iLabel->CropText();
      }
   } else {
      // WrapToStringL didnt add a newline (we dont need to wrap) but it
      // seems WrapToStringL always adds newline (see above comment).
      iLabelContainer[1].iLabel->SetTextL(aSecondText);
      iLabelContainer[2].iLabel->SetTextL(aThirdText);
      iLabelContainer[2].iLabel->CropText();
      iLabelContainer[3].iLabel->SetTextL(KDefaultText);      
   }
   //iLabel->SetRect(iLabelRect);
   //iLabel->DrawDeferred();
}