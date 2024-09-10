/*
 *  call-seq:
 *     WIN32OLE_TYPE.new(typelib, ole_class) -> WIN32OLE_TYPE object
 *
 *  Returns a new WIN32OLE_TYPE object.
 *  The first argument <i>typelib</i> specifies OLE type library name.
 *  The second argument specifies OLE class name.
 *
 *      WIN32OLE_TYPE.new('Microsoft Excel 9.0 Object Library', 'Application')
 *          # => WIN32OLE_TYPE object of Application class of Excel.
 */
static VALUE
foletype_initialize(VALUE self, VALUE typelib, VALUE oleclass)
{
    VALUE file;
    OLECHAR * pbuf;
    ITypeLib *pTypeLib;
    HRESULT hr;

    SafeStringValue(oleclass);
    SafeStringValue(typelib);
    file = typelib_file(typelib);
    if (file == Qnil) {
        file = typelib;
    }
    pbuf = ole_vstr2wc(file);
    hr = LoadTypeLibEx(pbuf, REGKIND_NONE, &pTypeLib);
    if (FAILED(hr))
        ole_raise(hr, eWIN32OLERuntimeError, "failed to LoadTypeLibEx");
    SysFreeString(pbuf);
    if (oleclass_from_typelib(self, pTypeLib, oleclass) == Qfalse) {
        OLE_RELEASE(pTypeLib);
        rb_raise(eWIN32OLERuntimeError, "not found `%s` in `%s`",
                 StringValuePtr(oleclass), StringValuePtr(typelib));
    }
    OLE_RELEASE(pTypeLib);
    return self;
}