void BacnetRange::Timer2_handle()
{
	int sel_value;
	CString temp_value;
	SetDlgItemTextW(IDC_STATIC_RANGE_UNITE_SHOW,_T(""));
	GetDlgItemTextW(IDC_EDIT_RANGE_SELECT,temp_value);
	sel_value = _wtoi(temp_value);

	if((bac_ranges_type == VARIABLE_RANGE_ANALOG_TYPE) || 
		(initial_dialog == 1))
	{
		if(sel_value <= 30)
		{
			bac_ranges_type = VARIABLE_RANGE_DIGITAL_TYPE;
			for (int i=IDC_RADIO1;i<=IDC_RADIO34;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			if(sel_value<=11)
			{
				m_digital_select = sel_value;
				CRect c4;
				GetDlgItem(IDC_RADIO35 + m_digital_select)->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);
				for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				((CButton *)GetDlgItem(IDC_RADIO35 + m_digital_select))->SetCheck(true);
			}
			else if((sel_value>11) && (sel_value <=22))
			{
				m_digital_select = sel_value - 11;
				CRect c4;
				GetDlgItem(IDC_RADIO35 + m_digital_select)->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);

				for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				((CButton *)GetDlgItem(IDC_RADIO35 + m_digital_select))->SetCheck(true);
			}
			else
			{
				m_digital_select = sel_value - 11;
				CRect c4;
				GetDlgItem(IDC_RADIO73 + sel_value - 23 )->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);
				for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				((CButton *)GetDlgItem(IDC_RADIO73 + sel_value - 23))->SetCheck(true);
			}
		}
		else if(sel_value <= 63)
		{
			bac_ranges_type = VARIABLE_RANGE_ANALOG_TYPE;
			for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			m_analog_select = sel_value - 30 ;
			CRect c4;
			GetDlgItem(IDC_RADIO1 + m_analog_select )->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
			ScreenToClient(c4);  
			m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
			m_rang_pic.Invalidate(TRUE);

			for (int i=IDC_RADIO1;i<=IDC_RADIO34;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			((CButton *)GetDlgItem(IDC_RADIO1 + m_analog_select))->SetCheck(true);
		}
		else
		{
			MessageBox(_T("Out of range"));
			SetDlgItemTextW(IDC_EDIT_RANGE_SELECT,_T(""));
		}
	}
	else if((bac_ranges_type == OUTPUT_RANGE_ANALOG_TYPE) || 	(initial_dialog == 3))
	{
		if(sel_value <= 30)
		{
			bac_ranges_type = OUTPUT_RANGE_ANALOG_TYPE;
			for (int i=IDC_RADIO47;i<=IDC_RADIO53;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			m_output_Analog_select = 0;
			if(sel_value<=11)
			{
				m_digital_select = sel_value;
				CRect c4;
				GetDlgItem(IDC_RADIO35 + m_digital_select)->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);

				for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				((CButton *)GetDlgItem(IDC_RADIO35 + m_digital_select))->SetCheck(true);


			}
			else if((sel_value>11) && (sel_value <=22))
			{
				m_digital_select = sel_value - 11;
				CRect c4;
				GetDlgItem(IDC_RADIO35 + m_digital_select)->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);

				for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				((CButton *)GetDlgItem(IDC_RADIO35 + m_digital_select))->SetCheck(true);
			}
			else
			{
				m_digital_select = sel_value - 11;
				CRect c4;
				GetDlgItem(IDC_RADIO73 + sel_value - 23 )->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);

				for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				((CButton *)GetDlgItem(IDC_RADIO73 + sel_value - 23))->SetCheck(true);
			}
		}
		else if(sel_value <= 36)
		{
			bac_ranges_type = OUTPUT_RANGE_ANALOG_TYPE;
			for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			m_output_Analog_select = sel_value - 30 ;
			CRect c4;
			GetDlgItem(IDC_RADIO47 + m_output_Analog_select )->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
			ScreenToClient(c4);  
			m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
			m_rang_pic.Invalidate(TRUE);

			for (int i=IDC_RADIO47;i<=IDC_RADIO53;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			((CButton *)GetDlgItem(IDC_RADIO47 + m_output_Analog_select))->SetCheck(true);
		}
		else
		{
			MessageBox(_T("Out of range"));
			SetDlgItemTextW(IDC_EDIT_RANGE_SELECT,_T(""));
		}
	}
	else if((bac_ranges_type == INPUT_RANGE_ANALOG_TYPE) || 	(initial_dialog == 2))
	{
		if(sel_value <= 30)
		{
			bac_ranges_type = INPUT_RANGE_DIGITAL_TYPE;
			for (int i=IDC_RADIO54;i<=IDC_RADIO72;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			((CButton *)GetDlgItem(IDC_RADIO81))->SetCheck(false);
			m_input_Analog_select = 0;
			if(sel_value<=11)
			{
				m_digital_select = sel_value;
				CRect c4;
				GetDlgItem(IDC_RADIO35 + m_digital_select)->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);
				for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				((CButton *)GetDlgItem(IDC_RADIO35 + m_digital_select))->SetCheck(true);
			}
			else if((sel_value>11) && (sel_value <=22))
			{
				m_digital_select = sel_value - 11;
				CRect c4;
				GetDlgItem(IDC_RADIO35 + m_digital_select)->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);
				for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				((CButton *)GetDlgItem(IDC_RADIO35 + m_digital_select))->SetCheck(true);
			}
			else
			{
				m_digital_select = sel_value - 11;
				CRect c4;
				GetDlgItem(IDC_RADIO73 + sel_value - 23 )->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);

				for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
				{
					((CButton *)GetDlgItem(i))->SetCheck(false);
				}
				((CButton *)GetDlgItem(IDC_RADIO73 + sel_value - 23))->SetCheck(true);

			}
		}
		else if(sel_value <= 49)
		{
			bac_ranges_type = INPUT_RANGE_ANALOG_TYPE;
			for (int i=IDC_RADIO35;i<=IDC_RADIO46;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			for (int i=IDC_RADIO73;i<=IDC_RADIO80;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			m_input_Analog_select = sel_value - 30 ;

			if(sel_value == 49)
			{
				CRect c4;
				GetDlgItem(IDC_RADIO81)->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);
			}
			else
			{
				CRect c4;
				GetDlgItem(IDC_RADIO54 + m_input_Analog_select )->GetWindowRect(c4);   //获取控件的位置 ，饼调整位置;
				ScreenToClient(c4);  
				m_rang_pic.SetWindowPos(NULL,c4.left - 40,c4.top - 4,0,0,SWP_NOZORDER|SWP_NOSIZE);
				m_rang_pic.Invalidate(TRUE);
			}


			for (int i=IDC_RADIO54;i<=IDC_RADIO72;i++)
			{
				((CButton *)GetDlgItem(i))->SetCheck(false);
			}
			((CButton *)GetDlgItem(IDC_RADIO81))->SetCheck(false);
			if(sel_value == 49)
			{
				((CButton *)GetDlgItem(IDC_RADIO81))->SetCheck(true);
			}
			else
			{
			((CButton *)GetDlgItem(IDC_RADIO54 + m_input_Analog_select))->SetCheck(true);
			}

		}
		else
		{
			MessageBox(_T("Out of range"));
			SetDlgItemTextW(IDC_EDIT_RANGE_SELECT,_T(""));
		}
	}
}