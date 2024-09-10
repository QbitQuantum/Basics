float32 IfxScuCcu_setSriFrequency(float32 sriFreq)
{
    float32         freq   = 0;
    float32         source = IfxScuCcu_getSourceFrequency();
    Ifx_SCU_CCUCON0 ccucon0;
    uint16          l_SEndInitPW;
    uint32          sriDiv = (uint32)__roundf(source / sriFreq);
    sriDiv = __maxu(sriDiv, 1);

    if ((sriDiv >= 7) && (sriDiv < 14) && ((sriDiv & 1) == 1))
    {
        sriDiv = sriDiv - 1;
    }

    if (sriDiv == 14)
    {
        sriDiv = 12;
    }

    l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword();
    IfxScuWdt_clearSafetyEndinit(l_SEndInitPW);

    ccucon0.U        = SCU_CCUCON0.U;
    ccucon0.B.SRIDIV = sriDiv;
    ccucon0.B.UP     = 1;
    SCU_CCUCON0.U    = ccucon0.U;

    IfxScuWdt_setSafetyEndinit(l_SEndInitPW);

    while (SCU_CCUCON0.B.LCK != 0U)
    {}

    freq = IfxScuCcu_getSriFrequency();
    return freq;
}