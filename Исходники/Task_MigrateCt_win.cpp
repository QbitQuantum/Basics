PRL_RESULT Task_MigrateCtSource::run_body()
{
	SmartPtr<CVmEvent> pEvent;
	SmartPtr<IOPackage> pPackage;
	IOSendJob::Response pResponse;
	CDispToDispCommandPtr pCmd;
	CDispToDispResponseCommand *pRespCmd;

	//https://bugzilla.sw.ru/show_bug.cgi?id=267152
	CAuthHelperImpersonateWrapper _impersonate( &getClient()->getAuthHelper() );

	if (operationIsCancelled())
		setLastErrorCode(PRL_ERR_OPERATION_WAS_CANCELED);

	PRL_RESULT nRetCode = PRL_ERR_SUCCESS;

	if (PRL_FAILED(nRetCode = CheckVmMigrationPreconditions()))
		goto exit;

	/* set migration mode */
	switch (m_nPrevVmState) {
	case VMS_RUNNING:
	case VMS_PAUSED:
		nRetCode = PRL_ERR_VM_MIGRATE_WARM_MODE_NOT_SUPPORTED;
		goto exit;
	default:
		m_nMigrationFlags |= PVMT_COLD_MIGRATION;
	}

	if (operationIsCancelled())
		setLastErrorCode(PRL_ERR_OPERATION_WAS_CANCELED);

	pEvent = SmartPtr<CVmEvent>(new CVmEvent(PET_DSP_EVT_VM_MIGRATE_STARTED, m_sVmUuid, PIE_DISPATCHER));
	pEvent->addEventParameter(new CVmEventParameter(PVE::Boolean, "true", EVT_PARAM_MIGRATE_IS_SOURCE));
	pPackage = DispatcherPackage::createInstance(PVE::DspVmEvent, pEvent->toString());

	m_nSteps |= MIGRATE_VM_STATE_CHANGED;
	/* and notify clients about VM migration start event */
	CDspService::instance()->getClientManager().sendPackageToVmClients(pPackage, m_sVzDirUuid, m_sVmUuid);

	/* remove target Vm config from watcher (#448235) */
	CDspService::instance()->getVmConfigWatcher().unregisterVmToWatch(m_sVmConfigPath);
	m_nSteps |= MIGRATE_UNREGISTER_VM_WATCH;

	nRetCode = migrateStoppedCt();
	if (PRL_FAILED(nRetCode))
		goto exit;

	/* wait finish reply from target (https://jira.sw.ru/browse/PSBM-9596) */
	quint32 nTimeout = m_nTimeout;

	/* wait target task finish */
	if (PVMT_CHANGE_SID & getRequestFlags())
		/* wait reply during changeSID task timeout (https://jira.sw.ru/browse/PSBM-9733) */
		nTimeout = CHANGESID_TIMEOUT;
	if (m_pIoClient->waitForResponse(m_hCheckReqJob, nTimeout) != IOSendJob::Success) {
		WRITE_TRACE(DBG_FATAL, "Finish acknowledgement receiving failure");
		nRetCode = PRL_ERR_CT_MIGRATE_INTERNAL_ERROR;
		goto exit;
	}
	pResponse = m_pIoClient->takeResponse(m_hCheckReqJob);
	if (pResponse.responseResult != IOSendJob::Success) {
		WRITE_TRACE(DBG_FATAL, "Finish acknowledgement receiving failure");
		nRetCode = PRL_ERR_CT_MIGRATE_INTERNAL_ERROR;
		goto exit;
	}
	pPackage  = pResponse.responsePackages[0];
	if (pPackage->header.type != DispToDispResponseCmd) {
		WRITE_TRACE(DBG_FATAL, "Invalid package type : %d", pPackage->header.type);
		nRetCode = PRL_ERR_CT_MIGRATE_INTERNAL_ERROR;
		goto exit;
	}

	pCmd = CDispToDispProtoSerializer::ParseCommand(
		DispToDispResponseCmd, UTF8_2QSTR(pPackage->buffers[0].getImpl()));
	pRespCmd = CDispToDispProtoSerializer::CastToDispToDispCommand<CDispToDispResponseCommand>(pCmd);
	nRetCode = pRespCmd->GetRetCode();
	if (PRL_FAILED(nRetCode))
		getLastError()->fromString(pRespCmd->GetErrorInfo()->toString());

exit:
	setLastErrorCode(nRetCode);
	return nRetCode;
}