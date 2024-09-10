MI_Result
OMIInterface::Connect ()
{
    util::unique_ptr<MI_Instance, MI_Result (*)(MI_Instance*)> pError (
        NULL, MI_Instance_Delete);
    MI_Instance* pTemp = NULL;
    MI_Result result = MI_Application_Initialize (0, NULL, &pTemp, &m_App);
    pError.reset (pTemp);
    if (MI_RESULT_OK == result)
    {
        result = MI_Application_NewSession (
            &m_App, NULL, NULL, NULL, NULL, &pTemp, &m_Session);
        pError.reset (pTemp);
        if (MI_RESULT_OK == result)
        {
            result = MI_Application_NewOperationOptions (
                &m_App, MI_FALSE, &m_Options);
            if (MI_RESULT_OK == result)
            {
                MI_Interval timeoutInterval;
                memset (&timeoutInterval, 0, sizeof (MI_Interval));
                timeoutInterval.seconds = 30;
                timeoutInterval.minutes = 1;
                result = MI_OperationOptions_SetTimeout (
                    &m_Options, &timeoutInterval);
            }
        }
    }
    if (MI_RESULT_OK != result)
    {
        Disconnect ();
    }
    return result;
}