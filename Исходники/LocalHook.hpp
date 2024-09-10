    /// <summary>
    /// Perform int3 hook
    /// </summary>
    /// <returns>true on success</returns>
    bool HookInt3()
    {
        this->_newCode[0] = 0xCC;
        this->_origSize = sizeof( this->_newCode[0] );

        // Setup handler
        if (this->_vecHandler == nullptr)
            this->_vecHandler = AddVectoredExceptionHandler( 1, &DetourBase::VectoredHandler );

        if (!this->_vecHandler)
            return false;

        this->_breakpoints.insert( std::make_pair( this->_original, (DetourBase*)this ) );

        // Save original code
        memcpy( this->_origCode, this->_original, this->_origSize );

        // Write break instruction
        DWORD flOld = 0;
        VirtualProtect( this->_original, this->_origSize, PAGE_EXECUTE_READWRITE, &flOld );
        memcpy( this->_original, this->_newCode, this->_origSize );
        VirtualProtect( this->_original, this->_origSize, flOld, &flOld );

        WriteProcessMemory( GetCurrentProcess(), this->_original, this->_newCode, this->_origSize, NULL );

        return this->_hooked = TRUE;
    }