void CDispToDispProtoSerializerTest::testParseDispToDispResponseCommand()
{
	RESPONSE_CMD_PARAMS_DECLARE
	SmartPtr<CVmEvent> _pkg( new CVmEvent );
	_pkg->setEventCode(nRetCode);
	_pkg->addEventParameter(new CVmEventParameter(PVE::String, pErrorEvent->toString(),
							EVT_PARAM_DISP_TO_DISP_RESPONSE_CMD_ERROR_INFO));
	_pkg->addEventParameter(new CVmEventParameter(PVE::UnsignedInt, QString("%1").arg(nRequestCmdId),
							EVT_PARAM_DISP_TO_DISP_RESPONSE_CMD_REQUEST_ID));
	_pkg->addEventParameter(new CVmEventParameterList(PVE::String, QStringList(),
							EVT_PARAM_DISP_TO_DISP_RESPONSE_CMD_PARAMS_LIST));
	CDispToDispCommandPtr pCmd = CDispToDispProtoSerializer::ParseCommand(DispToDispResponseCmd, _pkg->toString());
	QVERIFY(pCmd->IsValid());
	CDispToDispResponseCommand *pDispToDispResponseCmd =
				CDispToDispProtoSerializer::CastToDispToDispCommand<CDispToDispResponseCommand>(pCmd);
	QCOMPARE(pErrorEvent->toString(), pDispToDispResponseCmd->GetErrorInfo()->toString());
	QCOMPARE((quint32)nRequestCmdId, (quint32)pDispToDispResponseCmd->GetRequestCommandId());
	QCOMPARE((quint32)nRetCode, (quint32)pDispToDispResponseCmd->GetRetCode());
}