void GameMain_PassClient(SOCKET s, TABULACRYPT2 *tbc2)
{
	clientGamemain_t *cgm = ClientMgr_AddToGameMain(s);
	if( cgm == 0 )
		__debugbreak(); //No more free slot

	memcpy((void*)&cgm->tbc2, (void*)tbc2, sizeof(TABULACRYPT2));
}