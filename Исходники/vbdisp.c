static HRESULT invoke_variant_prop(VARIANT *v, WORD flags, DISPPARAMS *dp, VARIANT *res)
{
    HRESULT hres;

    switch(flags) {
    case DISPATCH_PROPERTYGET|DISPATCH_METHOD:
    case DISPATCH_PROPERTYGET:
        if(dp->cArgs) {
            WARN("called with arguments\n");
            return DISP_E_MEMBERNOTFOUND; /* That's what tests show */
        }

        hres = VariantCopyInd(res, v);
        break;

    case DISPATCH_PROPERTYPUT: {
        VARIANT *put_val;

        put_val = get_propput_arg(dp);
        if(!put_val) {
            WARN("no value to set\n");
            return DISP_E_PARAMNOTOPTIONAL;
        }

        if(arg_cnt(dp)) {
            FIXME("Arguments not supported\n");
            return E_NOTIMPL;
        }

        if(res)
            V_VT(res) = VT_EMPTY;

        hres = VariantCopyInd(v, put_val);
        break;
    }

    default:
        FIXME("unimplemented flags %x\n", flags);
        return E_NOTIMPL;
    }

    return hres;
}