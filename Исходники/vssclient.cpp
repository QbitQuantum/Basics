// Initialize the COM infrastructure and the internal pointers
void VssClient::Initialize(DWORD dwContext, wstring xmlDoc, bool bDuringRestore)
{
    FunctionTracer ft(DBG_INFO);

    // Initialize COM 
    CHECK_COM( CoInitialize(NULL) );
    m_bCoInitializeCalled = true;

    // Initialize COM security
    CHECK_COM( 
        CoInitializeSecurity(
            NULL,                           //  Allow *all* VSS writers to communicate back!
            -1,                             //  Default COM authentication service
            NULL,                           //  Default COM authorization service
            NULL,                           //  reserved parameter
            RPC_C_AUTHN_LEVEL_PKT_PRIVACY,  //  Strongest COM authentication level
            RPC_C_IMP_LEVEL_IDENTIFY,       //  Minimal impersonation abilities 
            NULL,                           //  Default COM authentication settings
            EOAC_NONE,                      //  No special options
            NULL                            //  Reserved parameter
            ) );

    // Create the internal backup components object
    CHECK_COM( CreateVssBackupComponents(&m_pVssObject) );
    
    // We are during restore now?
    m_bDuringRestore = bDuringRestore;

    // Call either Initialize for backup or for restore
    if (m_bDuringRestore)
    {
        CHECK_COM(m_pVssObject->InitializeForRestore(CComBSTR(xmlDoc.c_str())))
    }
    else
    {
        // Initialize for backup
        if (xmlDoc.length() == 0)