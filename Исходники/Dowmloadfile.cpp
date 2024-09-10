DWORD WINAPI   Dowmloadfile::DownLoadFileProcess(LPVOID lpVoid)
{
	Dowmloadfile *mparent = (Dowmloadfile *)lpVoid;
	int retry_time = 0;
	//int retry_send_
	char sendbuffer[1000];
	while(download_thread_flag)
	{
		
		switch(download_step)
		{
		case SEND_DOWNLOAD_COMMAND:
			{
				if(retry_time>10)
				{
					mparent->TCP_File_Socket.SetDownloadResults(DOWNLOAD_RESULTS_FAILED);
					download_step = THREAD_IDLE;
					continue;
				}
				retry_time ++;

				Download_Info temp_info;
				temp_info.HEAD_1 = 0x55;
				temp_info.HEAD_2 = 0xff;
				temp_info.length = sizeof(Download_Info) - 2;
				temp_info.commad = DOWNLOAD_FILE;
				temp_info.product_id = m_product_isp_auto_flash.product_class_id;
				temp_info.get_newest = 1;
				temp_info.file_type = 2;
				temp_info.softversion = 0;
				temp_info.CRC = 0xff;
				memset(sendbuffer,0,1000);
				memcpy(sendbuffer,&temp_info,sizeof(Download_Info));
				sendbuffer[sizeof(Download_Info) - 1] = Add_CRC(sendbuffer,sizeof(Download_Info));
				mparent->TCP_File_Socket.Send(sendbuffer,sizeof(Download_Info),0);
				for (int i=0;i<1000;i++)
				{
					if(download_step!= SEND_DOWNLOAD_COMMAND)
					{
						retry_time = 0;
						current_package = 1;
						break;
					}
					Sleep(1);
				}

				break;
			}
		case SEND_GET_MD5_VALUE:
			{
				if(retry_time>10)
				{
					mparent->TCP_File_Socket.SetDownloadResults(DOWNLOAD_RESULTS_FAILED);
					download_step = THREAD_IDLE;
					continue;
				}
				retry_time ++;

				Black_head_struct temp_info;
				temp_info.HEAD_1 = 0x55;
				temp_info.HEAD_2 = 0xff;
				temp_info.length = 4;
				temp_info.commad = GET_MD5_VALUE;
				memset(sendbuffer,0,1000);
				memcpy(sendbuffer,&temp_info,sizeof(temp_info));
				sendbuffer[5] = Add_CRC(sendbuffer,5);
				mparent->TCP_File_Socket.Send(sendbuffer,6,0);
				for (int i=0;i<1000;i++)
				{
					if(download_step!= SEND_GET_MD5_VALUE)
					{
						current_package = 1;
						retry_time = 0;
						break;
					}
					Sleep(1);
				}
			}
			break;
		case CHECK_MD5_VALUE:
			{
				CString ApplicationFolder;
				CString temp_file_path;
				CString file_name;
				GetModuleFileName(NULL, ApplicationFolder.GetBuffer(MAX_PATH), MAX_PATH);
				PathRemoveFileSpec(ApplicationFolder.GetBuffer(MAX_PATH));
				ApplicationFolder.ReleaseBuffer();
				temp_file_path = ApplicationFolder + _T("\\Database\\Firmware");
				MultiByteToWideChar( CP_ACP, 0, download_filename, (int)strlen((char *)download_filename)+1, file_name.GetBuffer(MAX_PATH), MAX_PATH );
				file_name.ReleaseBuffer();
				temp_file_path = temp_file_path + _T("\\") + file_name; 
				CFileFind findfirmwarefile;
				if(!findfirmwarefile.FindFile(temp_file_path))	//没有发现文件 就要服务器传过来;
				{
					::PostMessage(downloadfile_hwnd,WM_DOWNLOADFILE_MESSAGE,DOWNLOAD_NOT_FIND_LOCAL,NULL);
					download_step = START_SEND_WANT_PACKAGE;
				}
				else	//发现有一样的了就要比对MD5是否一致;
				{
					//CString remote_md5;
					//CString local_md5;
					//MultiByteToWideChar( CP_ACP, 0, receive_md5, (int)strlen((char *)receive_md5)+1, remote_md5.GetBuffer(MAX_PATH), MAX_PATH );
					//remote_md5.ReleaseBuffer();

					char locoal_char_md5[20];
					memcpy_s(locoal_char_md5,20, MD5(ifstream( temp_file_path )).digest(),20);
					int ret_value = memcmp(locoal_char_md5,receive_md5,16);
					//string local_string_md5 = MD5(ifstream( temp_file_path )).toString();
					//local_md5 = local_string_md5.c_str();
					if(ret_value == 0)	//MD5值一样就不用下载 直接结束;
					{
						::PostMessage(downloadfile_hwnd,WM_DOWNLOADFILE_MESSAGE,DOWNLOAD_LOCAL_EXSIT,NULL);
						//::PostMessage(downloadfile_hwnd,WM_DOWNLOADFILE_MESSAGE,DOWNLOAD_CLOSE_SOCKET,NULL);
						download_step = THREAD_IDLE;
					}
					else	// 不一致就要再次下载;
					{
						::PostMessage(downloadfile_hwnd,WM_DOWNLOADFILE_MESSAGE,DOWNLOAD_NOT_FIND_LOCAL,NULL);
						download_step = START_SEND_WANT_PACKAGE;
					}
				}
				
			}
			break;
		case START_SEND_WANT_PACKAGE:
			{
				if(retry_time>10)
				{
					mparent->TCP_File_Socket.SetDownloadResults(DOWNLOAD_RESULTS_FAILED);
					download_step = THREAD_IDLE;
					continue;
				}
				retry_time ++;

				File_Package_Struct temp_struct;
				temp_struct.HEAD_1 = 0x55;
				temp_struct.HEAD_2 = 0xff;
				temp_struct.length = sizeof(File_Package_Struct) - 2;
				temp_struct.commad = ACK_GET_FILE_PAGE;
				temp_struct.package_index = current_package;
				temp_struct.total_package = totalpackage;
				temp_struct.CRC = 0;
				memset(sendbuffer,0,1000);
				memcpy(sendbuffer,&temp_struct,sizeof(File_Package_Struct));
				sendbuffer[sizeof(File_Package_Struct) - 1] = Add_CRC(sendbuffer,sizeof(File_Package_Struct));
				mparent->TCP_File_Socket.Send(sendbuffer,sizeof(File_Package_Struct),0);
				for (int i=0;i<1000;i++)
				{
					if(download_step!= START_SEND_WANT_PACKAGE)
					{
						int npersent = (current_package * 100) / totalpackage;
						retry_time = 0;
						::PostMessage(downloadfile_hwnd,WM_DOWNLOADFILE_MESSAGE,DOWNLOAD_PERSENT,npersent);
						break;
					}
					Sleep(1);
				}
				break;
			}
		case RECEIVE_WANTED_PACKAGE:
			{
				download_step = START_SEND_WANT_PACKAGE;

				break;
			}
		case RECEIVE_COMPLET:
			{


				CString file_name;
				MultiByteToWideChar( CP_ACP, 0, download_filename, (int)strlen((char *)download_filename)+1, file_name.GetBuffer(MAX_PATH), MAX_PATH );
				file_name.ReleaseBuffer();
				CString ApplicationFolder;
				download_thread_flag = true;
				GetModuleFileName(NULL, ApplicationFolder.GetBuffer(MAX_PATH), MAX_PATH);
				PathRemoveFileSpec(ApplicationFolder.GetBuffer(MAX_PATH));
				ApplicationFolder.ReleaseBuffer();
				Folder_Path = ApplicationFolder + _T("\\Database\\Firmware");

				Folder_Path = Folder_Path + _T("\\") + file_name; 
				HEX_BIN_FILE_PATH = Folder_Path;
				HANDLE hFile;
				hFile=CreateFile(Folder_Path,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
				DWORD dWrites;
				WriteFile(hFile,receivefile_buffer,total_file_length,&dWrites,NULL);
				CloseHandle(hFile);  




				if(receivefile_buffer)
				{
					delete receivefile_buffer;
					receivefile_buffer = NULL;
					total_file_length = 0;	//开辟的内存空间大小;
				}
				download_step = THREAD_IDLE;

				char locoal_char_md5[20];
				memcpy_s(locoal_char_md5,20, MD5(ifstream( HEX_BIN_FILE_PATH )).digest(),20);
				int ret_value = memcmp(locoal_char_md5,receive_md5,16);
				if(ret_value != 0)
				{
					::PostMessage(downloadfile_hwnd,WM_DOWNLOADFILE_MESSAGE,RETURN_ERROR,DOWNLOAD_MD5_FAILED);
					mparent->TCP_File_Socket.SetDownloadResults(DOWNLOAD_RESULTS_FAILED);
				}
				else
				{
					::PostMessage(downloadfile_hwnd,WM_DOWNLOADFILE_MESSAGE,RETURN_ERROR,DOWNLOAD_MD5_CHECK_PASS);
					mparent->TCP_File_Socket.SetDownloadResults(DOWNLOAD_RESULTS_PASS);
					
				}

				::PostMessage(downloadfile_hwnd,WM_DOWNLOADFILE_MESSAGE,DOWNLOAD_FINISHED,NULL);
				break;
			}
		case THREAD_IDLE:
			{
				//mparent->TCP_File_Socket.ShutDown();
				//mparent->TCP_File_Socket.Close();
				::PostMessage(downloadfile_hwnd,WM_DOWNLOADFILE_MESSAGE,DOWNLOAD_CLOSE_SOCKET,NULL);
				Downloadfile_Thread = NULL;
				retry_time = 0;
				Sleep(1000);
				return 0;
			}
			break;
		}
		Sleep(1);
	}
	return 0;
}