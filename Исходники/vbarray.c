static HRESULT VBArrayConstr_value(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    VBArrayInstance *vbarray;
    HRESULT hres;

    TRACE("\n");

    switch(flags) {
    case DISPATCH_METHOD:
        if(argc<1 || !is_variant(argv[0]) || V_VT(get_variant(argv[0])) != (VT_ARRAY|VT_VARIANT))
            return throw_type_error(ctx, JS_E_VBARRAY_EXPECTED, NULL);

        return jsval_copy(argv[0], r);

    case DISPATCH_CONSTRUCT:
        if(argc<1 || !is_variant(argv[0]) || V_VT(get_variant(argv[0])) != (VT_ARRAY|VT_VARIANT))
            return throw_type_error(ctx, JS_E_VBARRAY_EXPECTED, NULL);

        hres = alloc_vbarray(ctx, NULL, &vbarray);
        if(FAILED(hres))
            return hres;

        hres = SafeArrayCopy(V_ARRAY(get_variant(argv[0])), &vbarray->safearray);
        if(FAILED(hres)) {
            jsdisp_release(&vbarray->dispex);
            return hres;
        }

        *r = jsval_obj(&vbarray->dispex);
        break;

    default:
        FIXME("unimplemented flags: %x\n", flags);
        return E_NOTIMPL;
    }

    return S_OK;
}