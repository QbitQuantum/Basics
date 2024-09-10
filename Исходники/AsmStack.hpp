    /// <summary>
    /// Allocate stack variable
    /// </summary>
    /// <param name="size">Variable size</param>
    /// <returns>Variable memory object</returns>
    asmjit::host::Mem AllocVar( intptr_t size )
    {
        // Align on word length
        size = Align( size, sizeof(size_t) );

#ifdef USE64
        auto val = asmjit::host::Mem( asmjit::host::zsp, static_cast<int32_t>(disp_ofst), static_cast<int32_t>(size) );
#else
        auto val = asmjit::host::Mem( asmjit::host::zbp, -disp_ofst - size, size );
#endif
        disp_ofst += size;
        return val;
    }