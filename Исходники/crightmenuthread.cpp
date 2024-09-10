int CRightMenuThread::CreateAddLabelPrc()
{
#ifdef Q_OS_WIN
    HANDLE hPipe = NULL;
    SECURITY_ATTRIBUTES   sa;
    SECURITY_DESCRIPTOR   sd;
    sa.lpSecurityDescriptor = &sd;
    InitializeSecurityDescriptor((_SECURITY_DESCRIPTOR*)sa.lpSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl((_SECURITY_DESCRIPTOR*)sa.lpSecurityDescriptor ,1,NULL,0);
    while(1) {
            hPipe = CreateNamedPipeA(
                    ("\\\\.\\pipe\\SFPipe_AddLabel"),             // pipe name
                    PIPE_ACCESS_DUPLEX,       // read/write access
                    PIPE_TYPE_MESSAGE |       // message type pipe
                    PIPE_READMODE_MESSAGE |   // message-read mode
                    PIPE_WAIT,                // blocking mode
                    PIPE_UNLIMITED_INSTANCES, // max. instances
                    sizeof(FILE_OPER_COPYDATA),                  // output buffer size
                    sizeof(FILE_OPER_COPYDATA),                  // input buffer size
                    0,                        // client time-out
                    &sa);                    // default security attribute

            if (hPipe == INVALID_HANDLE_VALUE)
            {

                    return S_FALSE;
            }

            bool bConnected;
            BOOL fSuccess;
            DWORD cbBytesRead;



            if((bConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED)))
            {
                    fSuccess = ReadFile(
                            hPipe,        // handle to pipe
                            (char *)&g_fileOper,    // buffer to receive data
                            sizeof(FILE_OPER_COPYDATA), // size of buffer
                            &cbBytesRead, // number of bytes read
                            NULL);        // not overlapped I/O

                    if (! fSuccess)  {

                            break;
                    }
                    if (cbBytesRead == 0)
                    {
                            DisconnectNamedPipe(hPipe);
                            continue;
                    }

                    QString sfPideInfo = QString("SFPipe_AddLabel：接收消息：操作类型：%1，强标路径：%2，右键操作路径：%3，右键操作类型：%4").arg(g_fileOper.dwFileOperType).arg(g_fileOper.stDmData.szFilePath).arg(g_fileOper.stRightData.szFilePath).arg(g_fileOper.stRightData.dwOperType);
                    locallogInfo(sfPideInfo);

                    if(g_fileOper.dwFileOperType == 1)//文件强制加标
                    {
                       memset(&g_addLabel, 0, sizeof(g_addLabel));
                       memcpy(&g_addLabel, &g_fileOper.stDmData, sizeof(g_addLabel));

                       locallogInfo(g_addLabel.szFilePath);

                       char *szName = strrchr(g_addLabel.szFilePath, '\\');
                       if(szName != NULL)
                       {
                           memset(g_fileName, 0, sizeof(g_fileName));
                           strcpy(g_fileName, szName+1);
                       }
                       memset(g_filePath, 0, sizeof(g_filePath));
                       strcpy(g_filePath, g_addLabel.szFilePath);

                       g_labelType = 1;//添加标签
                       emit LabdlgByMain();



                    }
                    else if (g_fileOper.dwFileOperType == 2)//文件右击加标
                    {
                        memset(&g_rightLabel, 0, sizeof(g_rightLabel));
                        memcpy(&g_rightLabel, &g_fileOper.stRightData, sizeof(g_rightLabel));
                        locallogInfo(g_rightLabel.szFilePath);



                        if(g_rightLabel.dwOperType == 1)//添加标签
                        {
                            char *szName = strrchr(g_rightLabel.szFilePath, '\\');
                            if(szName != NULL)
                            {
                                memset(g_fileName, 0, sizeof(g_fileName));
                                strcpy(g_fileName, szName+1);
                            }

                            memset(g_filePath, 0, sizeof(g_filePath));
                            strcpy(g_filePath, g_rightLabel.szFilePath);

                            g_labelType = 1;//添加标签
                            emit LabdlgByMain();

                        }
                        else if(g_rightLabel.dwOperType == 2)//去除标签
                        {

                            emit RemoveLabel();
                        }
                        else if(g_rightLabel.dwOperType == 3)//显示标签
                        {

                        }
                        else if(g_rightLabel.dwOperType == 4)//修改标签
                        {
                            char *szName = strrchr(g_rightLabel.szFilePath, '\\');
                            if(szName != NULL)
                            {
                                memset(g_fileName, 0, sizeof(g_fileName));
                                strcpy(g_fileName, szName+1);
                            }

                            memset(g_filePath, 0, sizeof(g_filePath));
                            strcpy(g_filePath, g_rightLabel.szFilePath);

                            g_labelType = 2;//修改标签
                            emit LabdlgByMain();

                        }
                        else
                        {
                           locallogInfo("g_rightLabel.dwOperType no this type");
                        }
                    }
                    else if(g_fileOper.dwFileOperType == 3)//判断是否登录
                    {
                        if(g_isLogin == true)  //0:已登录 1：未登录
                            g_fileOper.dwState = 0;
                        else
                            g_fileOper.dwState = 1;

                    }
                    else
                    {
                         locallogInfo("ReadSFPide no this type");

                    }


                    DWORD cbWritten = sizeof(FILE_OPER_COPYDATA);
                    WriteFile(
                            hPipe,        // handle to pipe
                            &g_fileOper,      // buffer to write from
                            sizeof(FILE_OPER_COPYDATA), // number of bytes to write
                            &cbWritten,   // number of bytes written
                            NULL);
            }

    }
            return S_OK;
#else

            char szPideName[80] = "/usr/etc/SFPipe_AddLabel";
            int fdRlst;
            unlink(szPideName);
            fdRlst = mkfifo(szPideName, S_IRUSR|S_IWUSR|0777);

            if(fdRlst == -1)
                return 1;
            else
            {
                  memset(&g_addLabel, 0, sizeof(g_addLabel));
                 while(1)
                {


                   if(0 ==ReadSFPide(g_fileOper))
                   {

                       QString sfPideInfo = QString("SFPipe_AddLabel：接收消息：操作类型：%1，强标路径：%2，右键操作路径：%3，右键操作类型：%4").arg(g_fileOper.dwFileOperType).arg(g_fileOper.stDmData.szFilePath).arg(g_fileOper.stRightData.szFilePath).arg(g_fileOper.stRightData.dwOperType);
                       locallogInfo(sfPideInfo);
                       if(g_fileOper.dwFileOperType == 1)
                       {
                          memset(&g_addLabel, 0, sizeof(g_addLabel));
                          memcpy(&g_addLabel, &g_fileOper.stDmData, sizeof(g_addLabel));

                          locallogInfo(g_addLabel.szFilePath);


                          char *szName = strrchr(g_addLabel.szFilePath, '/');
                          if(szName != NULL)
                          {
                              memset(g_fileName, 0, sizeof(g_fileName));
                              strcpy(g_fileName, szName+1);
                          }
                          memset(g_filePath, 0, sizeof(g_filePath));
                          strcpy(g_filePath, g_addLabel.szFilePath);

                          g_labelType = 1;//添加标签
                          emit LabdlgByMain();
                       }
                       else if (g_fileOper.dwFileOperType == 2)
                       {
                           memset(&g_rightLabel, 0, sizeof(g_rightLabel));
                           memcpy(&g_rightLabel, &g_fileOper.stRightData, sizeof(g_rightLabel));
                           locallogInfo(g_rightLabel.szFilePath);



                           if(g_rightLabel.dwOperType == 1)
                           {
                               char *szName = strrchr(g_rightLabel.szFilePath, '/');
                               if(szName != NULL)
                               {
                                   memset(g_fileName, 0, sizeof(g_fileName));
                                   strcpy(g_fileName, szName+1);
                               }

                               memset(g_filePath, 0, sizeof(g_filePath));
                               strcpy(g_filePath, g_rightLabel.szFilePath);

                               g_labelType = 1;//添加标签
                               emit LabdlgByMain();

                           }
                           else if(g_rightLabel.dwOperType == 2)
                           {
                               emit RemoveLabel();

                           }
                           else if(g_rightLabel.dwOperType == 3)
                           {

                           }
                           else if(g_rightLabel.dwOperType == 4)//修改标签
                           {
                               char *szName = strrchr(g_rightLabel.szFilePath, '\\');
                               if(szName != NULL)
                               {
                                   memset(g_fileName, 0, sizeof(g_fileName));
                                   strcpy(g_fileName, szName+1);
                               }

                               memset(g_filePath, 0, sizeof(g_filePath));
                               strcpy(g_filePath, g_rightLabel.szFilePath);

                               g_labelType = 2;//修改标签
                               emit LabdlgByMain();

                           }
                           else
                           {
                              locallogInfo("g_rightLabel.dwOperType no this type");
                           }
                       }
                       else
                       {
                          locallogInfo("ReadSFPide no this type");

                       }
                    }
                }
             }
            return 0;
#endif

}