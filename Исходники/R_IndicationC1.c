static MI_Result MI_CALL _SetIndicationProperties_Impl(
    _In_ void* cfg,
    _Outptr_ MI_Instance** indication)
{
    MI_Result r = MI_RESULT_OK;
    Config* config = (Config*)cfg;
    DEBUG_ASSERT (indication);
    *indication = NULL;
    {
        MI_Boolean match;
        R_IndicationC1* inst;

        MI_Context* context = config->postctx;
        r = MI_Context_NewInstance(context, &R_IndicationC1_rtti, indication);
        CHKMIRESULTRETURN(r, "MI_Context_NewInstance failed");

        L_Indication_SetIndicationProperties(cfg, *indication);
        CHKSETPROPERTY(r, "L_Indication Properties");

        inst = (R_IndicationC1*) (*indication);
        r = R_IndicationC1_Set_message(inst, MI_T("test indication message"));
        CHKSETPROPERTY(r, "message");
        r = R_IndicationC1_Set_id(inst, config->count);
        CHKSETPROPERTY(r, "id");
        r = R_IndicationC1_Set_rcode1(inst, config->count);
        CHKSETPROPERTY(r, "rcode1");

        r = class_TestFilter(config, &inst->__instance, &match);
        if (r == MI_RESULT_OK)
        {
            if (match == MI_FALSE)
            {
                LOGMSG(("Indication does not match filter"));
            }
        }
    }
    return r;
}