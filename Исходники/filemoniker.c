/******************************************************************************
 *        FileMoniker_Inverse
 */
static HRESULT WINAPI
FileMonikerImpl_Inverse(IMoniker* iface,IMoniker** ppmk)
{
    TRACE("(%p,%p)\n",iface,ppmk);

    return CreateAntiMoniker(ppmk);
}