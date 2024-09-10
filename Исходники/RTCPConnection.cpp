/**
 *
 * Method Name: ~CRTCPConnection() - Destructor
 *
 *
 * Inputs:      None
 *
 * Outputs:     None
 *
 * Returns:     None
 *
 * Description: Shall deallocated and/or release all resources which was
 *              acquired over the course of runtime.  In particular, the
 *              following shall occur:
 *                ==> Shall release the reference to the RTCP Render object
 *                ==> Shall release the reference to the RTCP Source object
 *
 * Usage Notes:
 *
 *
 */
CRTCPConnection::~CRTCPConnection(void)
{

    // Terminate Connection and release any remaining references to interfaces
    //  and objects
    Terminate();
    m_piRTCPNotify->Release();
    m_piSDESReport->Release();

}