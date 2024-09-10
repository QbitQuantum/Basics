HRESULT CMObject::GetActiveObject(const CLSID clsid)
{
	HRESULT hr;
	IDispatchPtr tmpobj;
	Release();
	hr=tmpobj.GetActiveObject(clsid);
	if(SUCCEEDED(hr))
		p=tmpobj.Detach();
	return hr;

}