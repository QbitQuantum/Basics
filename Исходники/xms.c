void WINAPI XMS_Handler( CONTEXT86 *context )
{
    switch(AH_reg(context))
    {
    case 0x00:   /* Get XMS version number */
        TRACE("get XMS version number\n");
        SET_AX( context, 0x0200 ); /* 2.0 */
        SET_BX( context, 0x0000 ); /* internal revision */
        SET_DX( context, 0x0001 ); /* HMA exists */
        break;
    case 0x08:   /* Query Free Extended Memory */
    {
        MEMORYSTATUS status;

        TRACE("query free extended memory\n");
        GlobalMemoryStatus( &status );
        SET_DX( context, status.dwAvailVirtual >> 10 );
        SET_AX( context, status.dwAvailVirtual >> 10 );
        TRACE("returning largest %dK, total %dK\n", AX_reg(context), DX_reg(context));
    }
    break;
    case 0x09:   /* Allocate Extended Memory Block */
        TRACE("allocate extended memory block (%dK)\n",
            DX_reg(context));
	SET_DX( context, GlobalAlloc16(GMEM_MOVEABLE, (DWORD)DX_reg(context)<<10) );
	SET_AX( context, DX_reg(context) ? 1 : 0 );
	if (!DX_reg(context)) SET_BL( context, 0xA0 ); /* out of memory */
	break;
    case 0x0a:   /* Free Extended Memory Block */
	TRACE("free extended memory block %04x\n",DX_reg(context));
       if(!DX_reg(context) || GlobalFree16(DX_reg(context))) {
         SET_AX( context, 0 );    /* failure */
         SET_BL( context, 0xa2 ); /* invalid handle */
       } else
         SET_AX( context, 1 );    /* success */
	break;
    case 0x0b:   /* Move Extended Memory Block */
    {
	MOVESTRUCT*move=CTX_SEG_OFF_TO_LIN(context,
	    context->SegDs,context->Esi);
        BYTE*src,*dst;
        TRACE("move extended memory block\n");
        src=XMS_Offset(&move->Source);
        dst=XMS_Offset(&move->Dest);
	memcpy(dst,src,move->Length);
	if (move->Source.Handle) GlobalUnlock16(move->Source.Handle);
	if (move->Dest.Handle) GlobalUnlock16(move->Dest.Handle);
	break;
    }
    case 0x88:   /* Query Any Free Extended Memory */
    {
        MEMORYSTATUS status;
        SYSTEM_INFO  info;

        TRACE("query any free extended memory\n");

        GlobalMemoryStatus( &status );
        GetSystemInfo( &info );
        context->Eax = status.dwAvailVirtual >> 10;
        context->Edx = status.dwAvailVirtual >> 10;
        context->Ecx = (DWORD)info.lpMaximumApplicationAddress;
        SET_BL( context, 0 ); /* No errors. */

        TRACE("returning largest %dK, total %dK, highest 0x%x\n",
              context->Eax, context->Edx, context->Ecx);
    }
    break;
    default:
        INT_BARF( context, 0x31 );
        SET_AX( context, 0x0000 ); /* failure */
        SET_BL( context, 0x80 );   /* function not implemented */
        break;
    }
}