/*********************************************************
*NAME:          dialogLanguagesSetText
*AUTHOR:        John Morrison
*CREATION DATE: 29/4/00
*LAST MODIFIED: 29/4/00
*PURPOSE:
*  Sets the text in the dialog box
*
*ARGUMENTS:
*  hWnd   - Handle to the window
*********************************************************/
void dialogLanguagesSetText(HWND hWnd) {
  /* Set dialog language text */
  SetDlgItemTextA(hWnd, IDOK, langGetText(STR_OK));  
  SetDlgItemTextA(hWnd, IDCANCEL, langGetText(STR_CANCEL));
  SetDlgItemTextA(hWnd, IDC_LANGNAMES, langGetText(STR_DLGLANG_NAME_CAPTION));
  SetDlgItemTextA(hWnd, IDC_LANGNAME, langGetText(STR_DLGLANG_NAME));
  SetDlgItemTextA(hWnd, IDC_AUTHORS, langGetText(STR_DLGLANG_AUTHOR_CAPTION));
  SetDlgItemTextA(hWnd, IDC_AUTHOR, langGetText(STR_DLGLANG_AUTHOR));
  SetDlgItemTextA(hWnd, IDC_NOTESS, langGetText(STR_DLGLANG_NOTES_CAPTION));
  SetDlgItemTextA(hWnd, IDC_NOTES, langGetText(STR_DLGLANG_NOTES));
  SetDlgItemTextA(hWnd, IDC_DEFAULT, langGetText(STR_DLGLANG_DEFAULTNOTE));
  SetWindowTextA(hWnd, langGetText(STR_DLGLANG_TITLE));
}