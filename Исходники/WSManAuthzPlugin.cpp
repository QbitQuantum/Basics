/*------------------------------------------------------------------------
typedef VOID (WINAPI * WSMAN_PLUGIN_AUTHORIZE_QUERY_QUOTA)(
    __in PVOID pluginContext,
    __in WSMAN_SENDER_DETAILS *senderDetails,
    __in DWORD flags
    );

This entry point will be called after a user has been authorized to 
retrieve quota information for the user. This method will only be called 
if the configuration specifies that quotas are enabled within the 
authorization plug-in.
  ------------------------------------------------------------------------*/
extern "C" VOID WINAPI WSManPluginAuthzQueryQuota(__in PVOID pluginContext,
                                                  __in WSMAN_SENDER_DETAILS * senderDetails,
                                                  __in DWORD flags)
{
    WSMAN_AUTHZ_QUOTA m_quota;
    ZeroMemory(&m_quota, sizeof(m_quota));
    
    // hardcoded quota limits
    m_quota.maxAllowedConcurrentShells = 2;
    m_quota.maxAllowedConcurrentOperations = 2;
    m_quota.timeslotSize = 60;
    m_quota.maxAllowedOperationsPerTimeslot = 10;

    WSManPluginAuthzQueryQuotaComplete(senderDetails, 
                                       0, 
                                       &m_quota, 
                                       ERROR_SUCCESS, 
                                       NULL);
}