HRESULT STDMETHODCALLTYPE 
CRenameExtImpl::GetCommandString(UINT idCmd, UINT uFlags, UINT *pwReserved, LPSTR pszName, UINT cchMax)
{
	HRESULT  hr = E_INVALIDARG;
	int uMaxNameLen = 100;
    if(idCmd != IDM_DISPLAY)
    {
        return hr;
    }

    switch(uFlags)
    {
       	case GCS_HELPTEXTA:        
		case GCS_VERBA:
            lstrcpynA(pszName, "Change File Extention", uMaxNameLen);
            hr = S_OK;
            break; 

		case GCS_HELPTEXTW: 
        case GCS_VERBW: 
            lstrcpynW((LPWSTR)pszName, L"Change File Extention", uMaxNameLen); 
            hr = S_OK;
            break; 
   
        default:
            hr = S_OK;
            break; 
    }
    return hr;
}