BOOL CInputDoc::doRunProcessors(CRemoteCommand* pRemoteCmd/*=NULL*/)
{
	CWnd* pWnd = getWindow();
	if(pWnd)
		pWnd->BringWindowToTop();

	if(IsModified())	// if changed the contents of the file we're processing
		OnSaveDocument(GetPathName());

	CCarlaLanguage *pSourceLang = getProcessingPrefs()->getSrcLang(); // could be null
	CCarlaLanguage *pTargetLang = getProcessingPrefs()->getTarLang(); // could be null
	ASSERTX(m_strPathName.GetLength());

	#define GOAL getProcessingPrefs()->getGoal()

	// on remote calls, we can override user prefs. Sorry this is all so ugly
	if(pRemoteCmd)
	{
		getProcessingPrefs()->setGoal(pRemoteCmd->iGoal);
		pSourceLang = pRemoteCmd->pSourceLang ;
		if(pSourceLang)
			getProcessingPrefs()->setSrcLang(pSourceLang);
		pTargetLang = pRemoteCmd->pTargetLang;
		if(pTargetLang)
			getProcessingPrefs()->setTarLang(pTargetLang);
		SetModifiedFlag(TRUE);// will also fix the title
	}

	// make the new status structure, which keeps track of which files have been
	// created and are in line for processing, among other things

	if(m_pProcessStatus)
		delete m_pProcessStatus;
	m_pProcessStatus = new CProcessStatus(m_strPathName,
								getProcessingPrefs(),
								pSourceLang,
								(pSourceLang!=0)?pSourceLang->getMFS():NULL,
								pTargetLang,
								(pTargetLang!=0)?pTargetLang->getMFS():NULL);

	//----- ask Shoebox, if it is running, to do a save all
	// note: if this was invoked by a call from CSRemote, then the send will hang us forever
	// thus, we have this bRemoteCall flag to prevent that.  If we are called from
	// Shoebox, it will have saved everything anyways as part of its batch file command
	if(!pRemoteCmd)
		SendMessage(HWND_BROADCAST, wm_RemoteSaveAll, NULL, NULL);

	//------ SETUP THE TEMP DIRECTORY ----------------------

	if( getCanDoAnalysis() || getProcessingPrefs()->getDoTransfer()
			|| getProcessingPrefs()->getDoInterlinearize()) // JDH 5/28/99 Added to allow Interlinearizing ANA files
	{
		ASSERTX(pSourceLang);
		if (!m_pProcessStatus->setupTempDir(pSourceLang->getName()))
			return FALSE;
	}
	else	// synthesis only
	{
		ASSERTX(pTargetLang);
		if (!m_pProcessStatus->setupTempDir(pTargetLang->getName()))
			return FALSE;
	}

	// load stuff that processors will commonly need, but which doesn't really
	// belong conceptually to the mfs into it, so that the processors can avoid
	// having to know about CCarlaLanguage just to get at the comment character, for example

	if(pSourceLang)
		pSourceLang->prepareMFSForProcessors();
	if(pTargetLang)
		pTargetLang->prepareMFSForProcessors();

	//---- SETUP PROGRESS BAR
	if( getCanDoAnalysis())
		m_pProcessStatus->expectSequenceWithCount(getSrcLang()->getAnalysisSequence()->getProcessorCount());
	if( getProcessingPrefs()->getDoInterlinearize())
		m_pProcessStatus->expectSequenceWithCount(getSrcLang()->getInterlinearSequence()->getProcessorCount());

	if(getProcessingPrefs()->getDoTransfer())
	{
		CTransferProcessSequence* pTSeq = getSrcLang()->getTransferSequence( pTargetLang);
		if(pTSeq)
			m_pProcessStatus->expectSequenceWithCount(pTSeq->getProcessorCount());
	}
	if(getProcessingPrefs()->getDoSynthesis())	// actually, i think you *always* have a synth seq
	{
		CSynthesisProcessSequence* pSSeq = getSrcLang()->getSynthesisSequence();
		if(pSSeq)
			m_pProcessStatus->expectSequenceWithCount(pSSeq->getProcessorCount());
	}


	//---- BRING THE CONTROL FILES UP TO DATE ON THE DISK
	theApp.getProject()->synchronizeExternals();

	//---- ANALYSIS ----------------------------------------------------------

	BOOL bOK = TRUE;
	if( getCanDoAnalysis())
	{
		CProcessSequence* pAnalysisSequence = getSrcLang()->getAnalysisSequence();

		m_pProcessStatus->setCurrentSequenceFunction(pAnalysisSequence->getFunctionCode());
		m_pProcessStatus->setInputLang(pSourceLang);
		m_pProcessStatus->setOutputLang(NULL);
		// do the analysis

		bOK = pAnalysisSequence->continueProcessing(m_pProcessStatus);

		// copy the analyzed text to the user's directory
		if(bOK )
		{
			CPathDescriptor newPath(pSourceLang->getMFS()->getOutputDirAnalyzedANA()+m_pProcessStatus->m_sFileNameRoot+".ana");
			redirectOutputFile(GOAL, CProcessingPrefs::kSourceAna,
				m_pProcessStatus->sANAPath,
				newPath,
				m_pProcessStatus);
		}
	}

	//---- INTERLINEAR ----------------------------------------------------------

	if(bOK && getProcessingPrefs()->getDoInterlinearize())
	{
		ASSERTX(pSourceLang);
		CProcessSequence* pS = pSourceLang->getInterlinearSequence();
		ASSERTX(pS);

		m_pProcessStatus->setInputLang(pSourceLang);
#ifndef hab15a4
		m_pProcessStatus->setOutputLang(pSourceLang); // hab 1999.09.17
		// a final CC pass will use the Output Language;
		// it needs to be set to the Source lang here (at least it worked for me...)
#else
		m_pProcessStatus->setOutputLang(NULL);
#endif
		m_pProcessStatus->setCurrentSequenceFunction(pS->getFunctionCode());
		bOK = pS->continueProcessing(m_pProcessStatus);

		if(bOK )//&& GOAL==CProcessingPrefs::kGlossedInterlinear)
		{
			CString sDestDir;
			CPathDescriptor newPath ;
			if(pRemoteCmd)
			{
				switch(pRemoteCmd->eOutputLocation)
				{
					case CRemoteCommand::csSameFolderAsInput:
							sDestDir = ::getDirectory(m_strPathName);
							break;
					case CRemoteCommand::csSpecifiedPath:
					case CRemoteCommand::csReplaceInput:
							newPath = pRemoteCmd->sDesiredOutputPath;
							break;
					default: throw("Unknown OutputLocation setting");
							break;
				}
			}
			else if(getProcessingPrefs()->m_dwFlags & CProcessingPrefs::kOutputItxToSameDir) // for morris
				sDestDir = ::getDirectory(m_strPathName);
			else // copy to interlinear output dir
				sDestDir = pSourceLang->getMFS()->getOutputDirInterlinear();

			if(newPath.GetLength() == 0)
				newPath = sDestDir+m_pProcessStatus->m_sFileNameRoot+".itx";
			//m_pProcessStatus->sInterlinearPath.copyTo(newPath);

			redirectOutputFile(GOAL, CProcessingPrefs::kGlossedInterlinear,
				m_pProcessStatus->sInterlinearPath,
				newPath,
				m_pProcessStatus);

			if(pRemoteCmd)
				pRemoteCmd->sActualOutputPath=newPath;
		}
	}

	//---- TRANSFER ----------------------------------------------------------

	if(bOK && getProcessingPrefs()->getDoTransfer())
	{
		//CCarlaLanguage* pTarget = getProcessingPrefs()->getTarLang();
		ASSERTX(pTargetLang);
		CTransferProcessSequence* pTransferSequence = getSrcLang()->getTransferSequence(pTargetLang);
		ASSERTX(pTransferSequence);
		m_pProcessStatus->setInputLang(pSourceLang);
		m_pProcessStatus->setOutputLang(pTargetLang);
		m_pProcessStatus->setCurrentSequenceFunction(pTransferSequence->getFunctionCode());

		bOK = pTransferSequence->continueProcessing(m_pProcessStatus);
		if(bOK )//&& GOAL==CProcessingPrefs::kTargetANA)
		{
			//CPathDescriptor x = pTargetLang->getMFS()->getOutputDirTransferedANA();
			//CString z = "s" + x  + "v";

			CPathDescriptor newPath(pTargetLang->getMFS()->getOutputDirTransferedANA()+m_pProcessStatus->m_sFileNameRoot+".ana");
			redirectOutputFile(GOAL, CProcessingPrefs::kTargetANA,
				m_pProcessStatus->sANAPath,
				newPath,
				m_pProcessStatus);
			//m_pProcessStatus->sANAPath.copyTo(pTargetLang->getMFS()->getOutputDirTransferedANA()+m_pProcessStatus->m_sFileNameRoot+".ana");

			if(pRemoteCmd)
				pRemoteCmd->sActualOutputPath=newPath;
		}
	}

	//---- SYNTHESIS ----------------------------------------------------------

	if(bOK && getProcessingPrefs()->getDoSynthesis())
	{
		ASSERTX(pTargetLang);
		//CCarlaLanguage* pTarget = getProcessingPrefs()->getTarLang();
		CProcessSequence* pS = pTargetLang->getSynthesisSequence();
		ASSERTX(pS);
#ifndef hab15a4
		m_pProcessStatus->setInputLang(pTargetLang); // hab 1999.09.17
		// a final CC pass will use the Input Language;
		// it needs to be set to the Target lang here  (at least it worked for me...)
#else
		m_pProcessStatus->setInputLang(NULL);
#endif
		m_pProcessStatus->setOutputLang(pTargetLang);
		m_pProcessStatus->setCurrentSequenceFunction(pS->getFunctionCode());
		bOK = pS->continueProcessing(m_pProcessStatus);

		// copy the synthesized text to the user's directory
		if(bOK)// && GOAL==CProcessingPrefs::kTargetText)
		{
			CPathDescriptor newPath;
			CString sDestDir;
			if(pRemoteCmd)
			{
				switch(pRemoteCmd->eOutputLocation)
				{
					case CRemoteCommand::csSameFolderAsInput:
							sDestDir = ::getDirectory(m_strPathName);
							break;
					case CRemoteCommand::csSpecifiedPath:
							newPath = pRemoteCmd->sDesiredOutputPath;
							break;
					// this case now allowed by csbridge, but would be if they scripted directly
					case CRemoteCommand::csReplaceInput:
							throw("Whoops.  You probably didn't mean to say that CStudio should do a transfer that overwrites the initial file.");
							break;
					default: throw("Unknown OutputLocation setting");
							break;
				}
			}
			else
				sDestDir = pTargetLang->getMFS()->getOutputDirSynthesizedText();

			if(newPath.GetLength() == 0)
				newPath = sDestDir+m_pProcessStatus->m_sFileNameRoot+"_"+pTargetLang->getAbrev()+".txt";

			redirectOutputFile(GOAL, CProcessingPrefs::kTargetText,
				m_pProcessStatus->sRAWPath,
				newPath,
				m_pProcessStatus);
			if(pRemoteCmd)
					pRemoteCmd->sActualOutputPath=newPath;
		}
	}

	if(bOK)
		m_pProcessStatus->finishedProcessing();
		storeAvailablePanels();

	loadResultPanels(bOK, m_pProcessStatus); // don't warn about missing files if there was an error already reported
	m_pProcessStatus->closeProgressDialog();

	ASSERTX(m_pView);	//!!!!!!!WHO'S SETTING THIS?
	m_pView->updatePanels();

#ifndef rde265
	//----- ask Shoebox, to refresh all (if this isn't a remote command)
	if(!pRemoteCmd)
#else
	//----- ask Shoebox, if it is running, to do a save all
#endif  // rde265
	PostMessage(HWND_BROADCAST, wm_RemoteRefreshAll, NULL, NULL);	// don't wait for it to finish that

	return bOK;
}