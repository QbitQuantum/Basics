/**
 *
 * Method Name: TerminateRTCPConnection
 *
 *
 * Inputs:   IRTCPConnection *piRTCPConnection
 *                     - The Connection Interface pointer returned on creation
 *
 * Outputs:  None
 *
 * Returns:  bool
 *
 * Description:  The TerminateRTCPConnection() method shall manage the
 *               termination of and RTCP session.  This shall include the
 *               graceful release of all associated objects as well as the
 *               deallocation of all resources associated with each contained
 *               RTCP connection.
 *
 *
 * Usage Notes:
 *
 *
 */
bool CRTCPSession::TerminateRTCPConnection(IRTCPConnection *piRTCPConnection)
{
    CRTCPConnection *poRTCPConnection;

    // Remove the RTCP Connection object from the collection list
    if((poRTCPConnection = RemoveEntry(RTCPConnectionComparitor,
                                      (void *)piRTCPConnection)) != NULL)
    {
        
#if RTCP_DEBUG /* [ */
        if(bPingtelDebug)
        {
            osPrintf("*** RTCP CONNECTION TERMINATED ****\n");
            osPrintf("\t ON SESSION ==> %d\n", GetSessionID());
            osPrintf("\t TO SSRC    ==> %u\n",
                                           piRTCPConnection->GetRemoteSSRC());
        }
#endif /* RTCP_DEBUG ] */

        // Terminate RTCPConnection and release reference
        poRTCPConnection->Terminate();

        // Release reference twice.  Once for its removal from the collection
        //  and once on behalf fo the client since this method serves to
        //  terminate the connection and release the client's reference.
        ((IRTCPConnection *)poRTCPConnection)->Release();
        ((IRTCPConnection *)poRTCPConnection)->Release();

        return(TRUE);
    }

    return(FALSE);
}