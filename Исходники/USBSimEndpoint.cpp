CUSBSimEndpoint::~CUSBSimEndpoint (void)
{
    if (m_Pipe) {
        usbsim_pipe_delete (m_Pipe);
    }
    if (m_pEvents) {
        AtlUnadvise (m_pSoftUSBEndpoint, __uuidof (ISoftUSBEndpointEvents),
                     m_dwCookie);
        m_pEvents->Release ();
    }
    if (m_pSoftUSBEndpoint) {
        m_pSoftUSBEndpoint->Release ();
    }
}