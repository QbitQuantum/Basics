void CPolicyStore::ConnectionMethodsLC(
    RArray<TUint32>& aVpnConnections,
    RCmManager& aCmManager,
    const TVpnPolicyId& aPolicyId,
    TBool& aPolicyActive)
    {
using namespace CMManager;         
    LOG_1("CPolicyStore::ConnectionMethodsLC : %S", &aPolicyId);
    CleanupClosePushL( aVpnConnections );

    aCmManager.ConnectionMethodL( 
        aVpnConnections,
        ETrue,
        EFalse,
        EFalse ); 
    LOG_1("CPolicyStore::ConnectionMethodsLC cnt: %d", 
        aVpnConnections.Count());
    
    TInt index(aVpnConnections.Count());
    
    while( index )
        {
        --index;
        LOG_1("CPolicyStore::ConnectionMethodsLC at: %d", index);
        TUint32 id(aVpnConnections[index]);
        RCmConnectionMethod connectioMethod = 
            aCmManager.ConnectionMethodL( id );
        CleanupClosePushL( connectioMethod );  
        if( connectioMethod.GetIntAttributeL(ECmBearerType) != 
            KPluginVPNBearerTypeUid )
            {
            aVpnConnections.Remove( index );
            }
        else
            {
            HBufC* policyId = connectioMethod.GetStringAttributeL(
                EVpnServicePolicy);
            if( aPolicyId.Compare( *policyId ) )
                {
                aVpnConnections.Remove( index );
                }
            else
                {
                if( connectioMethod.GetBoolAttributeL(ECmConnected) )
                    {
                    LOG_1("PolicyActiveL:%d", index);
                    aPolicyActive = ETrue;
                    }
                }
            delete policyId;      
            }
        CleanupStack::PopAndDestroy(); // connectioMethod 
        }
    }