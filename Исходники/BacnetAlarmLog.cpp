LRESULT CBacnetAlarmLog::Fresh_Alarmlog_List(WPARAM wParam,LPARAM lParam)
{
	bac_show_alarm_window = 0;
	for (int i=0;i<(int)m_alarmlog_data.size();i++)
	{
		bac_show_alarm_window = m_alarmlog_data.at(i).alarm || bac_show_alarm_window;
	}
	int Fresh_Item;
	int isFreshOne = (int)lParam;
	if(isFreshOne == REFRESH_ON_ITEM)
	{
		Fresh_Item = (int)wParam;
	}
	else
	{
		if(m_alarmlog_list.IsDataNewer((char *)&m_alarmlog_data.at(0),sizeof(Alarm_point) * BAC_ALARMLOG_COUNT))
		{
			//避免list 刷新时闪烁;在没有数据变动的情况下不刷新List;
			m_alarmlog_list.SetListData((char *)&m_alarmlog_data.at(0),sizeof(Alarm_point) * BAC_ALARMLOG_COUNT);
		}
		//else
		//{
		//	return 0;
		//}
	}


	for (int i=0;i<(int)m_alarmlog_data.size();i++)
	{
		if(isFreshOne)
		{
			i = Fresh_Item;
		}
		CString temp_item;
		CString temp_message;
		CString temp_panel;
		CString temp_time;

		if(m_alarmlog_data.at(i).alarm == 1)
		{
			temp_item.Format(_T("%d"),i+1);
			temp_panel.Format(_T("%d"),(unsigned char)m_alarmlog_data.at(i).alarm_panel);
			MultiByteToWideChar( CP_ACP, 0, (char *)m_alarmlog_data.at(i).alarm_message, (int)strlen((char *)m_alarmlog_data.at(i).alarm_message)+1, 
				temp_message.GetBuffer(MAX_PATH), MAX_PATH );
			temp_message.ReleaseBuffer();



			time_t tempalarm_time ;
			tempalarm_time = m_alarmlog_data.at(i).alarm_time;
			CTime time_alarmtime;
			time_alarmtime = tempalarm_time;
			temp_time = time_alarmtime.Format("%y/%m/%d %H:%M:%S");

		}
		else
		{
			temp_time.Empty();
			temp_panel.Empty();
			temp_message.Empty();
			temp_item.Empty();
			m_alarmlog_list.SetItemText(i,ALARMLOG_DEL,_T(""));
		}



		m_alarmlog_list.SetItemText(i,ALARMLOG_NUM,temp_item);
		m_alarmlog_list.SetItemText(i,ALARMLOG_PANEL,temp_panel);
		m_alarmlog_list.SetItemText(i,ALARMLOG_MESSAGE,temp_message);
		m_alarmlog_list.SetItemText(i,ALARMLOG_TIME,temp_time);

		if(m_alarmlog_data.at(i).alarm == 1)
		{
			if(m_alarmlog_data.at(i).ddelete == 0)
			{
				m_alarmlog_list.SetItemText(i,ALARMLOG_DEL,Yes_No[0]);
			}
			else
			{
				m_alarmlog_list.SetItemText(i,ALARMLOG_DEL,Yes_No[1]);
			}
		}
		else
		{
			m_alarmlog_list.SetItemText(i,ALARMLOG_MESSAGE,_T(""));
			m_alarmlog_list.SetItemText(i,ALARMLOG_DEL,_T(""));
		}

		if(isFreshOne)
		{
			break;
		}
	}
	

	return 0;
}