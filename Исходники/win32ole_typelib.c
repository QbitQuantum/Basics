/*
 *  call-seq:
 *     WIN32OLE_TYPELIB#path -> The type library file path.
 *
 *  Returns the type library file path.
 *
 *     tlib = WIN32OLE_TYPELIB.new('Microsoft Excel 9.0 Object Library')
 *     puts tlib.path #-> 'C:\...\EXCEL9.OLB'
 */
static VALUE
foletypelib_path(VALUE self)
{
    TLIBATTR *pTLibAttr;
    HRESULT hr = S_OK;
    BSTR bstr;
    LCID lcid = cWIN32OLE_lcid;
    VALUE path;
    ITypeLib *pTypeLib;

    pTypeLib = itypelib(self);
    oletypelib_get_libattr(pTypeLib, &pTLibAttr);
    hr = QueryPathOfRegTypeLib(&pTLibAttr->guid,
	                       pTLibAttr->wMajorVerNum,
			       pTLibAttr->wMinorVerNum,
			       lcid,
			       &bstr);
    if (FAILED(hr)) {
	pTypeLib->lpVtbl->ReleaseTLibAttr(pTypeLib, pTLibAttr);
	ole_raise(hr, eWIN32OLERuntimeError, "failed to QueryPathOfRegTypeTypeLib");
    }

    pTypeLib->lpVtbl->ReleaseTLibAttr(pTypeLib, pTLibAttr);
    path = WC2VSTR(bstr);
    return path;
}