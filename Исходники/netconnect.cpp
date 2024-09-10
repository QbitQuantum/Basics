extern "C" void odbc_SQLSvc_EndTransaction_ccf_ (
    CEE_tag_def cmptag_
  , const struct odbc_SQLSvc_EndTransaction_exc_ *exception_
  , const ERROR_DESC_LIST_def *sqlWarning
  )
{

	SRVR_CALL_CONTEXT	*srvrCallContext = (SRVR_CALL_CONTEXT *)cmptag_;
	CConnect			*pConnection = (CConnect *)srvrCallContext->sqlHandle;

	pConnection->setExceptionErrors(exception_->exception_nr, exception_->exception_detail);
	switch (exception_->exception_nr)
	{
		case CEE_SUCCESS:
			if (sqlWarning->_length > 0)
				pConnection->setDiagRec(sqlWarning);
			break;
		case odbc_SQLSvc_EndTransaction_SQLError_exn_:
			pConnection->setDiagRec(&exception_->u.SQLError);
			break;
		case odbc_SQLSvc_EndTransaction_ParamError_exn_:
			pConnection->setDiagRec(SERVER_ERROR, IDS_PROGRAM_ERROR, exception_->exception_nr, 
					exception_->u.ParamError.ParamDesc, NULL, 
					SQL_ROW_NUMBER_UNKNOWN, SQL_COLUMN_NUMBER_UNKNOWN, 1, pConnection->getSrvrIdentity());
			break;
		case odbc_SQLSvc_EndTransaction_SQLInvalidHandle_exn_:
			break;
		case odbc_SQLSvc_EndTransaction_InvalidConnection_exn_:
			pConnection->setDiagRec(SERVER_ERROR, IDS_08_S01);
			break;
		case odbc_SQLSvc_EndTransaction_TransactionError_exn_:
			char tmpNumBuffer[16];
			_itoa (exception_->exception_detail, tmpNumBuffer, 10);
			pConnection->setDiagRec(SERVER_ERROR, IDS_TRANSACTION_ERROR, exception_->exception_nr,
						tmpNumBuffer, NULL, SQL_ROW_NUMBER_UNKNOWN, SQL_COLUMN_NUMBER_UNKNOWN, 1, pConnection->getSrvrIdentity());
			break;
		default:
			pConnection->sendCDInfo(exception_->exception_nr);
			pConnection->setDiagRec(exception_->exception_nr, ENDTRANSACT_PROCNAME,
					pConnection->getSrvrIdentity());
			break;
	}

} // odbc_SQLSvc_EndTransaction_ccf_()