/// <summary>
/// Copy original bytes using LDASM
/// </summary>
/// <param name="pFunc">Original function ptr</param>
/// <param name="OriginalStore">Buffer to store bytes</param>
/// <param name="pSize">Lenght of copied data</param>
/// <returns>Status code</returns>
NTSTATUS PHpCopyCode( IN PVOID pFunc, OUT PUCHAR OriginalStore, OUT PULONG pSize )
{
    // Store original bytes
    PUCHAR src = pFunc;
    PUCHAR old = OriginalStore;
    ULONG all_len = 0;
    ldasm_data ld = { 0 };

    do
    {
        ULONG len = ldasm( src, &ld, TRUE );

        // Determine code end
        if (ld.flags & F_INVALID
            || (len == 1 && (src[ld.opcd_offset] == 0xCC || src[ld.opcd_offset] == 0xC3))
            || (len == 3 && src[ld.opcd_offset] == 0xC2)
            || len + all_len > 128)
        {
            break;
        }

        // move instruction 
        memcpy( old, src, len );

        // if instruction has relative offset, calculate new offset 
        if (ld.flags & F_RELATIVE)
        {
            LONG diff = 0;
            const uintptr_t ofst = (ld.disp_offset != 0 ? ld.disp_offset : ld.imm_offset);
            const uintptr_t sz = ld.disp_size != 0 ? ld.disp_size : ld.imm_size;

            memcpy( &diff, src + ofst, sz );
            // exit if jump is greater then 2GB
            if (_abs64( src + len + diff - old ) > INT_MAX)
            {
                break;
            }
            else
            {
                diff += (LONG)(src - old);
                memcpy( old + ofst, &diff, sz );
            }
        }

        src += len;
        old += len;
        all_len += len;

    } while (all_len < sizeof( JUMP_THUNK ));

    // Failed to copy old code, use backup plan
    if (all_len < sizeof( JUMP_THUNK ))
    {
        return STATUS_UNSUCCESSFUL;
    }
    else
    {
        PHpInitJumpThunk( (PJUMP_THUNK)old, (ULONG64)src );
        *pSize = all_len;
    }

    return STATUS_SUCCESS;
}