void CBacnetUserConfig::OnBnClickedButtonUserOk()
{
	// TODO: Add your control notification handler code here
	char temp_buffer[255];
	int compare_ret = 0;
	CString temp_enter_original;
	CString first_pw;
	CString second_pw;
	CString temp_user_name;
	CString access_string;
	switch(ok_button_stage)
	{
	case stage_enter_original_password://检查原始密码是否正确;
		{
			//m_user_login_data.at(m_slected_item).password
			GetDlgItemTextW(IDC_EDIT_USER_NAME,temp_user_name);
			GetDlgItemTextW(IDC_EDIT_USER_PASSWORD,temp_enter_original);
			if(temp_user_name.IsEmpty())
			{
				MessageBox(_T("user name is empty"),_T("Warning"),MB_OK);
				return;
			}
			if(temp_user_name.GetLength()>=STR_USER_NAME_LENGTH)
			{
				MessageBox(_T("User name is too long!"),_T("Warning"),MB_OK);
				return;
			}
			if(temp_enter_original.IsEmpty())
			{
				MessageBox(_T("Password is empty"),_T("Warning"),MB_OK);
				return;
			}
			memset(temp_buffer,0,255);
			WideCharToMultiByte(CP_ACP,NULL,temp_enter_original.GetBuffer(),-1,temp_buffer,255,NULL,NULL);
			compare_ret = strcmp(temp_buffer,m_user_login_data.at(m_slected_item).password);
			if(compare_ret == 0)
			{
				ok_button_stage = stage_enter_new_password;
				Enable_Window_Stage(ENTER_NEW_PASSWORD);
			}
			else
			{
				SetDlgItemTextW(IDC_EDIT_USER_PASSWORD,_T(""));
				MessageBox(_T("Password error"),_T("Warning"),MB_OK);	
				GetDlgItem(IDC_EDIT_USER_PASSWORD)->SetFocus();
				return;
			}
		}
		break;
	case stage_enter_new_password:
		{
			GetDlgItemTextW(IDC_EDIT_USER_NEW_PASSWORD,first_pw);
			if(first_pw.IsEmpty())
			{
				MessageBox(_T("Password is empty"),_T("Warning"),MB_OK);
				return;
			}
			if(first_pw.GetLength()>=STR_USER_PASSWORD_LENGTH)
			{
				MessageBox(_T("Password too long!"),_T("Warning"),MB_OK);
				return;
			}
			ok_button_stage = stage_retype_password;
			Enable_Window_Stage(RETYPE_NEW_PASSWORD);
		}
		break;
	case  stage_retype_password:
		{
			GetDlgItemTextW(IDC_EDIT_USER_NEW_PASSWORD,first_pw);
			GetDlgItemTextW(IDC_EDIT_USER_RETYPE_PASSWORD,second_pw);
			GetDlgItemTextW(IDC_EDIT_USER_NAME,temp_user_name);
			GetDlgItemTextW(IDC_COMBO_ACCESS_LEVEL,access_string);
			
			if(second_pw.IsEmpty())
			{
				MessageBox(_T("Password is empty"),_T("Warning"),MB_OK);
				return;
			}
			if(second_pw.GetLength()>=STR_USER_PASSWORD_LENGTH)
			{
				MessageBox(_T("Password too long!"),_T("Warning"),MB_OK);
				return;
			}

			if(first_pw.CompareNoCase(second_pw) == 0)
			{
				if(temp_user_name.IsEmpty())
				{
					MessageBox(_T("user name is empty"),_T("Warning"),MB_OK);
					return;
				}
				memset(temp_buffer,0,255);
				WideCharToMultiByte(CP_ACP,NULL,temp_user_name.GetBuffer(),-1,temp_buffer,255,NULL,NULL);
				memcpy(m_user_login_data.at(m_slected_item).name,temp_buffer,STR_USER_NAME_LENGTH);

				if(access_string.CompareNoCase(_T("View only")) == 0 )
				{
					m_user_login_data.at(m_slected_item).access_level = 1;
				}
				else if(access_string.CompareNoCase(_T("Graphic Mode")) == 0)
				{
					m_user_login_data.at(m_slected_item).access_level = 3;
				}
				else if(access_string.CompareNoCase(_T("Routine Mode")) == 0)
				{
					m_user_login_data.at(m_slected_item).access_level = 4;
				}
				else
					m_user_login_data.at(m_slected_item).access_level = 2;
				//_T("View only"));
				//_T("Full access"));

				memset(temp_buffer,0,255);
				WideCharToMultiByte(CP_ACP,NULL,second_pw.GetBuffer(),-1,temp_buffer,255,NULL,NULL);
				memcpy(m_user_login_data.at(m_slected_item).password,temp_buffer,STR_USER_PASSWORD_LENGTH);

				//Post_Write_Message(g_bac_instance,WRITEUSER_T3000,m_slected_item,m_slected_item,sizeof(Str_userlogin_point),m_user_config_hwnd ,_T(""),m_slected_item,m_slected_item);
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
						temp_invoke_id = WritePrivateData(g_bac_instance,WRITEUSER_T3000,m_slected_item,m_slected_item);

						Sleep(SEND_COMMAND_DELAY_TIME);
					} while (g_invoke_id<0);
					if(send_status)
					{
						Sleep(1000);
						if(tsm_invoke_id_free(temp_invoke_id))
						{
							ok_button_stage = 0;
							PostMessage(WM_REFRESH_BAC_USER_NAME_LIST,NULL,NULL);
							Enable_Window_Stage(HIDE_ALL);
							MessageBox(_T("Operation success!"),_T("Information"),MB_OK);
							return;
						}
						else
							continue;
					}
				}



			}
			else
			{
				MessageBox(_T("Password is not the same!"),_T("Warning"),MB_OK);
				return;
			}
		}
		break;
	default:
		break;
	}
}