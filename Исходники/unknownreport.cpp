DWORD STDMETHODCALLTYPE CUnkownReport::Run()
{
    HRESULT hr = S_OK;
    HANDLE  hEvent[ 2 ] = { NULL, NULL };

    WaitForSingleObject( g_hThread, INFINITE );

    if ( !g_bInitFalg )
    {
        CRunTimeLog::WriteLog(WINMOD_LLVL_ERROR, L"[CUnkownReport] Load Engine Failed" );
        goto Exit0;
    }

    hr = CScanEngineProxy::Instance().BKEngCreateEngine( 
        __uuidof(Skylark::IBKEngUploader), 
        ( void** )&m_spiUploader 
        );
    if ( FAILED( hr ) )
    {
        CRunTimeLog::WriteLog(WINMOD_LLVL_ERROR, L"[CUnkownReport] Upload interface create failed" );
        goto Exit0;
    }

    hr = m_spiUploader->Initialize();
    if ( FAILED( hr ) )
    {
        CRunTimeLog::WriteLog(WINMOD_LLVL_ERROR, L"[CUnkownReport] Upload interface initialize failed" );
        goto Exit0;
    }


    CBkBackupProxy::Instance().BKBackupCreateObject( 
        __uuidof( Skylark::IBKFileBackupFinder ), 
        ( void** )&m_spiBakFinder 
        );

    //if (WAIT_TIMEOUT != ::WaitForSingleObject(m_hNotifyStop, UNKNOWN_REPORT_FIRST_WAIT))
    //    goto Exit0;
    hEvent[ 0 ] = m_hNotifyStop;
    hEvent[ 1 ] = m_hNotifyReport;

    if ( WAIT_OBJECT_0 == ::WaitForMultipleObjects( 2, hEvent, FALSE, UNKNOWN_REPORT_FIRST_WAIT ) )
    {
        goto Exit0;
    }

    //BOOL bAutoReport = FALSE;
    //CSvcSetting::Instance().GetAutoReport( bAutoReport );


    if (!m_spiUploader)
        goto Exit0;


    CRunTimeLog::WriteLog(WINMOD_LLVL_INFO, L"report thread start ok" );


    while( 1 )
    {
        CReportFile rfile;
        CAtlList<CReportFile>   *pReportList = NULL;

        if (WAIT_TIMEOUT != ::WaitForSingleObject(m_hNotifyStop, UNKNOWN_REPORT_NEXT_WAIT))
            goto Exit0;

        if ( !GetReportFile( rfile, &pReportList ) )
        {
            continue;
        }

        hr = S_OK;

        if ( ( rfile.m_nTrack & FILE_TRACK_QUARANTINE ) )
        {
            CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] report quarantine %s", rfile.m_strFilePath );

            if ( m_spiBackup == ( Skylark::IBKFileBackup* )NULL )
            {
                hr = CBkBackupProxy::Instance().BKBackupCreateObject(
                    __uuidof(Skylark::IBKFileBackup),
                    ( void** )&m_spiBackup);
            }
            if ( SUCCEEDED( hr ) )
            {
                Skylark::BKBAK_BACKUP_ID  backupID;
                Skylark::BKENG_INIT( &backupID );
                backupID.uBackupID = _wtoi64(rfile.m_strFilePath);


                Skylark::BKENG_UPLOAD_PARAM  uploadParam;
                Skylark::BKENG_INIT( &uploadParam );
                hr = m_spiBackup->UploadBackupFile(
                    &backupID,
                    m_spiUploader,
                    &uploadParam,
                    static_cast<Skylark::IBKProgress*>(this));
                if ( SUCCEEDED( hr ) )
                {
                    CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] succeeded to report quarantine %s", rfile.m_strFilePath );

                    // 备份文件不需要重扫
                    // 上传成功,从数据库删除
                    //m_reportFileDB.RemoveFileInfo(rfile);
                    rfile.m_nReportState = enumFileReported;
                    m_reportFileDB.AddFileInfo( rfile );
                }
                else
                {
                    CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] failed to report quarantine %s : 0x%x", rfile.m_strFilePath, hr );

                    // 上传不成功
					if ( AtlHresultFromWin32(ERROR_FILE_NOT_FOUND) == hr )
					{// 隔离区中已不存在
						m_reportFileDB.RemoveFileInfo( rfile );
					}
					else
					{
						// 因为已经入库,所以下次重试
						if ( rfile.m_nRetry < REPORT_MAX_RETRY_TIMES )
						{
							rfile.m_nRetry++;
							pReportList->AddTail( rfile );
						}
						else
						{
							rfile.m_nReportState = enumFileRetried;

							m_reportFileDB.AddFileInfo( rfile );
						}
					}
                }
            }
            else
            {
                CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] failed to create IBKFileBackup : 0x%x", hr );

                // 创建隔离组件不成功
                // 因为已经入库,所以下次重试
            }
        }
        else
        {
            CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] report file %s", rfile.m_strFilePath );


            BOOL bIsReportFile = (rfile.m_nTrack & FILE_TRACK_REPORT_NONPE);


            Skylark::BKENG_UPLOAD_PARAM  uploadParam;
            Skylark::BKENG_INIT( &uploadParam );
            uploadParam.bUploadNonPEFile = bIsReportFile;
            hr = m_spiUploader->Upload( 
                rfile.m_strFilePath, 
                static_cast<Skylark::IBKProgress*>(this), 
                &uploadParam);
            if ( SUCCEEDED( hr ) )
            {
                CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] succeeded to report file %s", rfile.m_strFilePath );
                WIN32_FILE_ATTRIBUTE_DATA   fdata;

                // 上传成功,更新数据库,用于重扫
                if ( GetFileAttributesEx( rfile.m_strFilePath, GetFileExInfoStandard, &fdata ) )
                {
                    rfile.SetCreateTime( fdata.ftLastWriteTime );
                    GetSystemTimeAsFileTime( &rfile.m_ReportTime );
                    rfile.m_nReportState = enumFileReported;

                    m_reportFileDB.AddFileInfo( rfile );
                }
            }
            else
            {
                CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] failed to report file %s : 0x%x", rfile.m_strFilePath, hr );

                // 上传不成功
                if ( WinMod::CWinPathApi::IsFileExisting( rfile.m_strFilePath ) )
                {
                    // 因为已经入库,所以下次重试
                    if ( rfile.m_nRetry < REPORT_MAX_RETRY_TIMES )
                    {
                        rfile.m_nRetry++;
                        pReportList->AddTail( rfile );
                    }
                    else
                    {
                        rfile.m_nReportState = enumFileRetried;

                        m_reportFileDB.AddFileInfo( rfile );
                    }
                }
                else
                {
                    m_reportFileDB.RemoveFileInfo( rfile );
                }
            }


            // 有隐患
            if (bIsReportFile)
                ::DeleteFile(rfile.m_strFilePath);
        }
    }


Exit0:

    if ( m_spiUploader )
    {
        m_spiUploader->Uninitialize();
        m_spiUploader.Release();
    }


    CRunTimeLog::WriteLog(WINMOD_LLVL_INFO, L"[CUnkownReport] report thread exit" );
    return 0;
}