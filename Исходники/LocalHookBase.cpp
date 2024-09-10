/// <summary>
/// Copy original function bytes
/// </summary>
/// <param name="Ptr">Origianl function address</param>
void DetourBase::CopyOldCode( uint8_t* ptr )
{ 
    // Store original bytes
    uint8_t* src = ptr;
    uint8_t* thunk = _origThunk, *original = _origCode;
    uint32_t all_len = 0;
    ldasm_data ld = { 0 };

    do 
    {
        uint32_t len = ldasm( src, &ld, is_x64 );

        // Determine code end
        if (ld.flags & F_INVALID
                || (len == 1 && (src[ld.opcd_offset] == 0xCC || src[ld.opcd_offset] == 0xC3))
                || (len == 3 && src[ld.opcd_offset] == 0xC2)
                || len + all_len > 128)
        {
            break;
        }

        // move instruction 
        memcpy( original, src, len );
        memcpy( thunk, src, len );

        // if instruction has relative offset, calculate new offset 
        if (ld.flags & F_RELATIVE)
        {
            int32_t diff = 0;
            const uintptr_t ofst = (ld.disp_offset != 0 ? ld.disp_offset : ld.imm_offset);
            const uintptr_t sz = ld.disp_size != 0 ? ld.disp_size : ld.imm_size;

            memcpy( &diff, src + ofst, sz );

        #ifdef USE64
            // exit if jump is greater then 2GB
            if (_abs64( src + len + diff - thunk ) > INT_MAX)
            {
                break;
            }
            else
            {
                diff += static_cast<int32_t>(src - thunk);
                memcpy( thunk + ofst, &diff, sz );
            }
        #else
            diff += src - thunk;
            memcpy( thunk + ofst, &diff, sz );
        #endif
        }

        src += len;
        thunk += len;
        original += len;
        all_len += len;
    } while (all_len < _origSize);

    // Failed to copy old code, use backup plan
    if (all_len < _origSize)
    {
        _type = HookType::InternalInline;
        memcpy( _origCode, ptr, _origSize );
    }         
    else
    {
        SET_JUMP( thunk, src );
        _callOriginal = _origThunk;
    } 
}