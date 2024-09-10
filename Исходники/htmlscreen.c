static HRESULT WINAPI HTMLScreen_get_availWidth(IHTMLScreen *iface, LONG *p)
{
    HTMLScreen *This = impl_from_IHTMLScreen(iface);
    RECT work_area;

    TRACE("(%p)->(%p)\n", This, p);

    if(!SystemParametersInfoW(SPI_GETWORKAREA, 0, &work_area, 0))
        return E_FAIL;

    *p = work_area.right-work_area.left;
    return S_OK;
}