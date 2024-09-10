int TdApi::reqInsertOrder(dict req)
{
	DFITCInsertOrderField myreq = DFITCInsertOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getInt(req, "openCloseType", &myreq.openCloseType);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getDouble(req, "insertPrice", &myreq.insertPrice);
	getChar(req, "orderProperty", myreq.orderProperty);
	getShort(req, "buySellType", &myreq.buySellType);
	getInt(req, "orderType", &myreq.orderType);
	getLong(req, "minMatchAmount", &myreq.minMatchAmount);
	getInt(req, "speculator", &myreq.speculator);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "reservedType2", &myreq.reservedType2);
	getInt(req, "insertType", &myreq.insertType);
	getLong(req, "orderAmount", &myreq.orderAmount);
	getDouble(req, "profitLossPrice", &myreq.profitLossPrice);
	getString(req, "customCategory", myreq.customCategory);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqInsertOrder(&myreq);
	return i;
};