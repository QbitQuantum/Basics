void IBN_TimeAccess (u8 nParamsGet_u8,u8 CMD_u8,u32 Param_u32,u8 *String_pu8)
{
	struct tm      tm_st;
//	struct tm      tm_st1;

	u8             Time_u8[30];
	time_t now;

	if (0 == nParamsGet_u8)
	{
		CI_LocalPrintf ("Time functions\r\n");
		CI_LocalPrintf ("\r\n");
		CI_LocalPrintf ("0   Show time\r\n");
		CI_LocalPrintf ("1   Set time - HH:MM:SS\r\n");
    CI_LocalPrintf ("2   Set date - DD:MM:YY\r\n");
    CI_LocalPrintf ("3   Set time in sec\r\n");
    CI_LocalPrintf ("4   Write time to flash\r\n");
    CI_LocalPrintf ("5   Read time from flash\r\n");
		CI_LocalPrintf ("\r\n");
		return;
	}
	switch (CMD_u8)
	{
		case 0 :
			time (&now);
			CI_LocalPrintf ("Time %ld\r\n",now);
			ctime_r (&now,(char*)Time_u8);
			CI_LocalPrintf ("Time %s\r\n",Time_u8);
			break;
		case 1 :
			if (NULL == String_pu8)
			{
				break;
			}
			time (&now);
			localtime_r (&now,&tm_st);
			tm_st.tm_hour = atoi ((char*)&String_pu8[0]);
			tm_st.tm_min  = atoi ((char*)&String_pu8[3]);
			tm_st.tm_sec  = atoi ((char*)&String_pu8[6]);
			CI_LocalPrintf ("Set time to %2d:%02d:%02d\r\n",tm_st.tm_hour,tm_st.tm_min,tm_st.tm_sec);
			now = mktime (&tm_st);
			set_time (now);
			break;

		case 2 :
			if (NULL == String_pu8)
			{
				break;
			}
			time (&now);
			localtime_r (&now,&tm_st);
			tm_st.tm_mday = atoi ((char*)&String_pu8[0]);
			tm_st.tm_mon  = atoi ((char*)&String_pu8[3]) - 1;
			tm_st.tm_year = atoi ((char*)&String_pu8[6]);
			if (50 > tm_st.tm_year)
			{
				tm_st.tm_year += 100;
			}
			CI_LocalPrintf ("Set date to %2d.%02d.%04d\r\n",tm_st.tm_mday,tm_st.tm_mon+1,1900+tm_st.tm_year);
			now = mktime (&tm_st);
			set_time (now);
			break;
    case 3 :
      CI_LocalPrintf ("Set Time %ld\r\n",Param_u32);
      set_time (Param_u32);
      time (&now);
      CI_LocalPrintf ("Time %ld\r\n",now);
      ctime_r (&now,(char*)Time_u8);
      CI_LocalPrintf ("Time %s\r\n",Time_u8);
      break;
    case 4 :
      time (&now);
      CI_LocalPrintf ("Write time %ld -",now);
      ctime_r (&now,(char*)Time_u8);
      CI_LocalPrintf ("%s\r\n",Time_u8);
      WriteDatetime (now);
      break;
    case 5 :
      ReadDatetime (&now);
      CI_LocalPrintf ("Stored time %ld - ",now);
      ctime_r (&now,(char*)Time_u8);
      CI_LocalPrintf ("Time %s\r\n",Time_u8);
      break;

	}
}