BOOL PLUGIN_FILTER_FILTERACE(
    _In_ PLUGIN_API_TABLE const * const api,
    _Inout_ PIMPORTED_ACE ace
) {
    PSID trusteeSidAce = api->Ace.GetTrustee(ace);

    if (gs_TrusteeFilter == NULL && gs_TrusteeDnFilter != NULL) {
        PIMPORTED_OBJECT object = api->Resolver.GetObjectByDn(gs_TrusteeDnFilter);
        if (!object) {
            API_FATAL(_T("Cannot resolve DN <%s>"), gs_TrusteeDnFilter);
        }
        gs_TrusteeFilter = &object->imported.sid;
    }

    return EqualSid(trusteeSidAce, gs_TrusteeFilter);
}