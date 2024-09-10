/**********************************************************************
 *          FreeResource     (KERNEL.63)
 */
BOOL16 WINAPI FreeResource16( HGLOBAL16 handle )
{
    FARPROC16 proc;
    HMODULE16 user;
    NE_MODULE *pModule = NE_GetPtr( FarGetOwner16( handle ) );

    TRACE("(%04x)\n", handle );

    /* Try NE resource first */

    if (pModule && pModule->ne_rsrctab)
    {
        NE_TYPEINFO *pTypeInfo = (NE_TYPEINFO *)((char *)pModule + pModule->ne_rsrctab + 2);
        while (pTypeInfo->type_id)
        {
            WORD count;
            NE_NAMEINFO *pNameInfo = (NE_NAMEINFO *)(pTypeInfo + 1);
            for (count = pTypeInfo->count; count > 0; count--)
            {
                if (pNameInfo->handle == handle)
                {
                    if (pNameInfo->usage > 0) pNameInfo->usage--;
                    if (pNameInfo->usage == 0)
                    {
                        GlobalFree16( pNameInfo->handle );
                        pNameInfo->handle = 0;
                        pNameInfo->flags &= ~NE_SEGFLAGS_LOADED;
                    }
                    return FALSE;
                }
                pNameInfo++;
            }
            pTypeInfo = (NE_TYPEINFO *)pNameInfo;
        }
    }

    /* If this failed, call USER.DestroyIcon32; this will check
       whether it is a shared cursor/icon; if not it will call
       GlobalFree16() */
    user = GetModuleHandle16( "user" );
    if (user && (proc = GetProcAddress16( user, "DestroyIcon32" )))
    {
        WORD args[2];
        DWORD result;

        args[1] = handle;
        args[0] = 1;  /* CID_RESOURCE */
        WOWCallback16Ex( (SEGPTR)proc, WCB16_PASCAL, sizeof(args), args, &result );
        return LOWORD(result);
    }
    else
        return GlobalFree16( handle );
}