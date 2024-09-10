LRESULT CBCGPWnd::OnGetObject(WPARAM wParam, LPARAM lParam)
{
	if (globalData.IsAccessibilitySupport () &&
		IsAccessibilityCompatible ())
	{

#if _MSC_VER >= 1300
		return CWnd::OnGetObject (wParam, lParam);
#else
        if ((DWORD)lParam == OBJID_CLIENT)
		{
			LPUNKNOWN pUnknown = GetInterface(&IID_IAccessible);
			if (!pUnknown)
			{
				return E_FAIL;
			}

			m_pStdObject = (IAccessible*)pUnknown;

			return LresultFromObject(IID_IAccessible, wParam, pUnknown);
		}
#endif
	}

	return (LRESULT)0L;
}	