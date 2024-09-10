HRESULT DAPI EseEndSession(
    __in JET_INSTANCE jiInstance,
    __in JET_SESID jsSession
    )
{
    HRESULT hr = S_OK;
    JET_ERR jEr = JET_errSuccess;

    jEr = JetEndSession(jsSession, 0);
    ExitOnJetFailure(jEr, hr, "Failed to end jet session");

    jEr = JetTerm(jiInstance);
    ExitOnJetFailure(jEr, hr, "Failed to uninitialize jet engine instance");

LExit:
    return hr;
}