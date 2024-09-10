/// <summary>
/// Process Kinect window menu commands
/// </summary>
/// <param name="commanId">ID of the menu item</param>
/// <param name="param">Parameter passed in along with the commmand ID</param>
/// <param name="previouslyChecked">Check status of menu item before command is issued</param>
void KinectSettings::ProcessMenuCommand(WORD commandId, WORD param, bool previouslyChecked)
{
	DWORD ExitCode;
	FaceTracker* pFaceTracker;
	InbedAPPs* pFallDetect;
	DepthInbedAPPs* pDepthInbedApps;
	LegRaisExcer* pLegRaisExer;
	HandRaisExcer* pHandRaisExer;
	
	m_pKinectWindow->GetFaceTraker(&pFaceTracker);
	m_pPrimaryView->GetFallDetect(&pFallDetect);
	m_pDepthStream->GetDepthInbedAPPs(&pDepthInbedApps);
	m_pPrimaryView->GetLegRaisExcer(&pLegRaisExer);
	m_pPrimaryView->GetHandRaisExcer(&pHandRaisExer);

    if (ID_COLORSTREAM_PAUSE == commandId)
    {
        // Pause color stream
        if (m_pColorStream)
        {
            m_pColorStream->PauseStream(!previouslyChecked);
        }
    }
    else if (ID_COLORSTREAM_RESOLUTION_START <= commandId && ID_COLORSTREAM_RESOLUTION_END >= commandId)
    {
        // Set color stream format and resolution
        if (!m_pColorStream)
        {
            return;
        }

        switch (commandId)
        {
        case ID_RESOLUTION_RGBRESOLUTION640X480FPS30:
            m_pColorStream->SetImageType(NUI_IMAGE_TYPE_COLOR);
            m_pColorStream->SetImageResolution(NUI_IMAGE_RESOLUTION_640x480);
            break;

        case ID_RESOLUTION_RGBRESOLUTION1280X960FPS12:
            m_pColorStream->SetImageType(NUI_IMAGE_TYPE_COLOR);
            m_pColorStream->SetImageResolution(NUI_IMAGE_RESOLUTION_1280x960);
            break;

        case ID_RESOLUTION_YUVRESOLUTION640X480FPS15:
            m_pColorStream->SetImageType(NUI_IMAGE_TYPE_COLOR_YUV);
            m_pColorStream->SetImageResolution(NUI_IMAGE_RESOLUTION_640x480);
            break;

        case ID_RESOLUTION_INFRAREDRESOLUTION640X480FPS30:
            m_pColorStream->SetImageType(NUI_IMAGE_TYPE_COLOR_INFRARED);
            m_pColorStream->SetImageResolution(NUI_IMAGE_RESOLUTION_640x480);
            break;

        case ID_RESOLUTION_RAWBAYERRESOLUTION640X480FPS30:
            m_pColorStream->SetImageType(NUI_IMAGE_TYPE_COLOR_RAW_BAYER);
            m_pColorStream->SetImageResolution(NUI_IMAGE_RESOLUTION_640x480);
            break;

        case ID_RESOLUTION_RAWBAYERRESOLUTION1280X960FPS12:
            m_pColorStream->SetImageType(NUI_IMAGE_TYPE_COLOR_RAW_BAYER);
            m_pColorStream->SetImageResolution(NUI_IMAGE_RESOLUTION_1280x960);
            break;

        default:
            return;
        }

        m_pColorStream->OpenStream();
    }
    else if (ID_DEPTHSTREAM_PAUSE == commandId)
    {
        // Pause depth stream
        if(m_pDepthStream)
        {
            m_pDepthStream->PauseStream(!previouslyChecked);
        }
    }
    else if (ID_DEPTHSTREAM_RANGEMODE_START <= commandId && ID_DEPTHSTREAM_RANGEMODE_END >= commandId)
    {
        // Set depth stream range mode
        bool nearMode = false;
        switch (commandId)
        {
        case ID_RANGEMODE_DEFAULT:
            nearMode = false;
            break;

        case ID_RANGEMODE_NEAR:
            nearMode = true;
            break;

        default:
            return;
        }

        if (m_pDepthStream)
        {
            m_pDepthStream->SetNearMode(nearMode);
        }

        if (m_pSkeletonStream)
        {
            m_pSkeletonStream->SetNearMode(nearMode);
        }
    }
    else if (ID_DEPTHSTREAM_RESOLUTION_START <= commandId && ID_DEPTHSTREAM_RESOLUTION_END >= commandId)
    {
        // Set depth stream resolution
        NUI_IMAGE_RESOLUTION resolution = (NUI_IMAGE_RESOLUTION)(commandId - ID_DEPTHSTREAM_RESOLUTION_START);
        if (m_pDepthStream)
        {
            m_pDepthStream->OpenStream(resolution);
        }
    }
    else if (ID_DEPTHSTREAM_DEPTHTREATMENT_START <= commandId && ID_DEPTHSTREAM_DEPTHTREATMENT_END >= commandId)
    {
        // Set depth stream treatment mode
        DEPTH_TREATMENT treatment = (DEPTH_TREATMENT)(commandId - ID_DEPTHSTREAM_DEPTHTREATMENT_START);
        if (m_pDepthStream)
        {
            m_pDepthStream->SetDepthTreatment(treatment);
        }
    }
    else if (ID_SKELETONSTREAM_PAUSE == commandId)
    {
        // Pause skeleton stream
        if (m_pSkeletonStream)
        {
            m_pSkeletonStream->PauseStream(!previouslyChecked);
        }
    }
    else if (ID_SKELETONSTREAM_TRACKINGMODE_START <= commandId && ID_SKELETONSTREAM_TRACKINGMODE_END >= commandId)
    {
        // Set skeleton track mode
        if (!m_pSkeletonStream)
        {
            return;
        }

        switch (commandId)
        {
        case ID_TRACKINGMODE_DEFAULT:
            m_pSkeletonStream->SetSeatedMode(false);
            break;

        case ID_TRACKINGMODE_SEATED:
            m_pSkeletonStream->SetSeatedMode(true);
            break;

        default:
            return;
        }
    }
    else if (ID_SKELETONSTREAM_CHOOSERMODE_START <= commandId && ID_SKELETONSTREAM_CHOOSERMODE_END >= commandId)
    {
        // Set skeleton chooser mode
        if(!m_pSkeletonStream)
        {
            return;
        }

        m_pSkeletonStream->SetChooserMode(ConvertCommandIdToChooserMode(commandId));
    }
    else
    {
        switch (commandId)
        {
            // Bring up camera color setting dialog
        case ID_CAMERA_COLORSETTINGS:
            m_pColorSettingsView->ShowView();
            break;

            // Bring up camera exposure setting dialog
        case ID_CAMERA_EXPOSURESETTINGS:
            m_pExposureSettingsView->ShowView();
            break;

            // Switch the stream display on primary and secondary stream viewers
        case ID_VIEWS_SWITCH:
            if (m_pColorStream && m_pDepthStream)
            {
                m_pColorStream->SetStreamViewer(m_pDepthStream->SetStreamViewer(m_pColorStream->SetStreamViewer(nullptr)));
            }
            break;

        case ID_FORCE_OFF_IR:
            m_pNuiSensor->NuiSetForceInfraredEmitterOff(param);
            break;

		//////Recording
		case ID_RECORDING_AUDIO:
			if (m_pAudioStream && !m_pAudioStream->GetRecordingStauts())
			{
				m_pAudioStream->SetRecordingStatus(true);
			}
			else if (m_pAudioStream && m_pAudioStream->GetRecordingStauts())
			{
				m_pAudioStream->m_pWaveWriter->Stop();
				delete(m_pAudioStream->m_pWaveWriter);
				m_pAudioStream->m_pWaveWriter=NULL;
				m_pAudioStream->SetRecordingStatus(false);
			}
			break;

		case ID_RECORDING_RGB:
			if (m_pColorStream && !m_pColorStream->GetRecordingStauts())
			{
				m_pColorStream->SetRecordingStatus(true);
			}
			else if (m_pColorStream && m_pColorStream->GetRecordingStauts())
			{
				cvReleaseVideoWriter(&m_pColorStream->m_pwriter);
				m_pColorStream->m_pwriter=nullptr;
				m_pColorStream->SetRecordingStatus(false);
			}
			break;

		case ID_RECORDING_DEPTH:
			if (m_pDepthStream && !m_pDepthStream->GetRecordingStauts())
			{
				m_pDepthStream->SetRecordingStatus(true);
			} 
			else if (m_pDepthStream && m_pDepthStream->GetRecordingStauts())
			{
				cvReleaseVideoWriter(&m_pDepthStream->m_pwriter);
				m_pDepthStream->m_pwriter=nullptr;
				m_pDepthStream->SetRecordingStatus(false);
			}
			break;

		case ID_RECORDING_ALL:
			////RGB
			if (m_pColorStream && !m_pColorStream->GetRecordingStauts())
			{
				m_pColorStream->SetRecordingStatus(true);
			}
			else if (m_pColorStream && m_pColorStream->GetRecordingStauts())
			{
				cvReleaseVideoWriter(&m_pColorStream->m_pwriter);
				m_pColorStream->m_pwriter=nullptr;
				m_pColorStream->SetRecordingStatus(false);
			}
			////Depth
			if (m_pDepthStream && !m_pDepthStream->GetRecordingStauts())
			{
				m_pDepthStream->SetRecordingStatus(true);
			} 
			else if (m_pDepthStream && m_pDepthStream->GetRecordingStauts())
			{
				cvReleaseVideoWriter(&m_pDepthStream->m_pwriter);
				m_pDepthStream->m_pwriter=nullptr;
				m_pDepthStream->SetRecordingStatus(false);
			}
			//////Audio
			if (m_pAudioStream && !m_pAudioStream->GetRecordingStauts())
			{
				m_pAudioStream->SetRecordingStatus(true);
			}
			else if (m_pAudioStream && m_pAudioStream->GetRecordingStauts())
			{
				m_pAudioStream->m_pWaveWriter->Stop();
				delete(m_pAudioStream->m_pWaveWriter);
				m_pAudioStream->m_pWaveWriter=NULL;
				m_pAudioStream->SetRecordingStatus(false);
			}
			break;
		
		////Recording 3D facial model
		case ID_RECORDING_3DFACIALMODEL:
			if (!(pFaceTracker->GetFTRecordingStatus())) 
				pFaceTracker->SetFTRecordingStatus(true);
			else
			{
				pFaceTracker->SetFTRecordingStatus(false);
				pFaceTracker->ResetAUSUcounts();
				pFaceTracker->CloseAUSUfile();
			}
			break;
		////Speech recognition dication pad
		case ID_SPEECHRECOGNITION:
			/*if (!m_threadRun)
			{*/
				//m_hSpeechRecogThread=CreateThread(NULL, 0, m_pKinectWindow->SpeechRecogStaticThread, (PVOID)m_pKinectWindow, 0, 0);
				//m_threadRun=true;
		/*	}
			else
			{*/
				//if (m_hSpeechRecogThread)
				//{
				//	CSimpleDict* pSimpleDict;
				//	m_pKinectWindow->GetSimpleDict(&pSimpleDict);
				//	pSimpleDict->~CSimpleDict();
				//    WaitForSingleObject(m_hSpeechRecogThread, 200);
			 //       CloseHandle(m_hSpeechRecogThread);
				//    m_threadRun=false;
				//}
			//}
			break;

		////In-bed detection
		case ID_FALLDETECTION:
			if (!(pFallDetect->getIsRunFallDetect()))
			{
				pFallDetect->setIsRunFallDetect(TRUE);
				if (!m_FallDetectThreadRun)
				{
				    m_hFallDetectTxt2SpeechThread = CreateThread(NULL, 0, pFallDetect->Txt2SpeechStaticThread, (PVOID)pFallDetect, 0, 0);
			        m_FallDetectThreadRun = TRUE;
				}
			}
			else
			{
				pFallDetect->setIsRunFallDetect(FALSE);
				if (m_FallDetectThreadRun)
				{
					DWORD lpExitCode;
					GetExitCodeThread(m_hFallDetectTxt2SpeechThread, &lpExitCode);
					TerminateThread(m_hFallDetectTxt2SpeechThread, lpExitCode);
					WaitForSingleObject(m_hFallDetectTxt2SpeechThread, 200);
				    CloseHandle(m_hFallDetectTxt2SpeechThread);
				    m_FallDetectThreadRun = FALSE;
				}
			}
			break;

		case ID_MOVEMENTDETECTION:	
			if (!(pFallDetect->getIsRunMovementDetect()))
			{
				pFallDetect->setIsRunMovementDetect(TRUE);
			}
			else
			{
				pFallDetect->setIsRunMovementDetect(FALSE);
			}
			break;

		case ID_OUTOFBEDDETECTION: 		  
			break;

		case ID_LYANGLEDETECTION:
			if (!(pDepthInbedApps->getIsRunLyAngleDetect()))
			{
				pDepthInbedApps->setIsRunLyAngleDetect(TRUE);
			}
			else
			{
				pDepthInbedApps->setIsRunLyAngleDetect(FALSE);
			}
			break;

		case ID_CALLNURSINGBYHANDRAISING:
			if (!(pFallDetect->getIsRunHandsMovementRIC()))
			{
				pFallDetect->setIsRunHandsMovementRIC(TRUE);
				if (!m_NurseCallThreadRun)
				{
				    m_hNurseCallTxt2SpeechThread = CreateThread(NULL, 0, m_pPrimaryView->Txt2SpeechStaticThread, (PVOID)m_pPrimaryView, 0, 0);
			        m_NurseCallThreadRun = TRUE;
				}
				
			}
			else
			{
				pFallDetect->setIsRunHandsMovementRIC(FALSE);
				if (m_NurseCallThreadRun)
				{
					DWORD lpExitCode;
					GetExitCodeThread(m_hNurseCallTxt2SpeechThread, &lpExitCode);
					TerminateThread(m_hNurseCallTxt2SpeechThread, lpExitCode);
					WaitForSingleObject(m_hNurseCallTxt2SpeechThread, 200);
				    CloseHandle(m_hNurseCallTxt2SpeechThread);
				    m_NurseCallThreadRun = FALSE;
				}
			}
			break;

		case ID_VIEWDETECTIONRECS:
			if (!m_processFlag)
			{
				ViewDetectionRes();
			    m_processFlag = TRUE;
			}
			else
			{
				GetViewDetecResProcessStatus(&ExitCode);
				TerminateProcess(m_pi.hProcess, ExitCode);
				m_processFlag = FALSE;
			}
			break;

		case ID_STANDMOVELEGOUTWARD:
			if (!(pLegRaisExer->isRunningExcer()))
			{
				Sleep(5000);
				pLegRaisExer->setRunningExer(TRUE);
				if (!m_LegRaisexcerThreadRun)
				{
				    m_hLegRaisExcerTxt2SpeechThread = CreateThread(NULL, 0, pLegRaisExer->Txt2SpeechStaticThread, (PVOID)pLegRaisExer, 0, 0);
			        m_LegRaisexcerThreadRun = TRUE;
				}
			}
			else
			{
				pLegRaisExer->setRunningExer(FALSE);
				pLegRaisExer->Reset();
				if (m_LegRaisexcerThreadRun)
				{
					DWORD lpExitCode;
					GetExitCodeThread(m_hLegRaisExcerTxt2SpeechThread, &lpExitCode);
					TerminateThread(m_hLegRaisExcerTxt2SpeechThread, lpExitCode);
					WaitForSingleObject(m_hLegRaisExcerTxt2SpeechThread, 200);
				    CloseHandle(m_hLegRaisExcerTxt2SpeechThread);
				    m_LegRaisexcerThreadRun = FALSE;
				}
			}
			break;

		case ID_STANDARMSLIFTWEIGHTS:
			if (!(pHandRaisExer->isRunningExcer()))
			{
				Sleep(5000);
				pHandRaisExer->setRunningExer(TRUE);
				if (!m_HandRaisexcerThreadRun)
				{
				    m_hHandRaisExcerTxt2SpeechThread = CreateThread(NULL, 0, pHandRaisExer->Txt2SpeechStaticThread, (PVOID)pHandRaisExer, 0, 0);
			        m_HandRaisexcerThreadRun = TRUE;
				}
			}
			else
			{
				pHandRaisExer->setRunningExer(FALSE);
				pHandRaisExer->Reset();
				if (m_HandRaisexcerThreadRun)
				{
					DWORD lpExitCode;
					GetExitCodeThread(m_hHandRaisExcerTxt2SpeechThread, &lpExitCode);
					TerminateThread(m_hHandRaisExcerTxt2SpeechThread, lpExitCode);
					WaitForSingleObject(m_hHandRaisExcerTxt2SpeechThread, 200);
				    CloseHandle(m_hHandRaisExcerTxt2SpeechThread);
				    m_HandRaisexcerThreadRun = FALSE;
				}
			}
			break;

        default:
            break;
        }
    }
}