void CContainerUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("inset")) == 0 ) SetInset(CSize(_ttoi(pstrValue), _ttoi(pstrValue)));
   else if( _tcscmp(pstrName, _T("padding")) == 0 ) SetPadding(_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("width")) == 0 ) SetWidth(_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("height")) == 0 ) SetHeight(_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("scrollbar")) == 0 ) EnableScrollBar(_tcscmp(pstrValue, _T("true")) == 0);
   else CControlUI::SetAttribute(pstrName, pstrValue);
}