/******************************************************************************
 * IDispatch_Invoke {OLEAUT32}
 *
 * Call an object method.
 *
 * PARAMS
 *  iface        [I] IDispatch interface
 *  dispIdMember [I] DISPID of the method (from GetIDsOfNames())
 *  riid         [I] Reserved, set to IID_NULL
 *  lcid         [I] Locale of the type information to convert parameters with
 *  wFlags,      [I] Kind of method call (DISPATCH_ flags from "oaidl.h")
 *  pDispParams  [I] Array of method arguments
 *  pVarResult   [O] Destination for the result of the call
 *  pExcepInfo   [O] Destination for exception information
 *  puArgErr     [O] Destination for bad argument
 *
 * RETURNS
 *  Success: S_OK.
 *  Failure: See DispInvoke() for failure cases.
 *
 * NOTES
 *  See DispInvoke() and IDispatch().
 */
static HRESULT WINAPI StdDispatch_Invoke(LPDISPATCH iface, DISPID dispIdMember, REFIID riid, LCID lcid,
                                         WORD wFlags, DISPPARAMS * pDispParams, VARIANT * pVarResult,
                                         EXCEPINFO * pExcepInfo, UINT * puArgErr)
{
    StdDispatch *This = impl_from_IDispatch(iface);
    TRACE("(%d, %s, 0x%x, 0x%x, %p, %p, %p, %p)\n", dispIdMember, debugstr_guid(riid), lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);

    if (!IsEqualGUID(riid, &IID_NULL))
    {
        FIXME(" expected riid == IID_NULL\n");
        return E_INVALIDARG;
    }
    return DispInvoke(This->pvThis, This->pTypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
}