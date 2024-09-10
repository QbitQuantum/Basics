void TestLoggingMacros::TestLogTraceComError()
{
	Workshare::Logging::Configuration::EnableLogging(true);
	Workshare::Logging::Configuration::SetSeverity(EVENT_SEVERITY_TRACE);
	Workshare::Logging::Configuration::EnableFileLog(true);
	Logger::GetInstance().ReadConfiguration();

	SYSTEMTIME time; // can't test for time; this is dynamically generated so is untestable.
	GetLocalTime(&time);

	Event refEvent(time, EVENT_SEVERITY_TRACE, L"TestHarness.exe", ::_getpid(), GetCurrentThreadId(), L"Workshare.Logging.Tests.dll", __FILE__, __LINE__ + 1, __FUNCTION__, L"Com Exception:\r\nDetails: 0x80040004 - (null)");
	LOG_WS_TRACE_RESULT(_com_error(OLE_E_NOCONNECTION));

	MockILogger* pMockILogger = static_cast<MockILogger*>(Logger::GetInstance().GetFileLogger());
	assertTest(pMockILogger->GetEventCount() == 1);
	Event logEvent = pMockILogger->GetEvent(1);

	assertEquals( refEvent.GetFileName(),		logEvent.GetFileName(),		__LINE__,	L"FileName not equal" );
	assertEquals( refEvent.GetFunctionName(),	logEvent.GetFunctionName(), __LINE__,	L"FunctionName not equal" );
	assertEquals( refEvent.GetLineNumber(),		logEvent.GetLineNumber(),	__LINE__,	L"LineNumber not equal" );
	assertEquals( refEvent.GetSeverity(),		logEvent.GetSeverity(),		__LINE__,	L"Severity not equal" );
	assertEquals( refEvent.GetMessage(),		logEvent.GetMessage(),		__LINE__,	L"Message not equal" );
	assertEquals( refEvent.GetProcess().Normalize(),		logEvent.GetProcess().Normalize(),		__LINE__,	L"Process not equal" );
	assertEquals( refEvent.GetPid(),			logEvent.GetPid(),		    __LINE__,	L"Pid not equal" );
	assertEquals( refEvent.GetThreadId(),		logEvent.GetThreadId(),		__LINE__,	L"Thread id not equal" );
	assertEquals( refEvent.GetModule(),			logEvent.GetModule(),		__LINE__,	L"Module not equal" );
}