static HRESULT WINAPI RegExp2_Execute(IRegExp2 *iface,
                                      BSTR sourceString, IDispatch **ppMatches)
{
    RegExp2 *This = impl_from_IRegExp2(iface);
    match_state_t *result;
    const WCHAR *pos;
    IMatchCollection2 *match_collection;
    IMatch2 *add = NULL;
    HRESULT hres;

    TRACE("(%p)->(%s %p)\n", This, debugstr_w(sourceString), ppMatches);

    if(!This->pattern) {
        DWORD i, len = SysStringLen(sourceString);

        hres = create_match_collection2(&match_collection);
        if(FAILED(hres))
            return hres;

        for(i=0; i<=len; i++) {
            hres = create_match2(i, NULL, &add);
            if(FAILED(hres))
                break;

            hres = add_match(match_collection, add);
            if(FAILED(hres))
                break;
            IMatch2_Release(add);

            if(!(This->flags & REG_GLOB))
                break;
        }

        if(FAILED(hres)) {
            IMatchCollection2_Release(match_collection);
            return hres;
        }

        *ppMatches = (IDispatch*)match_collection;
        return S_OK;
    }

    if(!This->regexp) {
        This->regexp = regexp_new(NULL, &This->pool, This->pattern,
                                  strlenW(This->pattern), This->flags, FALSE);
        if(!This->regexp)
            return E_FAIL;
    } else {
        hres = regexp_set_flags(&This->regexp, NULL, &This->pool, This->flags);
        if(FAILED(hres))
            return hres;
    }

    hres = create_match_collection2(&match_collection);
    if(FAILED(hres))
        return hres;

    pos = sourceString;
    while(1) {
        result = alloc_match_state(This->regexp, NULL, pos);
        if(!result) {
            hres = E_OUTOFMEMORY;
            break;
        }

        hres = regexp_execute(This->regexp, NULL, &This->pool,
                              sourceString, SysStringLen(sourceString), result);
        if(hres != S_OK) {
            heap_free(result);
            break;
        }
        pos = result->cp;

        hres = create_match2(result->cp-result->match_len-sourceString, &result, &add);
        heap_free(result);
        if(FAILED(hres))
            break;
        hres = add_match(match_collection, add);
        IMatch2_Release(add);
        if(FAILED(hres))
            break;

        if(!(This->flags & REG_GLOB))
            break;
    }

    if(FAILED(hres)) {
        IMatchCollection2_Release(match_collection);
        return hres;
    }

    *ppMatches = (IDispatch*)match_collection;
    return S_OK;
}