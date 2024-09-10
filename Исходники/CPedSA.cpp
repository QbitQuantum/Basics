void CPedSA::Respawn(CVector * position, bool bCameraCut)
{
    CPed * pLocalPlayer = pGame->GetPools()->GetPedFromRef ( (DWORD)1 );

    if ( !bCameraCut )
    {
         // DISABLE call to CCamera__RestoreWithJumpCut when respawning
        MemSet ( (void*)0x4422EA, 0x90, 20 );
    }

    DEBUG_TRACE("void CPedSA::Respawn(CVector * position)");
    FLOAT fX = position->fX;
    FLOAT fY = position->fY;
    FLOAT fZ = position->fZ;
    FLOAT fUnk = 1.0f; 
    DWORD dwFunc = FUNC_RestorePlayerStuffDuringResurrection;
    DWORD dwThis = (DWORD)this->GetInterface();
    _asm
    {
        push    fUnk
        push    fZ
        push    fY
        push    fX
        push    dwThis
        call    dwFunc
        add     esp, 20
    }
#if 0   // Removed to see if it reduces crashes
    dwFunc = 0x441440; // CGameLogic::SortOutStreamingAndMemory
    fUnk = 10.0f;
    _asm
    {
        push    fUnk
        push    position
        call    dwFunc
        add     esp, 8
    }
#endif
    dwFunc = FUNC_RemoveGogglesModel;
    _asm
    {
        mov     ecx, dwThis
        call    dwFunc
    }

    if ( !bCameraCut )
    {
        // B9 28 F0 B6 00 E8 4C 9A 0C 00 B9 28 F0 B6 00 E8 B2 97 0C 00
        unsigned char szCode[] = {0xB9, 0x28, 0xF0, 0xB6, 0x00, 0xE8, 0x4C, 0x9A, 0x0C, 0x00, 0xB9, 0x28, 0xF0, 0xB6, 0x00, 0xE8, 0xB2, 0x97, 0x0C, 0x00} ;
        // RE-ENABLE call to CCamera__RestoreWithJumpCut when respawning
        MemCpy ( (void*)0x4422EA, szCode, 20 );
    }
    //OutputDebugString ( "Respawn!!!!" );
}