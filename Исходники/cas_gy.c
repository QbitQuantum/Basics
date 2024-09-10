UINT8 gyca_addmail_one_to_ram(T_CAMailInfo *data)
{
	UINT8 i;
	UINT8 ret = 0xff;
	if(!MEMCMP(&premail, data, sizeof(T_CAMailInfo)))
		return 1;
	
	gyca_mutex_lock();
	ret = gyca_getmail_num_from_ram();
	if(GYCA_EMAIL_MAX_CNT == ret)
	{
		gyca_mutex_unlock();
		return 2;
	}
	i = ret ;
	//gyca_mutex_lock();
	flashbuf[i].flg = 1;
	flashbuf[i].status = 1;
	MEMCPY(&flashbuf[i].info, data, sizeof(T_CAMailInfo));
	gyca_write_enable_time = osal_get_tick();
	gyca_write_enable = TRUE;
	gyca_mutex_unlock();
	return 0;
}