//-----------------------------------------------------------------------------
// CheckURLProc()
//-----------------------------------------------------------------------------
// ISSUE#XX : nouvelle fonction d'énumération des childs en remplacement
// du GetDlgItem qui ne trouvait pas le bouton "NOuveau mot de passe" 
// de la fenêtre de login de SAP
//-----------------------------------------------------------------------------
static int CALLBACK CheckURLProc(HWND w, LPARAM lp)
{
	int iAction;
	iAction=((T_CHECK_URL*)lp)->iAction;
	int rc=TRUE;
	char szCtrlURL[128+1];
	HRESULT hr;
	IAccessible *pAccessible=NULL;
	BSTR bstrName=NULL;

	TRACE((TRACE_DEBUG,_F_,"GetDlgCtrlID=%d",GetDlgCtrlID(w)));
	// champ trouvé ou non recherché car * (ISSUE#271), il faut vérifier son libellé
	if (GetDlgCtrlID(w)==((T_CHECK_URL*)lp)->iCtrlURL ||
		((T_CHECK_URL*)lp)->iCtrlURL==-9999)
	{
		TRACE((TRACE_DEBUG,_F_,"Champ %d trouve, on verifie son libelle",((T_CHECK_URL*)lp)->iCtrlURL));
		GetWindowText(w,szCtrlURL,sizeof(szCtrlURL));
		TRACE((TRACE_DEBUG,_F_,"GetWindowText(0x%08lx)=%s",w,szCtrlURL));
		if (*szCtrlURL==0) // pas de libellé trouvé, peut-être qu'on est dans un cas type SAP...
		{
			TRACE((TRACE_DEBUG,_F_,"Libelle vide, recherche via API accessibilite"));
			hr=AccessibleObjectFromWindow(w,(DWORD)OBJID_CLIENT,IID_IAccessible,(void**)&pAccessible);
			if (FAILED(hr)) { TRACE((TRACE_ERROR,_F_,"AccessibleObjectFromWindow(IID_IAccessible)=0x%08lx",hr)); goto end; }
			VARIANT vtMe;
			vtMe.vt=VT_I4;
			vtMe.lVal=CHILDID_SELF;
			hr=pAccessible->get_accName(vtMe,&bstrName);
			if (FAILED(hr)) { TRACE((TRACE_ERROR,_F_,"pAccessible->get_accName()=0x%08lx",hr)); goto end; }
			TRACE((TRACE_DEBUG,_F_,"Libelle=%S",bstrName));
			wsprintf(szCtrlURL,"%S",bstrName); // waouh le beau risque de buffer overflow :-)
		}
		if (*szCtrlURL!=0) // // libellé trouvé, on vérifie que c'est le bon 
		{
			if (swStringMatch(szCtrlURL,((T_CHECK_URL*)lp)->pszURL))
			{
				TRACE((TRACE_INFO,_F_,"Trouve le champ !"));
				((T_CHECK_URL*)lp)->bFound=TRUE;
			}
		}
		// ISSUE#271 : si *, on ne vérifie
		if (((T_CHECK_URL*)lp)->iCtrlURL==-9999)
		{
			if (((T_CHECK_URL*)lp)->bFound) 
				rc=FALSE; // si trouvé, on arrête l'énumération
			else
				rc=TRUE; // libellé pas trouvé, on continue
		}
		else
			rc=FALSE;// libellé correct ou pas, on arrête l'énum car on a trouvé un champ avec le bon ID donc inutile d'espérer en trouver un autre
	}
end:
	if (bstrName!=NULL) SysFreeString(bstrName);
	if (pAccessible!=NULL) pAccessible->Release();
	return rc;
}