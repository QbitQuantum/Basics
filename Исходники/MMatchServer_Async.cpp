void MMatchServer::OnAsyncInsertConnLog(MAsyncJob* pJobResult)
{
	if (pJobResult->GetResult() != MASYNC_RESULT_SUCCEED) {
		char szTime[128]="";
		_strtime(szTime);

		mlog("[%s] Async DB Query(OnAsyncInsertConnLog) Failed\n", szTime);
		return;
	}		

}