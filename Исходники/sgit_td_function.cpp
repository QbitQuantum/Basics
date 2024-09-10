int TdApi::reqExecOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputExecOrderField myreq = CThostFtdcInputExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExecOrderRef", myreq.ExecOrderRef);
	getChar(req, "CloseFlag", &myreq.CloseFlag);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "PosiDirection", &myreq.PosiDirection);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionType", &myreq.ActionType);
	getChar(req, "ReservePositionFlag", &myreq.ReservePositionFlag);
	int i = this->api->ReqExecOrderInsert(&myreq, nRequestID);
	return i;
};