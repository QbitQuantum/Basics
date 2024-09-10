BOOL SimpleBrowser::GetElementText(LPCTSTR elementName, LPTSTR bf, UINT bfLen)
{
	IHTMLDocument3* pDocument = GetDocument3();
	if (pDocument == NULL)
		return FALSE;
	BOOL bRet = FALSE;
	IHTMLElement* pElement = NULL;
	CComBSTR elemName = elementName;
	if (pDocument->getElementById(elemName, &pElement) == S_OK && pElement != NULL)
	{
		CComBSTR innerText;
		if (pElement->get_innerText(&innerText) == S_OK)
		{
			if (innerText.Length() > 0)
			{
				_tcsncpy(bf, innerText, bfLen);
				bf[bfLen - 1] = 0;
			}
			else
				bf[0] = 0;
			bRet = TRUE;
		}
		pElement->Release();
	}
	pDocument->Release();
	return bRet;

}