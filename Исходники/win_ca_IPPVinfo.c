INT32 IPPVinfo_got_info()
{
	UINT16 ret;
	UINT16 total_num = CDCA_MAXNUM_IPPVP;
	SCDCAIppvInfo  total_program_info[CDCA_MAXNUM_IPPVP];
	
#if 1	
	MEMSET(total_program_info, 0, sizeof(total_program_info));
	ret = CDCASTB_GetIPPVProgram(current_operator_ID, total_program_info, &total_num);
	if (CDCA_RC_CARD_INVALID== ret)
	{
		win_popup_msg(NULL, NULL, RS_CAERR_NOSMC);
		return 0;
	}
	else if (CDCA_RC_DATA_NOT_FIND == ret)
	{
		win_popup_msg(NULL, NULL, RS_CAERR_DATA_NOT_FOUND);
		return 0;	
	}
	else if (CDCA_RC_DATASPACE_SMALL == ret)
	{
		win_popup_msg(NULL, NULL, RS_CAERR_BUFFER_SMALL);
		return 0;
	}
	else if (CDCA_RC_OK == ret)
	{
		//success, sort the IPPV prog info by Select Sorting Method
		UINT32 i, j, k;
		SCDCAIppvInfo tmp;

		for (i=0; i<total_num; i++)
		{
			k = i;
			for (j=i+1; j<total_num; j++)
			{
				/*if ((total_program_info[j].m_bySlotID < total_program_info[k].m_bySlotID)
					||((total_program_info[j].m_bySlotID == total_program_info[k].m_bySlotID) 
						&&(total_program_info[j].m_dwProductID<total_program_info[k].m_dwProductID)))*/
				if (total_program_info[j].m_dwProductID<total_program_info[k].m_dwProductID)
					k = j;
			}
			if (k != i)
			{
				MEMCPY(&tmp, &total_program_info[i], sizeof(SCDCAIppvInfo));
				MEMCPY(&total_program_info[i], &total_program_info[k], sizeof(SCDCAIppvInfo));
				MEMCPY(&total_program_info[k], &tmp, sizeof(SCDCAIppvInfo));
			}
		}
		//just display the viewed records
		MEMSET(IPPV_program_info, 0, sizeof(IPPV_program_info));
		j= 0;
		for(i=0; i<total_num; i++)
		{
			if (CDCA_IPPVSTATUS_VIEWED == total_program_info[i].m_byBookEdFlag) //viewed
			{
				MEMCPY(&IPPV_program_info[j], &total_program_info[i], sizeof(SCDCAIppvInfo));
				j++;
			}
		}
		total_IPPV_number = j;
	}
	else
	{
		win_popup_msg(NULL, NULL, RS_CAERR_UNKNOWN);
		return 0;
	}
#else // for self -testing 
	UINT32 i, j, k;
	SCDCAIppvInfo tmp;
	total_num = 201;

	MEMSET(total_program_info, 0, sizeof(total_program_info));
	for (k=0;k<total_num;k++)
	{
		i = total_num - k;
		total_program_info[i].m_dwProductID = 1200000290+i;
		total_program_info[i].m_bCanTape = i%2;
		total_program_info[i].m_byBookEdFlag = (i%3) +1;
		total_program_info[i].m_bySlotID = i%5;
		total_program_info[i].m_wPrice = i*3;
	}


		for (i=0; i<total_num; i++)
		{
			k = i;
			for (j=i+1; j<total_num; j++)
			{
				/*if ((total_program_info[j].m_bySlotID < total_program_info[k].m_bySlotID)
					||((total_program_info[j].m_bySlotID == total_program_info[k].m_bySlotID) 
						&&(total_program_info[j].m_dwProductID<total_program_info[k].m_dwProductID)))*/
				if (total_program_info[j].m_dwProductID<total_program_info[k].m_dwProductID)
					k = j;
			}
			if (k != i)
			{
				MEMCPY(&tmp, &total_program_info[i], sizeof(SCDCAIppvInfo));
				MEMCPY(&total_program_info[i], &total_program_info[k], sizeof(SCDCAIppvInfo));
				MEMCPY(&total_program_info[k], &tmp, sizeof(SCDCAIppvInfo));
			}
		}
		//just display the viewed records
		MEMSET(IPPV_program_info, 0, sizeof(IPPV_program_info));
		j= 0;
		for(i=0; i<total_num; i++)
		{
			if (CDCA_IPPVSTATUS_VIEWED == total_program_info[i].m_byBookEdFlag) //viewed
			{
				MEMCPY(&IPPV_program_info[j], &total_program_info[i], sizeof(SCDCAIppvInfo));
				j++;
			}
		}
		total_IPPV_number = j;
#endif	
	return 1;

}