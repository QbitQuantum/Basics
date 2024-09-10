///询价通知
void CMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	LOG2("Subscribed Quote Response for InstrmentID: ", pForQuoteRsp->InstrumentID);
}