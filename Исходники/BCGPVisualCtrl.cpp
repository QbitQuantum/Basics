//***********************************************************************************************************
LRESULT CBCGPBaseVisualCtrl::OnGetObject(WPARAM wParam, LPARAM lParam)
{
#ifndef _BCGPCHART_STANDALONE
	if (globalData.IsAccessibilitySupport ())
	{
		
        if ((DWORD)lParam == OBJID_CLIENT)
		{
			CBCGPBaseAccessibleObject* pVisualObject = DYNAMIC_DOWNCAST(CBCGPBaseAccessibleObject, GetVisualBaseObject());
			if (pVisualObject == NULL || !pVisualObject->IsAccessibilityCompatible())
			{
				return 0;
			}
			

			LPUNKNOWN pUnknown = pVisualObject->GetInterface(&IID_IAccessible);
			if (pUnknown == NULL)
			{
				return 0;
			}
			
			pVisualObject->OnSetIAccessible((IAccessible*)pUnknown);
			
			return LresultFromObject(IID_IAccessible, wParam, pUnknown);
		}
	}
#endif	
	return (LRESULT)0L;
}	