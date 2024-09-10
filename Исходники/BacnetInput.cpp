LRESULT CBacnetInput::Fresh_Input_Item(WPARAM wParam,LPARAM lParam)
{
    int cmp_ret ;//compare if match it will 0;
    int Changed_Item = (int)wParam;
    int Changed_SubItem = (int)lParam;

    memcpy_s(&m_temp_Input_data[Changed_Item],sizeof(Str_in_point),&m_Input_data.at(Changed_Item),sizeof(Str_in_point));

    CString temp_task_info;
    CString New_CString =  m_input_list.GetItemText(Changed_Item,Changed_SubItem);
    CString cstemp_value;
    if(Changed_SubItem == INPUT_LABLE)
    {
        CString cs_temp = m_input_list.GetItemText(Changed_Item,Changed_SubItem);
        if(cs_temp.GetLength()>= STR_IN_LABEL)	//长度不能大于结构体定义的长度;
        {
            MessageBox(_T("Length can not higher than 8"),_T("Warning"));
            PostMessage(WM_REFRESH_BAC_INPUT_LIST,NULL,NULL);
            return 0;
        }
        char cTemp1[255];
        memset(cTemp1,0,255);
        WideCharToMultiByte( CP_ACP, 0, cs_temp.GetBuffer(), -1, cTemp1, 255, NULL, NULL );
        memcpy_s(m_Input_data.at(Changed_Item).label,STR_IN_LABEL,cTemp1,STR_IN_LABEL);
    }

    if(Changed_SubItem == INPUT_FULL_LABLE)
    {
        CString cs_temp = m_input_list.GetItemText(Changed_Item,Changed_SubItem);
        if(cs_temp.GetLength()>= STR_IN_DESCRIPTION_LENGTH)	//长度不能大于结构体定义的长度;
        {
            MessageBox(_T("Length can not higher than 20"),_T("Warning"));
            PostMessage(WM_REFRESH_BAC_INPUT_LIST,NULL,NULL);
            return 0;
        }

        char cTemp1[255];
        memset(cTemp1,0,255);
        WideCharToMultiByte( CP_ACP, 0, cs_temp.GetBuffer(), -1, cTemp1, 255, NULL, NULL );
        memcpy_s(m_Input_data.at(Changed_Item).description,STR_IN_DESCRIPTION_LENGTH,cTemp1,STR_IN_DESCRIPTION_LENGTH);
    }


    if(Changed_SubItem == INPUT_AUTO_MANUAL)
    {
        CString temp_cs = m_input_list.GetItemText(Changed_Item,Changed_SubItem);
        if(temp_cs.CompareNoCase(_T("Auto"))==0)
        {
            m_input_list.SetCellEnabled(Changed_Item,INPUT_VALUE,0);
            m_Input_data.at(Changed_Item).auto_manual = BAC_AUTO ;
        }
        else
        {
            m_input_list.SetCellEnabled(Changed_Item,INPUT_VALUE,1);
            m_Input_data.at(Changed_Item).auto_manual = BAC_MANUAL ;
        }
    }

    if(Changed_SubItem == INPUT_VALUE)
    {
        CString temp_cs = m_input_list.GetItemText(Changed_Item,Changed_SubItem);

        int temp_int = (int)(_wtof(temp_cs) * 1000);
        //int temp_int = _wtoi(temp_cs);
        m_Input_data.at(Changed_Item).value = temp_int;
    }

    if(Changed_SubItem == INPUT_RANGE)
    {
        CString temp_cs = m_input_list.GetItemText(Changed_Item,Changed_SubItem);
        BacnetRange dlg;
        if(temp_cs.CompareNoCase(Units_Type[UNITS_TYPE_ANALOG])==0)
        {
            bac_ranges_type = INPUT_RANGE_ANALOG_TYPE;
            dlg.DoModal();
            if(range_cancel)
            {
                PostMessage(WM_REFRESH_BAC_INPUT_LIST,Changed_Item,REFRESH_ON_ITEM);//这里调用 刷新线程重新刷新会方便一点;
                return 0;
            }
            m_Input_data.at(Changed_Item).digital_analog =  BAC_UNITS_ANALOG;
            m_Input_data.at(Changed_Item).range =  bac_range_number_choose;
            m_input_list.SetItemText(Changed_Item,INPUT_RANGE,Input_Analog_Units_Array[bac_range_number_choose]);
            m_input_list.SetItemText(Changed_Item,INPUT_UNITE,Input_List_Analog_Units[bac_range_number_choose]);

            cstemp_value.Format(_T("%d"),m_Input_data.at(Changed_Item).calibration);
            m_input_list.SetItemText(Changed_Item,INPUT_CAL,cstemp_value);


            m_input_list.SetCellEnabled(Changed_Item,INPUT_CAL,1);
            m_input_list.SetCellEnabled(Changed_Item,INPUT_UNITE,1);
            //m_input_list.SetItemText(Changed_Item,OUTPUT_100_PERSENT,_T("10"));
            //m_input_list.SetCellEnabled(Changed_Item,OUTPUT_100_PERSENT,1);

            CString cstemp_value;
            float temp_float_value;
            temp_float_value = ((float)m_Input_data.at(Changed_Item).value) / 1000;
            cstemp_value.Format(_T("%.2f"),temp_float_value);
            m_input_list.SetItemText(Changed_Item,INPUT_VALUE,cstemp_value);

            //cstemp_value.Format(_T("%d"),m_Input_data.at(Changed_Item).value);
            //m_input_list.SetItemText(Changed_Item,INPUT_VALUE,cstemp_value);
        }
        else if(temp_cs.CompareNoCase(Units_Type[UNITS_TYPE_DIGITAL])==0)
        {
            bac_range_number_choose = m_Input_data.at(Changed_Item).range;
            bac_ranges_type = INPUT_RANGE_DIGITAL_TYPE;
            dlg.DoModal();
            if(range_cancel)
            {
                PostMessage(WM_REFRESH_BAC_INPUT_LIST,Changed_Item,REFRESH_ON_ITEM);//这里调用 刷新线程重新刷新会方便一点;
                return 0;
            }
            m_Input_data.at(Changed_Item).digital_analog =  BAC_UNITS_DIGITAL;
            m_Input_data.at(Changed_Item).range =  bac_range_number_choose;
            //m_input_list.SetItemText(Changed_Item,INPUT_RANGE,INPUT_Digital_Units_Show[bac_range_number_choose]);

            m_input_list.SetItemText(Changed_Item,INPUT_CAL,_T(""));
            m_input_list.SetCellEnabled(Changed_Item,INPUT_CAL,0);
            m_input_list.SetItemText(Changed_Item,INPUT_UNITE,_T(""));
            m_input_list.SetCellEnabled(Changed_Item,INPUT_UNITE,0);

            CString temp1;
            CStringArray temparray;
            temp1 = Digital_Units_Array[bac_range_number_choose];//22 is the sizeof the array
            SplitCStringA(temparray,temp1,_T("/"));

            if(m_Input_data.at(Changed_Item).control == 1)
            {
                if((temparray.GetSize()==2)&&(!temparray.GetAt(1).IsEmpty()))
                {
                    m_input_list.SetItemText(Changed_Item,INPUT_VALUE,temparray.GetAt(1));
                }
            }
            else
            {
                if((temparray.GetSize()==2)&&(!temparray.GetAt(0).IsEmpty()))
                {
                    m_input_list.SetItemText(Changed_Item,INPUT_VALUE,temparray.GetAt(0));
                }
            }
            m_input_list.SetItemText(Changed_Item,INPUT_RANGE,temp1);


        }
        else if(temp_cs.CompareNoCase(Units_Type[UNITS_TYPE_CUSTOM])==0)
        {
            bac_ranges_type = OUTPUT_RANGE_CUSTOM_DIG_TYPE;
            //dlg.DoModal();
        }
        else
        {
            PostMessage(WM_REFRESH_BAC_INPUT_LIST,Changed_Item,REFRESH_ON_ITEM);//这里调用 刷新线程重新刷新会方便一点;
            //m_input_list.SetItemText(Changed_Item,INPUT_RANGE,temp_cs);
        }
    }


    //if(Changed_SubItem==INPUT_RANGE)
    //{
    //	CString temp_cs = m_input_list.GetItemText(Changed_Item,Changed_SubItem);
    //	if(temp_cs.CompareNoCase(_T("Not Used"))==0)
    //	{
    //		m_input_list.SetItemText(Changed_Item,INPUT_UNITE,Input_Unit[_unused]);
    //	}
    //	else if(temp_cs.CompareNoCase(_T("10K(-40->120)"))==0)
    //	{
    //		ListCtrlEx::CStrList strlist;
    //		strlist.clear();
    //		strlist.push_back(Input_Unit[degC]);
    //		//strlist.push_back(Input_Unit[degF]);
    //		m_input_list.SetCellStringList(Changed_Item, INPUT_UNITE, strlist);
    //		m_input_list.SetItemText(Changed_Item,INPUT_UNITE,Input_Unit[degC]);
    //	}
    //	else if(temp_cs.CompareNoCase(_T("I 4->20ma"))==0)
    //	{
    //		ListCtrlEx::CStrList strlist;
    //		strlist.clear();
    //		TRACE(Input_Unit[ma]);
    //		strlist.push_back(Input_Unit[ma]);
    //		m_input_list.SetCellStringList(Changed_Item, INPUT_UNITE, strlist);
    //		m_input_list.SetItemText(Changed_Item,INPUT_UNITE,Input_Unit[ma]);
    //	}
    //	else if(temp_cs.CompareNoCase(_T("V 0->10V"))==0)
    //	{
    //		ListCtrlEx::CStrList strlist;
    //		strlist.clear();
    //		TRACE(Input_Unit[Volts]);
    //		strlist.push_back(Input_Unit[Volts]);
    //		m_input_list.SetCellStringList(Changed_Item, INPUT_UNITE, strlist);
    //		m_input_list.SetItemText(Changed_Item,INPUT_UNITE,Input_Unit[Volts]);
    //	}
    //	else if(temp_cs.CompareNoCase(_T("V 0->5V"))==0)
    //	{
    //		ListCtrlEx::CStrList strlist;
    //		strlist.clear();
    //		TRACE(Input_Unit[Volts]);
    //		strlist.push_back(Input_Unit[Volts]);
    //		m_input_list.SetCellStringList(Changed_Item, INPUT_UNITE, strlist);
    //		m_input_list.SetItemText(Changed_Item,INPUT_UNITE,Input_Unit[Volts]);
    //	}
    //	else if(temp_cs.CompareNoCase(_T("V 0->24AC"))==0)
    //	{
    //		ListCtrlEx::CStrList strlist;
    //		strlist.clear();
    //		strlist.push_back(_T("ON/OFF"));
    //		m_input_list.SetCellStringList(Changed_Item, INPUT_UNITE, strlist);
    //		m_input_list.SetItemText(Changed_Item,INPUT_UNITE,_T("ON/OFF"));
    //	}
    //	else if(temp_cs.CompareNoCase(_T("TST Normal"))==0)
    //	{
    //		ListCtrlEx::CStrList strlist;
    //		strlist.clear();
    //		strlist.push_back(_T("ON/OFF"));
    //		m_input_list.SetCellStringList(Changed_Item, INPUT_UNITE, strlist);
    //		m_input_list.SetItemText(Changed_Item,INPUT_UNITE,_T("ON/OFF"));
    //	}
    //}

    if(Changed_SubItem==INPUT_CAL)
    {
        CString cs_temp=m_input_list.GetItemText(Changed_Item,INPUT_CAL);
        int cal_value = _wtoi(cs_temp);
        m_Input_data.at(Changed_Item).calibration = cal_value;
    }
    else if(Changed_SubItem==INPUT_FITLER)
    {
        CString cs_temp=m_input_list.GetItemText(Changed_Item,INPUT_FITLER);
        int  temp2 = _wtoi(cs_temp);
        m_Input_data.at(Changed_Item).filter = (int8_t)(log((double)temp2)/log((double)2));
    }
    else if(Changed_SubItem==INPUT_DECOM)
    {
        CString cs_temp = m_input_list.GetItemText(Changed_Item,INPUT_DECOM);
        int dec_index=-1;
        for (int m=0; m<(int)sizeof(Decom_Array)/sizeof(Decom_Array[0]); m++)
        {
            if(cs_temp.CompareNoCase(Decom_Array[m])==0)
            {
                dec_index = m;
                break;
            }
        }
        m_Input_data.at(Changed_Item).decom = dec_index;
    }

    cmp_ret = memcmp(&m_temp_Input_data[Changed_Item],&m_Input_data.at(Changed_Item),sizeof(Str_in_point));
    if(cmp_ret!=0)
    {
        m_input_list.SetItemBkColor(Changed_Item,Changed_SubItem,LIST_ITEM_CHANGED_BKCOLOR);
        temp_task_info.Format(_T("Write Input List Item%d .Changed to \"%s\" "),Changed_Item + 1,New_CString);
        Post_Write_Message(g_bac_instance,WRITEINPUT_T3000,Changed_Item,Changed_Item,sizeof(Str_in_point),m_input_dlg_hwnd ,temp_task_info,Changed_Item,Changed_SubItem);
    }
    //m_input_list.Invalidate();
    return 0;
}