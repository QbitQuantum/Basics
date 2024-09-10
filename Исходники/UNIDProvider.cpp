STDMETHODIMP UNIDProvider::ProvideUNID(BSTR* szUNID)
{
	*szUNID=NULL;
	BSTR guid=NULL;
	if (ProvideGUID(&guid)==S_OK){
		TCHAR *szGuid=OLE2T(guid);
		TCHAR szUnid[33]={0};
		int j=0;
		for (int i=1;i<37;i++){
			if (i!=9 && i!=14 && i!=19 && i!=24) szUnid[j++]=szGuid[i];
		}
		*szUNID=T2BSTR(szUnid);
	}
	return S_OK;
}