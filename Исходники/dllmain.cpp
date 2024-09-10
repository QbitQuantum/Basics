DWORD WINAPI StormThread1( void )
{
    // Local Variables
    int iCount = 0 ;
    //static Sync CritSec;

    Sleep( 1000 ) ; // Sleep 1 second

    Log("\n ====================================================== ") ;
    Log("\n =============== StormThread1 SEPERATOR =============== ") ;
    Log("\n ====================================================== ") ;

    do
    {
        if( iCount != 3 )
        {
            pGlobal->g_Game_Mod_Base   = (DWORD64)( GetModuleHandle( "H1Z1.exe" ) ) ;
            pGlobal->g_H_Game_Mod_Base = (HANDLE)pGlobal->g_Game_Mod_Base ;
            pGlobal->g_D3D9_Mod_Base   = (DWORD64)( GetModuleHandle( "d3d9.dll" ) ) ;
            Sleep( 100 ) ; // Sleep .1 second
        } else
        {
            Log( "Global Bases Failed: %d\n", iCount ) ;
            break ;
        }
        iCount++ ;
    } while( !pGlobal->g_Game_Mod_Base && !pGlobal->g_D3D9_Mod_Base ) ;
    //Log( "\nH1Z1.exe - Base Address: %016llX", pGlobal->g_Game_Mod_Base ) ;
    //Log( "\nH1Z1.exe - Handle: %08X", pGlobal->g_H_Game_Mod_Base ) ;
    //Log( "\ng_D3D_Mod_Base: %016llX", pGlobal->g_D3D9_Mod_Base ) ;

    pGlobal->g_Game_Mod_Size = (DWORD64)GetModuleSize( "H1Z1.exe" ) ;
    //Log( "\nH1Z1.exe - Size: %016llX\n", pGlobal->g_Game_Mod_Size ) ;

    // Setup Overlay
    OverlayWindow( VTable ) ;

    // Enable Debug Privileges
    EnableDebugPriv() ;

    // OpenProcess with All Access
    pGlobal->g_PseudoHandle = GetCurrentProcess() ;
    //Log( "PseudoHandle: %016llX\n", pGlobal->g_PseudoHandle ) ;
    pGlobal->g_AllAccess_Process_Handle = OpenProcess( PROCESS_ALL_ACCESS, FALSE, Get_PID_From_Process_Handle( pGlobal->g_PseudoHandle ) ) ;
    Log( "All Access Handle: %016llX\n", pGlobal->g_AllAccess_Process_Handle ) ;

    /* =========================================================================== */
    /* Present() & Gameoverlayrenderer64 HOOK Related Information */
    /* =========================================================================== */

    // Define & Initialize Patch Info Structure
    pPatchInfo = (PPATCH_INFO)malloc( sizeof( PATCH_INFO ) ) ;
    memset( pPatchInfo, 0xEE, sizeof(PATCH_INFO) ) ;
    //Log( "pPatchInfo: %016llX", pPatchInfo ) ;

    // Assign The Present() addess within SystemCall
    pPatchInfo->SystemCall = (BYTE*)VTable[ PR ] ;  // This is Present() within directx 9 sdk
    //Log( "pPatchInfo->SystemCall: %016llX", pPatchInfo->SystemCall ) ;

    // Define Signature & Mask For Present()
    pPatchInfo->SignatureSize = 0xF ;
    memcpy( pPatchInfo->Signature, "\xE9\x00\x00\x00\x00\x58\x08\x00\x00\x68\x00\x00\x00\x00\x00", pPatchInfo->SignatureSize ) ;
    memcpy( pPatchInfo->SignatureMask, "x????xx??x?????", pPatchInfo->SignatureSize ) ;
    //Log( "pPatchInfo->SignatureSize; %016llX", &pPatchInfo->SignatureSize ) ;
    //Log( "pPatchInfo->Signature: %016llX",     pPatchInfo->Signature ) ;
    //Log( "pPatchInfo->SignatureMask: %016llX", pPatchInfo->SignatureMask ) ;

    // Setup Prologue Patch
    pPatchInfo->PrologPatchOffset = 0x0 ;
    pPatchInfo->SizePrologPatch = 0xF ;
    memcpy( pPatchInfo->PrologPatch, "\x48\xB8\xDE\xC0\xBE\xBA\xFE\xCA\xED\xFE\x50\xC3\x90\x90\x90", pPatchInfo->SizePrologPatch ) ;
    //Log( "pPatchInfo->PrologPatchOffset: %016llX", &pPatchInfo->PrologPatchOffset ) ;
    //Log( "pPatchInfo->SizePrologPatch: %016llX", &pPatchInfo->SizePrologPatch ) ;
    //Log( "pPatchInfo->PrologPatch: %016llX", pPatchInfo->PrologPatch ) ;

    // Assign Detour Functions - Prologue & Epilogue Assignment.
    pPatchInfo->PrologDetour = (BYTE*)Prolog_Present ;
    //Log( "pPatchInfo->PrologDetour %016llX", pPatchInfo->PrologDetour ) ;

    // Make Sure our System Call Region has the proper RWE permissions.
    DWORD old_protect ;
    if( VirtualProtect( pPatchInfo->SystemCall, pPatchInfo->SignatureSize, PAGE_EXECUTE_READWRITE, &old_protect ) )
    {
        // Verify Signature @ Function We Want To Hook
        if( VerifySignature( pPatchInfo->SignatureMask, pPatchInfo->Signature, pPatchInfo->SignatureSize, pPatchInfo->SystemCall ) )
        {
            // Get Prologues Existing Bytes From Function We Want To Hook
            memcpy( pPatchInfo->PrologOriginal, pPatchInfo->SystemCall, pPatchInfo->SignatureSize ) ;
            //Log( "pPatchInfo->PrologOriginal: %016llX", pPatchInfo->PrologOriginal ) ;

            // Assign our patches the proper addresses to our Detour Functions.
            // Prologue
            MakePatchLegit( pPatchInfo->PrologDetour, pPatchInfo->PrologPatch ) ;
            //Log( "pPatchInfo->PrologPatch After Fixup: %016llX", pPatchInfo->PrologPatch ) ;

            // Follow Steam Hook
            FixUpSteamHook( pPatchInfo ) ;

            // Prologue Hook Complete
            InsertDetour( pPatchInfo->SystemCall, pPatchInfo->PrologPatch, pPatchInfo->SizePrologPatch, pPatchInfo->PrologPatchOffset ) ;     /* Activate Hook */
            Log( "First Hook Complete" );

            FixUpGameOverlayHook( pPatchInfo ) ;

        } else
        {
            Log( "Verify Signature Failed" ) ;
        }
    } else
    {
        Log( "First HOOK Virtual Protect Failed" ) ;
    }



    //CritSec.lock() ;

    // Prologue Hook
    //InsertDetour( pPatchInfo->SystemCall, pPatchInfo->PrologPatch, pPatchInfo->SizePrologPatch, pPatchInfo->PrologPatchOffset ) ; /* Activate Hook */
    //Log( "First Hook Complete" ) ;

    //// Call Hook
    //InsertDetour( pPatchInfo->GameOverlayPatchCall, pPatchInfo->PatchCall, 0x6, 0 ) ; /* Activate Hook */
    //Log( "Second HOOK Complete" ) ;

    //CritSec.unlock() ;


    //pCanvas = &Canvas ;

    /* =========================================================================== */
    /* Clean-Up Related Information */
    /* =========================================================================== */
    //free( pPatchInfo ) ;
    //pPatchInfo = NULL ;

    return 0 ;

} // End Of StormThread1