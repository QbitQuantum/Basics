///////////////////////////////////////////////////////////////
//
// CVideoModeManager::IsMultiMonitor
//
//
//
///////////////////////////////////////////////////////////////
bool CVideoModeManager::IsMultiMonitor ( void )
{
    if ( m_ulMonitorCount == 0 )
    {
        // Count attached monitors
        for ( int i = 0 ; true ; i++ )
        {
            DISPLAY_DEVICE device;
            device.cb = sizeof(device);

            // Get next DISPLAY_DEVICE from the system
            if( !EnumDisplayDevicesA ( NULL, i, &device, 0 ) )
                break;

            // Calc flags
            bool bAttachedToDesktop = ( device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP ) != 0;
            bool bMirroringDriver   = ( device.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER ) != 0;
            bool bPrimaryDevice     = ( device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE ) != 0;

            // Ignore devices that are not required
            if( !bAttachedToDesktop || bMirroringDriver )
                continue;

            m_ulMonitorCount++;
        }
    }

    return m_ulMonitorCount > 1;
}