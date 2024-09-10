// Call Trade Order Frame 5
void CTradeOrderDB::DoTradeOrderFrame5(TTradeOrderFrame5Output *pOut)
{
#ifdef DEBUG
	cout << "<<< TOF5" << endl;
#endif

	// rollback the transaction we are inside
	rollbackTransaction();
	pOut->status = CBaseTxnErr::ROLLBACK;

#ifdef DEBUG
	cout << "- Trade Order Frame 5 (output)" << endl <<
			"-- status: " << pOut->status << endl;
	cout << ">>> TOF5" << endl;
#endif
}