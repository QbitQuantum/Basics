    void MemoryOsSpecific::fillBuffer( u8 *buffer, u64 offset, unsigned int length) const
    {

        if( EnumSystemFirmwareTables && GetSystemFirmwareTable )
        {
            // Use the newer W2K3 SP1 APIs if they are available.
            // If we first call readPhysicalMemoryMap and readPhysicalMemoryDebugSysctl
            // and then call enumSystemFirmwareTables, the new GetSystemFirmwareTable API
            // of W2K3 SP1 returns invalid data.
            enumSystemFirmwareTables( buffer, offset, length );
        }
        else
        {
            HANDLE hPhysMem = static_cast<HANDLE>(osData);
            if(hPhysMem)
            {
                readPhysicalMemoryMap( hPhysMem, buffer, offset, length );
            }
            else
            {
                readPhysicalMemoryDebugSysctl( buffer, offset, length );
            }
        }
    }