static BOOL DS_IsPresent(void)
{
	if(DirectSoundCreate(NULL,&pSoundCard,NULL)!=DS_OK)
		return 0;
	if (pSoundCard) {
		IDirectSound_Release(pSoundCard);
		pSoundCard = NULL;
	}
	return 1;
}