BOOL CPdd6410Uart::MapHardware() 
{
    if (m_pRegVirtualAddr !=NULL)
    {
        return TRUE;
    }

    // Get IO Window From Registry
    DDKWINDOWINFO dwi;
    if ( GetWindowInfo( &dwi)!=ERROR_SUCCESS || 
    dwi.dwNumMemWindows < 1 || 
    dwi.memWindows[0].dwBase == 0 || 
    dwi.memWindows[0].dwLen < m_dwMemLen)
    {
        return FALSE;
    }

    DWORD dwInterfaceType;
    if (m_ActiveReg.IsKeyOpened() && 
    m_ActiveReg.GetRegValue( DEVLOAD_INTERFACETYPE_VALNAME, (PBYTE)&dwInterfaceType,sizeof(DWORD)))
    {
        dwi.dwInterfaceType = dwInterfaceType;
    }

    // Translate to System Address.
    PHYSICAL_ADDRESS    ioPhysicalBase = { dwi.memWindows[0].dwBase, 0};
    ULONG                inIoSpace = 0;
    if (TranslateBusAddr(m_hParent,(INTERFACE_TYPE)dwi.dwInterfaceType,dwi.dwBusNumber, ioPhysicalBase,&inIoSpace,&ioPhysicalBase))
    {
        // Map it if it is Memeory Mapped IO.
        m_pRegVirtualAddr = MmMapIoSpace(ioPhysicalBase, dwi.memWindows[0].dwLen,FALSE);
    }

    return (m_pRegVirtualAddr!=NULL );
}