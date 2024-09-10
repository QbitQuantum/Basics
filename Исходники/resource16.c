/**********************************************************************
 *          LoadResource     (KERNEL.61)
 */
HGLOBAL16 WINAPI LoadResource16( HMODULE16 hModule, HRSRC16 hRsrc )
{
    NE_TYPEINFO *pTypeInfo;
    NE_NAMEINFO *pNameInfo = NULL;
    NE_MODULE *pModule = get_module( hModule );
    int d;

    if (!hRsrc || !pModule) return 0;

    if (pModule->module32)
    {
        /* load 32-bit resource and convert it */
        HRSRC hRsrc32 = MapHRsrc16To32( pModule, hRsrc );
        WORD type     = MapHRsrc16ToType( pModule, hRsrc );
        HGLOBAL hMem  = LoadResource( pModule->module32, hRsrc32 );
        DWORD size    = SizeofResource( pModule->module32, hRsrc32 );
        if (!hMem) return 0;
        return NE_LoadPEResource( pModule, type, LockResource( hMem ), size );
    }

    /* first, verify hRsrc (just an offset from pModule to the needed pNameInfo) */

    d = pModule->ne_rsrctab + 2;
    pTypeInfo = (NE_TYPEINFO *)((char *)pModule + d);
    while( hRsrc > d )
    {
        if (pTypeInfo->type_id == 0) break; /* terminal entry */
        d += sizeof(NE_TYPEINFO) + pTypeInfo->count * sizeof(NE_NAMEINFO);
        if (hRsrc < d)
        {
            if( ((d - hRsrc)%sizeof(NE_NAMEINFO)) == 0 )
            {
                pNameInfo = (NE_NAMEINFO *)((char *)pModule + hRsrc);
                break;
            }
            else break; /* NE_NAMEINFO boundary mismatch */
        }
        pTypeInfo = (NE_TYPEINFO *)((char *)pModule + d);
    }

    if (pNameInfo)
    {
        if (pNameInfo->handle && !(GlobalFlags16(pNameInfo->handle) & GMEM_DISCARDED))
        {
            pNameInfo->usage++;
            TRACE("  Already loaded, new count=%d\n", pNameInfo->usage );
        }
        else
        {
            FARPROC16 resloader;
            memcpy_unaligned( &resloader, &pTypeInfo->resloader, sizeof(FARPROC16) );
            if (resloader && resloader != get_default_res_handler())
            {
                WORD args[3];
                DWORD ret;

                args[2] = pNameInfo->handle;
                args[1] = pModule->self;
                args[0] = hRsrc;
                WOWCallback16Ex( (DWORD)resloader, WCB16_PASCAL, sizeof(args), args, &ret );
                pNameInfo->handle = LOWORD(ret);
            }
            else
                pNameInfo->handle = NE_DefResourceHandler( pNameInfo->handle, pModule->self, hRsrc );

            if (pNameInfo->handle)
            {
                pNameInfo->usage++;
                pNameInfo->flags |= NE_SEGFLAGS_LOADED;
            }
        }
        return pNameInfo->handle;
    }
    return 0;
}