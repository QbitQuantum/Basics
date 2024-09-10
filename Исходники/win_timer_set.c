INT32 insert_timer(TYPE_TIMER type,TIMER_SET_CONTENT  *t_insert, UINT32 pos)
{
	SYSTEM_DATA * sys_data = sys_data_get();
	TIMER_SET_CONTENT * tmp = NULL;
	UINT32 highpos =0;
	INT32 ret=0;
	
	date_time insert,other;
	
	insert.year = t_insert->wakeup_year;
	insert.month = t_insert->wakeup_month;
	insert.day = t_insert->wakeup_day;

	
	
	if(type == TIMER_TYPE_EPG)
	{
		tmp= &sys_data->timer_set.TimerContent[0];
		highpos = MAX_EPG_TIMER_NUM;
	}
	else if(type ==TIMER_TYPE_NVOD)
	{
		tmp= &sys_data->timer_set.TimerContent[32];
		highpos = MAX_NVOD_TIMER_NUM;
	}

	UINT32 idx = 0;
	
	if(pos>=highpos)
	{
		show_pop_up_info(RS_BOOK_FULL);
		return !SUCCESS;
	}

	for(idx =0; idx<pos;idx++)
	{
		other.year = tmp[idx].wakeup_year;
		other.month = tmp[idx].wakeup_month;
		other.day = tmp[idx].wakeup_day;
		
		ret = api_compare_day(&other,&insert);

		if(ret > 0)
			break;
		else if(ret ==0)
		{
			if(t_insert->wakeup_time < tmp[idx].wakeup_time)
				break;	
		}
	}
	
	if(idx==pos)
	{
		MEMCPY(&tmp[pos],t_insert,sizeof(TIMER_SET_CONTENT));
		return SUCCESS;
	}
	else
	{
		MEMMOVE(&tmp[idx+1],&tmp[idx],((UINT32)&tmp[pos]-(UINT32)&tmp[idx]));
		MEMCPY(&tmp[idx],t_insert,sizeof(TIMER_SET_CONTENT));
		return SUCCESS;
	}
}