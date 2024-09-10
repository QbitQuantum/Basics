/**********************************************************************
 *	    DOSVM_Int25Handler
 *
 * Handler for int 25h (absolute disk read).
 */
void WINAPI DOSVM_Int25Handler( CONTEXT *context )
{
    WCHAR drivespec[4] = {'A', ':', '\\', 0};
    BYTE *dataptr = CTX_SEG_OFF_TO_LIN( context, context->SegDs, context->Ebx );
    DWORD begin;
    DWORD length;

    drivespec[0] += AL_reg( context );

    if (GetDriveTypeW( drivespec ) == DRIVE_NO_ROOT_DIR || 
        GetDriveTypeW( drivespec ) == DRIVE_UNKNOWN)
    {
        SET_CFLAG( context );
        SET_AX( context, 0x0201 ); /* unknown unit */
        return;
    }

    if (CX_reg( context ) == 0xffff)
    {
        begin   = *(DWORD *)dataptr;
        length  = *(WORD *)(dataptr + 4);
        dataptr = (BYTE *)CTX_SEG_OFF_TO_LIN( context,
                                              *(WORD *)(dataptr + 8), 
                                              *(DWORD *)(dataptr + 6) );
    }
    else
    {
        begin  = DX_reg( context );
        length = CX_reg( context );
    }

    DOSVM_RawRead( AL_reg( context ), begin, length, dataptr, TRUE );
    RESET_CFLAG( context );
}