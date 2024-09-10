void FunctionMenu (CEdit & editctrl, const bool bLua, set<string> * extraItems, const bool bFunctions)
  {

  int nStartChar,
      nEndChar;
  CString strWindowContents;

  // find the selection range
  editctrl.GetSel(nStartChar, nEndChar);

  if (nEndChar < 0)
    nEndChar = nStartChar;

  // get window text
  editctrl.GetWindowText (strWindowContents);

  CString strWord = GetSelectedFunction (strWindowContents, nStartChar, nEndChar);

  if (strWord.IsEmpty ())
    return;

  CCompleteWordDlg dlg;

  dlg.m_bLua = bLua;
  dlg.m_extraItems = extraItems;
  dlg.m_bFunctions = bFunctions;
  dlg.m_pt = editctrl.PosFromChar (nEndChar - 1);  // strangely doesn't work at end of line

  dlg.m_pt.x += 10;  // small gap
  dlg.m_pt.y += 10;  // small adjustment lalala

  editctrl.ClientToScreen(&dlg.m_pt);

  dlg.m_strFilter = strWord;     // selected word from dialog/text window

  if (dlg.DoModal () == IDCANCEL || dlg.m_strResult.IsEmpty ())
    return;

  // adjust selection in case we wandered around catching characters around the cursor

  editctrl.SetSel (nStartChar, nEndChar);

  // replace selection with the word they chose
  editctrl.ReplaceSel (dlg.m_strResult, TRUE);
              
  // New in version 4.57 - add the argument list after the function name

  // find the new selection range (ie. where the cursor is after the function name)
  editctrl.GetSel(nStartChar, nEndChar);
  if (nEndChar < 0)
    nEndChar = nStartChar;

  // get window text with function name in it
  editctrl.GetWindowText (strWindowContents);

  nStartChar = nEndChar;
  bool bFoundBracket = false;

  // scan forwards from cursor, looking for bracket (which would have function args in it)
  while (nEndChar < strWindowContents.GetLength () && 
         nEndChar < nStartChar + 30)
    {
    if (strWindowContents [nEndChar] == '(')
      {
      bFoundBracket = true;
      break;
      }
    // non-space means we have skipped the spaces basically, without finding a bracket
    else if (!isspace (strWindowContents [nEndChar]))
      break;
    else
      nEndChar++;
    }

  // if not found, assume a function call at least needs brackets
  // (first check if it *is* a function call and not something like sendto.script)
  if (dlg.m_strArgs.IsEmpty ())
    {
    // see if Lua function
    if (LuaFunctionsSet.find ((LPCTSTR) dlg.m_strResult) != LuaFunctionsSet.end ())
      dlg.m_strArgs = "( )";
    }   // end of no brackets

  // add in arguments if found and no arguments already
  if (!bFoundBracket && !dlg.m_strArgs.IsEmpty ())
    {
    dlg.m_strArgs = " " + dlg.m_strArgs;
    editctrl.ReplaceSel (dlg.m_strArgs, TRUE);
    // put cursor to right of LH bracket (add 2 to skip the space and the bracket)
    editctrl.SetSel (nStartChar + 2, nStartChar + 2);
    }

  // ensure text box has the focus if you click on the 'Complete' button in a dialog box
  // (otherwise the Complete button still has it)

  editctrl.SetFocus ();

  }