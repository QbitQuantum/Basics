/////////////////////////////////////////////////////////////////////////////
//	OnEditVerifyFloatCell
//		This is a handy utility to keep user entry in floating point number cells valid as they type.
//    The caller should determine that the cell is for percent entry, and if so
//    can pass verification of the input key to this function.
//	Params:
//		col, row	- location of the edit cell
//		edit		-	pointer to the edit control
//		vcKey		- virtual key code of the pressed key
//	Return:
//		TRUE - to accept pressed key
//		FALSE - to do not accept the key
int CDDBaseGrid::OnEditVerifyFloatCell(int col, long row,CWnd *edit,UINT *vcKey)
{
   // Cursor movement keys are okay
   // But these symbols don't work ... ?
   //if (*vcKey == VK_BACK || *vcKey == VK_LEFT || *vcKey == VK_RIGHT || *vcKey == VK_DELETE)
   //   return TRUE;
   if (*vcKey == VK_BACK || *vcKey == 0x7F /*Delete*/)
      return TRUE;

   // Current selection will be replaced, so chars in there don't matter, remove them from
   // consideration during validation tests.
   CString curTxt;
   CEdit *cedit = (CEdit*)edit;
   edit->GetWindowText(curTxt);
   int startIndx = -1, endIndx = -1;
   cedit->GetSel(startIndx, endIndx);
   if (startIndx > -1 && endIndx > startIndx)
      curTxt.Delete(startIndx, endIndx - startIndx);

   int curMinusIndx = curTxt.Find("-");

   // Alpha chars '.' and '-' accepted, but only one per customer
   if (*vcKey == '.' || *vcKey == '-')
   {
      // Possibly okay, make sure no duplicate of percent or decimal pt.

      int curDecimalIndx = curTxt.Find(".");

      // Can only have one of these
      if (*vcKey == '-' && curMinusIndx > -1)
      {
         MessageBeep((UINT)-1);
         return FALSE;
      }
      if (*vcKey == '.' && curDecimalIndx > -1)
      {
         MessageBeep((UINT)-1);
         return FALSE;
      }

      // Can't put decimal before minus
      if (*vcKey == '.' && curMinusIndx > -1 && startIndx <= curMinusIndx)
      {
         MessageBeep((UINT)-1);
         return FALSE;
      }

      // Minus can only go at beginning
      if (*vcKey == '-' && startIndx != 0)
      {
         MessageBeep((UINT)-1);
         return FALSE;
      }

      // Okay, we'll accept the char
      return TRUE;
   }

   // We're accepting digits, but not in front of minus sign
   if (isdigit(*vcKey))
   {
      // Can't put digits in front of minus
      if (curMinusIndx > -1 && startIndx <= curMinusIndx)
      {
         MessageBeep((UINT)-1);
         return FALSE;
      }

      // Okay
      return TRUE;
   }

   // All else
   MessageBeep((UINT)-1);
   return FALSE;
}