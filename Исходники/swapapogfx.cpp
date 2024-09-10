//-------------------------------------------------------------------------
// Description:
//
//  Destructor.
//
// Parameters:
//
//     void
//
// Return values:
//
//      void
//
// Remarks:
//
//      This method deletes whatever was allocated.
//
//      This method may not be called from a real-time processing thread.
//
CSwapAPOGFX::~CSwapAPOGFX(void)
{
    if (m_bIsInitialized)
    {
        //
        // unregister for callbacks
        //
        if (m_spEnumerator != NULL)
        {
            m_spEnumerator->UnregisterEndpointNotificationCallback(this);
        }
    }
    // Free locked memory allocations
    if (NULL != m_pf32Coefficients)
    {
        AERT_Free(m_pf32Coefficients);
        m_pf32Coefficients = NULL;
    }
} // ~CSwapAPOGFX