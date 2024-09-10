void CBacnetVariable::OnNMClickListVariable(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	long lRow,lCol;
	m_variable_list.Set_Edit(true);
	DWORD dwPos=GetMessagePos();//Get which line is click by user.Set the check box, when user enter Insert it will jump to program dialog
	CPoint point( LOWORD(dwPos), HIWORD(dwPos));
	m_variable_list.ScreenToClient(&point);
	LVHITTESTINFO lvinfo;
	lvinfo.pt=point;
	lvinfo.flags=LVHT_ABOVE;
	int nItem=m_variable_list.SubItemHitTest(&lvinfo);

	lRow = lvinfo.iItem;
	lCol = lvinfo.iSubItem;


	if(lRow>m_variable_list.GetItemCount()) //如果点击区超过最大行号，则点击是无效的
		return;
	if(lRow<0)
		return;



	CString temp1;
	m_row = lRow;
	m_col = lCol;

	memcpy_s(&m_temp_variable_data[lRow],sizeof(Str_variable_point),&m_Variable_data.at(lRow),sizeof(Str_variable_point));
	CString New_CString;
	CString temp_task_info;
	if((lCol == VARIABLE_VALUE) &&(m_Variable_data.at(lRow).digital_analog == BAC_UNITS_DIGITAL ) && (m_Variable_data.at(lRow).auto_manual != BAC_AUTO))
	{
		
		
		CString temp1;
		CStringArray temparray;

		if((m_Variable_data.at(lRow).range < 23) &&(m_Variable_data.at(lRow).range !=0))
			temp1 = Digital_Units_Array[m_Variable_data.at(lRow).range];
		else if((m_Variable_data.at(lRow).range >=23) && (m_Variable_data.at(lRow).range <= 30))
		{
			if(receive_customer_unit)
				temp1 = temp_unit_no_index[m_Variable_data.at(lRow).range - 23];
			else
			{
				m_variable_list.Set_Edit(false);
				return;
			}
		}
		else
			return;
		SplitCStringA(temparray,temp1,_T("/"));



		if(m_Variable_data.at(lRow).control == 0)
		{
			m_Variable_data.at(lRow).control = 1;
			m_variable_list.SetItemText(lRow,VARIABLE_VALUE,temparray.GetAt(1));
			New_CString = temparray.GetAt(1);
		}
		else
		{
			m_Variable_data.at(lRow).control = 0;
			m_variable_list.SetItemText(lRow,VARIABLE_VALUE,temparray.GetAt(0));
			New_CString = temparray.GetAt(0);
		}
		m_variable_list.Set_Edit(false);

		temp_task_info.Format(_T("Write Variable List Item%d .Changed to \"%s\" "),lRow + 1,New_CString);
	}
	else if((lCol == VARIABLE_VALUE) &&(m_Variable_data.at(lRow).digital_analog == BAC_UNITS_ANALOG ) && (m_Variable_data.at(lRow).auto_manual == BAC_MANUAL) && (m_Variable_data.at(lRow).range == 20))
	{
		m_variable_list.Set_Edit(false);
		m_variable_time_picker.ShowWindow(SW_SHOW);
		CRect list_rect,win_rect;
		m_variable_list.GetWindowRect(list_rect);
		GetWindowRect(win_rect);
		CRect myrect;
		m_variable_list.GetSubItemRect(lRow,lCol,LVIR_BOUNDS,myrect);


		myrect.left = myrect.left + list_rect.left - win_rect.left  +2 ;
		myrect.right = myrect.right + list_rect.left - win_rect.left + 2;
		//myrect.top = myrect.top + 11;
		//myrect.bottom = myrect.bottom + 13;
		myrect.top = myrect.top + 24;
		myrect.bottom = myrect.bottom + 26;
		m_variable_time_picker.BringWindowToTop();
		m_variable_time_picker.MoveWindow(myrect);

		
		CString Temp_CString =  m_variable_list.GetItemText(lRow,lCol);

		CStringArray TEMPCS;
		int temp_hour,temp_minute;
		SplitCStringA(TEMPCS, Temp_CString, _T(":"));
		if((int)TEMPCS.GetSize() <2)
		{
			temp_hour = 0;
			temp_minute = 0;
			CTime TimeTemp(2014,1,1,temp_hour,temp_minute,0);
			m_variable_time_picker.SetFormat(_T("HH:mm"));
			m_variable_time_picker.SetTime(&TimeTemp);
			m_variable_time_picker.SetFocus();
		}
		else
		{
			temp_hour = _wtoi(TEMPCS.GetAt(0));
			temp_minute = _wtoi(TEMPCS.GetAt(1));
			CTime TimeTemp(2014,1,1,temp_hour,temp_minute,0);
			m_variable_time_picker.SetFormat(_T("HH:mm"));
			m_variable_time_picker.SetTime(&TimeTemp);
			m_variable_time_picker.SetFocus();
		}
		m_variable_list.SetItemText(lRow,lCol,_T(""));
		m_variable_time_picker.Invalidate();
		SetTimer(2,100,NULL);
	}
	else if(lCol == VARIABLE_VALUE)
	{
		if(m_Variable_data.at(lRow).auto_manual == BAC_AUTO)
		{
			m_variable_list.Set_Edit(false);
			return;
		}
	}
	else if(lCol == VARIABLE_AUTO_MANUAL)
	{
		if(m_Variable_data.at(lRow).auto_manual == 0)
		{
			m_Variable_data.at(lRow).auto_manual = 1;
			m_variable_list.SetItemText(lRow,VARIABLE_AUTO_MANUAL,_T("Manual"));
			//m_variable_list.SetCellEnabled(lRow,VARIABLE_VALUE,TRUE);
			New_CString = _T("Manual");
		}
		else
		{
			m_Variable_data.at(lRow).auto_manual = 0;
			m_variable_list.SetItemText(lRow,VARIABLE_AUTO_MANUAL,_T("Auto"));
			//m_variable_list.SetCellEnabled(lRow,VARIABLE_VALUE,FALSE);
			New_CString = _T("Auto");
		}
		temp_task_info.Format(_T("Write Variable List Item%d .Changed to \"%s\" "),lRow + 1,New_CString);
	}
	else if(lCol == VARIABLE_UNITE)
	{


		BacnetRange dlg;

		//点击产品的时候 需要读customer units，老的产品firmware 说不定没有 这些，所以不强迫要读到;
		if(!read_customer_unit)
		{

			int temp_invoke_id = -1;
			int send_status = true;
			int	resend_count = 0;
			for (int z=0;z<3;z++)
			{
				do 
				{
					resend_count ++;
					if(resend_count>5)
					{
						send_status = false;
						break;
					}
					temp_invoke_id =  GetPrivateData(
						g_bac_instance,
						READUNIT_T3000,
						0,
						BAC_CUSTOMER_UNITS_COUNT - 1,
						sizeof(Str_Units_element));		

					Sleep(SEND_COMMAND_DELAY_TIME);
				} while (g_invoke_id<0);
				if(send_status)
				{
					for (int z=0;z<1000;z++)
					{
						Sleep(1);
						if(tsm_invoke_id_free(temp_invoke_id))
						{
							read_customer_unit = true;
							break;
						}
						else
							continue;
					}

				}
				if(read_customer_unit)
					break;
			}

		}

		//CString temp_cs = m_variable_list.GetItemText(lRow,lCol);
		//if(temp_cs.CompareNoCase(Units_Type[UNITS_TYPE_ANALOG])==0)
		//{


		if(m_Variable_data.at(lRow).digital_analog == BAC_UNITS_ANALOG)
		{
			bac_ranges_type = VARIABLE_RANGE_ANALOG_TYPE;
			if(m_Variable_data.at(lRow).range > (sizeof(Variable_Analog_Units_Array) / sizeof(Variable_Analog_Units_Array[0])))
			{
				m_Variable_data.at(lRow).range = 0;
				bac_range_number_choose = 0;
			}
		}
		else
		{
			bac_ranges_type = VARIABLE_RANGE_DIGITAL_TYPE;
			if(m_Variable_data.at(lRow).range > 30)
			{
				m_Variable_data.at(lRow).range = 0;
				bac_range_number_choose = 0;
			}
		}


			initial_dialog = 1;
			bac_range_number_choose = m_Variable_data.at(lRow).range;
			//bac_ranges_type = VARIABLE_RANGE_ANALOG_TYPE;
			dlg.DoModal();
			if(range_cancel)
			{
				PostMessage(WM_REFRESH_BAC_VARIABLE_LIST,lRow,REFRESH_ON_ITEM);//这里调用 刷新线程重新刷新会方便一点;
				return ;
			}
			if(bac_range_number_choose == 0)	//如果选择的是 unused 就认为是analog 的unused;这样 能显示对应的value;
			{
				m_Variable_data.at(lRow).digital_analog =  BAC_UNITS_ANALOG;
				bac_ranges_type = VARIABLE_RANGE_ANALOG_TYPE;
			}

			if(bac_ranges_type == VARIABLE_RANGE_ANALOG_TYPE)
			{
				m_Variable_data.at(lRow).digital_analog = BAC_UNITS_ANALOG;
				m_Variable_data.at(lRow).range = bac_range_number_choose;
				m_variable_list.SetItemText(lRow,lCol,Variable_Analog_Units_Array[bac_range_number_choose]);



				if(m_Variable_data.at(lRow).range == 20)	//如果是时间;
				{
					char temp_char[50];
					int time_seconds = m_Variable_data.at(lRow).value / 1000;
					intervaltotext(temp_char,time_seconds,0,0);

					CString temp_11;
					MultiByteToWideChar( CP_ACP, 0, temp_char, strlen(temp_char) + 1, 
						temp_11.GetBuffer(MAX_PATH), MAX_PATH );
					temp_11.ReleaseBuffer();		
					m_variable_list.SetItemText(lRow,VARIABLE_VALUE,temp_11);

				}
				else
				{
					CString cstemp_value;
					float temp_float_value;
					temp_float_value = ((float)m_Variable_data.at(lRow).value) / 1000;
					cstemp_value.Format(_T("%.3f"),temp_float_value);
					m_variable_list.SetItemText(lRow,VARIABLE_VALUE,cstemp_value);

					/*				cstemp_value.Format(_T("%d"),m_Variable_data.at(Changed_Item).value);
					m_variable_list.SetItemText(Changed_Item,VARIABLE_VALUE,cstemp_value);*/	
				}
			}
			else if((bac_ranges_type == VARIABLE_RANGE_DIGITAL_TYPE) || (bac_ranges_type == INPUT_RANGE_DIGITAL_TYPE) || (bac_ranges_type == OUTPUT_RANGE_DIGITAL_TYPE))
			{
				m_Variable_data.at(lRow).digital_analog = BAC_UNITS_DIGITAL;
				m_Variable_data.at(lRow).range = bac_range_number_choose;


				CStringArray temparray;
				if((bac_range_number_choose >= 23) && (bac_range_number_choose <= 30))
				{
					//temp1.Format(_T("%s"), temp_unit_no_index[bac_range_number_choose - 23]);
					temp1 = temp_unit_no_index[bac_range_number_choose - 23];
				}
				else
					temp1 = Digital_Units_Array[bac_range_number_choose];//22 is the sizeof the array

				SplitCStringA(temparray,temp1,_T("/"));





				if(m_Variable_data.at(lRow).control == 1)
				{
					if((temparray.GetSize()==2)&&(!temparray.GetAt(1).IsEmpty()))
					{
						m_variable_list.SetItemText(lRow,VARIABLE_VALUE,temparray.GetAt(1));
					}
				}
				else
				{
					if((temparray.GetSize()==2)&&(!temparray.GetAt(0).IsEmpty()))
					{
						m_variable_list.SetItemText(lRow,VARIABLE_VALUE,temparray.GetAt(0));
					}			
				}
				m_variable_list.SetItemText(lRow,VARIABLE_UNITE,temp1);
			}
		
	
	}
	else
	{
		//m_variable_list.Set_Edit(false);
		return;
	}

	int cmp_ret = memcmp(&m_temp_variable_data[lRow],&m_Variable_data.at(lRow),sizeof(Str_variable_point));
	if(cmp_ret!=0)
	{
		m_variable_list.SetItemBkColor(lRow,lCol,LIST_ITEM_CHANGED_BKCOLOR);
		Post_Write_Message(g_bac_instance,WRITEVARIABLE_T3000,lRow,lRow,sizeof(Str_variable_point),m_variable_dlg_hwnd,temp_task_info,lRow,lCol);
	}
//	GetDlgItem(IDC_BUTTON_VARIABLE_APPLY)->SetFocus();
	*pResult = 0;
}