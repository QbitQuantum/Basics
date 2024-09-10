    // Fills the structure in mk_Memory with a pointer to the resource in memory
    // mk_Resource.sw_Module may be = "" if the cabinet is in the EXE which created the process.
    BOOL GetMemory()
    {
        CStrW sw_ResName = mk_Resource.sw_Name;
        if (mk_Resource.u32_ID) sw_ResName.FormatResource(mk_Resource.u32_ID);

        WCHAR* u16_Module = 0; // Resource is in the calling process
        if (mk_Resource.sw_Module.Len())
            u16_Module = mk_Resource.sw_Module;

        // Load the resource (via Filemapping, there is no memory consumption here)
        HMODULE h_DLL      = GetModuleHandleW(u16_Module);
        HRSRC   h_Resource = FindResourceW(h_DLL, sw_ResName, mk_Resource.sw_Type);
        HGLOBAL h_Global   = LoadResource (h_DLL, h_Resource);

        mk_Memory.p_Addr   = LockResource  (h_Global);
        mk_Memory.s32_Size = SizeofResource(h_DLL, h_Resource);
        mk_Memory.s32_Pos  = 0;

        if (mk_Memory.p_Addr == 0 || mk_Memory.s32_Size == 0)
        {
            mi_Error.Set(FDIERROR_INVAL_RESOURCE,0,0);
            return FALSE;
        }
        return TRUE;
    }