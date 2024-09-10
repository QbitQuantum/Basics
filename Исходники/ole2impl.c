/******************************************************************************
 *		OleCreateFromDataEx        [OLE32.@]
 *
 * Creates an embedded object from data transfer object retrieved from
 * the clipboard or OLE drag and drop.
 */
HRESULT WINAPI OleCreateFromDataEx(IDataObject *data, REFIID iid, DWORD flags,
                                   DWORD renderopt, ULONG num_cache_fmts, DWORD *adv_flags, FORMATETC *cache_fmts,
                                   IAdviseSink *sink, DWORD *conns,
                                   IOleClientSite *client_site, IStorage *stg, void **obj)
{
    HRESULT hr;
    UINT src_cf;

    FIXME("(%p, %s, %08x, %08x, %d, %p, %p, %p, %p, %p, %p, %p): stub\n",
          data, debugstr_guid(iid), flags, renderopt, num_cache_fmts, adv_flags, cache_fmts,
          sink, conns, client_site, stg, obj);

    hr = get_storage(data, stg, &src_cf);
    if(FAILED(hr)) return hr;

    hr = OleLoad(stg, iid, client_site, obj);
    if(FAILED(hr)) return hr;

    /* FIXME: Init cache */

    return hr;
}