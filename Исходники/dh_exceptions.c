/* **************************************************************************
 * dhExitEx:
 *   This function is called when exiting a DispHelper function.
 *
 * Parameter Info:
 *   bDispatchError   - TRUE if the error was returned from the IDispatch interface.  
 *   szMember         - The member name that caused the error. eg. "TypeText"
 *   szCompleteMember - The complete member. eg. "Selection.TypeText(%S)"
 *   pExcepInfo       - A pointer to the EXCEPINFO structure returned by IDispatch::Invoke.
 *   iArgError        - The index of the argument that caused the error as returned by Invoke.
 *   szFunctionName   - The function which is exiting(string must have global life time).
 * 
 * Notes:
 *   szMember, szCompleteMember, pExcepInfo and iArgError are NULL or 0 if not available.
 *
 ============================================================================ */
HRESULT dhExitEx(HRESULT hr, BOOL bDispatchError, LPCWSTR szMember, LPCWSTR szCompleteMember,
                 EXCEPINFO * pExcepInfo, UINT iArgError, LPCWSTR szFunctionName)
{
	UINT nStackCount = GetStackCount();

	SetStackCount(nStackCount - 1);

	if (FAILED(hr) && !g_ExceptionOptions.bDisableRecordExceptions)
	{
		PDH_EXCEPTION pException = GetExceptionPtr();

		if (!pException) /* No exception allocated for this thread yet */
		{ 
			pException = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(DH_EXCEPTION));
			if (!pException) return hr;
			SetExceptionPtr(pException);
		}
		else if (pException->bOld) /* Exception is from a former call */
		{
			SysFreeString(pException->szDescription);
			SysFreeString(pException->szSource);
			SysFreeString(pException->szHelpFile);
			ZeroMemory(pException, sizeof(DH_EXCEPTION));
		}

		if (pException->hr == 0)
		{
			/* Only record the error information the first time it is reported */

			pException->hr              = hr;
			pException->iArgError       = iArgError;
			pException->szErrorFunction = szFunctionName;
			pException->bDispatchError  = bDispatchError;

			if (szMember) hlprStringCchCopyW(pException->szMember, ARRAYSIZE(pException->szMember), szMember);

			if (pExcepInfo && hr == DISP_E_EXCEPTION)
			{
				/* Extract error info returned by IDispatch::Invoke in an EXCEPINFO */

				if (pExcepInfo->pfnDeferredFillIn &&
				    !IsBadCodePtr((FARPROC) pExcepInfo->pfnDeferredFillIn)) pExcepInfo->pfnDeferredFillIn(pExcepInfo);

				pException->szDescription = pExcepInfo->bstrDescription;
				pException->szSource      = pExcepInfo->bstrSource;
				pException->szHelpFile    = pExcepInfo->bstrHelpFile;
				pException->dwHelpContext = pExcepInfo->dwHelpContext;
				pException->swCode        = (pExcepInfo->wCode ? pExcepInfo->wCode : pExcepInfo->scode);
			}
		}

		if (nStackCount == 1) /* We are exiting the outer most function */
		{
			pException->bOld              = TRUE;
			pException->szInitialFunction = szFunctionName;

			if (szCompleteMember) hlprStringCchCopyW(pException->szCompleteMember, ARRAYSIZE(pException->szCompleteMember), szCompleteMember);

			if (g_ExceptionOptions.bShowExceptions)
				dhShowException(pException);

			if (g_ExceptionOptions.pfnExceptionCallback)
				g_ExceptionOptions.pfnExceptionCallback(pException);
		}
	}
	else if (hr == DISP_E_EXCEPTION && pExcepInfo)
	{
		/* We are responsible for cleaning up pExcepInfo even if we don't use it */
		SysFreeString(pExcepInfo->bstrDescription);
		SysFreeString(pExcepInfo->bstrSource);
		SysFreeString(pExcepInfo->bstrHelpFile);
	}

	return hr;
}