// **************************************************************************
// GetValue ()
//
// Description:
//	Return a string representing the value of a variant.
//
// Parameters:
//  VARIANT		&vtVal		Input variant.
//	TCHAR		*pBuffer	Pointer to buffer for output string.
//	int			nBufLen		Size of output buffer.
//
// Returns:
//  void
// **************************************************************************
void CKItemPropertiesDlg::GetValue (VARIANT &vtVal,	// [in]	
									TCHAR *pBuffer, // [out]
									int nBufLen)	// [in]
	{
	ASSERT (pBuffer != NULL);
	ASSERT (nBufLen > 0);

	// Declare a CString to help construct result string:
	CString strVal;

	// Format string according to data type:
	switch (vtVal.vt)
		{
		case VT_BOOL:
			strVal.Format (_T("%d"), vtVal.boolVal);
			break;

		case VT_UI1:
			strVal.Format (_T("%u"), vtVal.bVal);
			break;

		case VT_I1:
			strVal.Format (_T("%d"), vtVal.cVal);
			break;

		case VT_UI2:
			strVal.Format (_T("%u"), vtVal.uiVal);
			break;

		case VT_I2:
			strVal.Format (_T("%d"), vtVal.iVal);
			break;

		case VT_UI4:
			strVal.Format (_T("%u"), vtVal.ulVal);
			break;

		case VT_I4:
			strVal.Format (_T("%d"), vtVal.lVal);
			break;

		case VT_R4:
			strVal.Format (_T("%G"), vtVal.fltVal);
			break;

		case VT_R8:
			strVal.Format (_T("%G"), vtVal.dblVal);
			break;

		case VT_BSTR:
			strVal = vtVal.bstrVal;
			break;

		case VT_DATE:
			{
			bool bSuccess = false;

			// Cariant time to system time (UTC):
			SYSTEMTIME systime;
			if (VariantTimeToSystemTime (vtVal.dblVal, &systime))
				{
				// Get time zone information:
				TIME_ZONE_INFORMATION tTZI;
				if (GetTimeZoneInformation (&tTZI) != TIME_ZONE_ID_INVALID)
					{
					// Localize system time:
					SYSTEMTIME systimelocal;
					if (SystemTimeToTzSpecificLocalTime (&tTZI, &systime, &systimelocal))
						{
						strVal.Format (_T("%02d:%02d:%02d"), 
							systimelocal.wHour, systimelocal.wMinute, systimelocal.wSecond);			

						bSuccess = true;
						}
					}
				}
			
			if (!bSuccess)
				strVal = _T("???");
			}
			break;

		case VT_UI1	| VT_ARRAY:
		case VT_I1	| VT_ARRAY:
		case VT_UI2	| VT_ARRAY:
		case VT_I2	| VT_ARRAY:
		case VT_UI4	| VT_ARRAY:
		case VT_I4	| VT_ARRAY:
		case VT_R4	| VT_ARRAY:
		case VT_R8	| VT_ARRAY:
			{
			CSafeArray *pSafeArr = (CSafeArray *) vtVal.parray;
			DWORD dwCols = pSafeArr->GetNumCols ();
			DWORD dwSize = pSafeArr->GetByteLength ();
			ULONG cbElements = pSafeArr->cbElements;
			LPBYTE lpByte = (LPBYTE)pSafeArr->pvData;
			DWORD dwCol = 0;

			// Start row delimiter:
			strVal = _T("[ ");

			// Cycle through the elements:
			for (DWORD i = 0; i < dwSize; i += cbElements, lpByte += cbElements)
				{
				TCHAR szNum[32];

				// Format element according to data size:
				if (cbElements == 1)
					{
					if (vtVal.vt ==	(VT_UI1 | VT_ARRAY))
						_stprintf (szNum, _T("%u"), *lpByte);
					else
						_stprintf (szNum, _T("%d"), *(char *)lpByte);
					}
				
				else if (cbElements == 2)
					{
					if (vtVal.vt ==	(VT_UI2 | VT_ARRAY))
						_stprintf (szNum, _T("%u"), *(WORD *)lpByte);
					else 
						_stprintf (szNum, _T("%d"), *(short *)lpByte);
					}
				
				else if (cbElements == 4)
					{
					if (vtVal.vt ==	(VT_R4	| VT_ARRAY))
						_stprintf (szNum, _T("%G"), *(float *)lpByte);
					else if (vtVal.vt ==	(VT_UI4	| VT_ARRAY))
						_stprintf (szNum, _T("%u"), *(DWORD *)lpByte);
					else if (vtVal.vt ==	(VT_I4	| VT_ARRAY))
						_stprintf (szNum, _T("%d"), *(DWORD *)lpByte);
					}

				else if (cbElements == 8)
					_stprintf (szNum, _T("%G"), *(double *)lpByte);

				else
					{
					ASSERT (FALSE);
					}

				// Delimit each element within the row with a comma:
				if (dwCol != 0)
					strVal += _T(", ");

				// Append the formatted element data:
				strVal += szNum;

				// Terminate each row (except the last):
				if (++dwCol == dwCols)
					{
					if (i < dwSize - cbElements) 
						strVal += _T(" ] [ ");

					dwCol = 0;
					}
				}

			// End delimiter:
			strVal += _T(" ]");
			}
			break;

		default:
			// Unsupported datatype:
			strVal = _T ("<Bad VARTYPE>");
			break;
		}

	// Copy value to output buffer:
	lstrcpyn (pBuffer, strVal, nBufLen);
	}