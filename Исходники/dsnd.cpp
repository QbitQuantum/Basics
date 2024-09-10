INT16 m1sdr_IsThere(void)
{
    if(DS_OK == DirectSoundCreate(NULL, &lpDS, NULL)) 
    {
		IDirectSound_Release(lpDS);
		hw_present = 1;
		return(1);
    } 
    else
    {
		hw_present = 0;
    	return(0);
    }
}