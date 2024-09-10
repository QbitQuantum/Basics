WERROR NetGetAnyDCName_r(struct libnetapi_ctx *ctx,
                         struct NetGetAnyDCName *r)
{
    NTSTATUS status;
    WERROR werr;
    struct dcerpc_binding_handle *b;
    const char *dcname;
    void *buffer;

    werr = libnetapi_get_binding_handle(ctx, r->in.server_name,
                                        &ndr_table_netlogon,
                                        &b);
    if (!W_ERROR_IS_OK(werr)) {
        goto done;
    }

    status = dcerpc_netr_GetAnyDCName(b, talloc_tos(),
                                      r->in.server_name,
                                      r->in.domain_name,
                                      &dcname,
                                      &werr);
    if (!NT_STATUS_IS_OK(status)) {
        werr = ntstatus_to_werror(status);
        goto done;
    }

    if (!W_ERROR_IS_OK(werr)) {
        goto done;
    }

    if (NetApiBufferAllocate(strlen_m_term(dcname), &buffer)) {
        werr = WERR_NOT_ENOUGH_MEMORY;
        goto done;
    }
    memcpy(buffer, dcname, strlen_m_term(dcname));
    *r->out.buffer = buffer;

done:

    return werr;

}