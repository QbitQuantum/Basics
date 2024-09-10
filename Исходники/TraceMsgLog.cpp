void CTraceMsgLog::TraceMessage(int level, CString str)
{
	CString traceMsg(_T(""));
	switch(level)
	{
	case MSGINFO:
		traceMsg.Append(_T("[INFO] "));
		break;

	case MSGERROR:
		traceMsg.Append(_T("[ERR] "));
		break;

	case JAVASCRIPT_ALERT:
		traceMsg.Append(_T("[JAVASCRIPT ALERT] "));
		break;

	default:
		traceMsg.Append(_T("[DEBUG] "));
		break;
	}
	//
	traceMsg.Append(str);
	//
	TraceMessage(traceMsg);
}