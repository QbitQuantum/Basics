// Call Trade Lookup Frame 4
void CTradeLookupDB::DoTradeLookupFrame4(const TTradeLookupFrame4Input *pIn,
		TTradeLookupFrame4Output *pOut)
{
#ifdef DEBUG
	pthread_t pid = pthread_self();
	cout << pid << " <<< TLF4" << endl;
	cout << pid << " - Trade Lookup Frame 4 (input)" << endl <<
			pid << " -- acct_id: " << pIn->acct_id << endl <<
			pid << " -- trade_dts: " << pIn->trade_dts.year << "-" <<
					pIn->trade_dts.month << "-" << pIn->trade_dts.day <<
					" " << pIn->trade_dts.hour << ":" <<
					pIn->trade_dts.minute << ":" <<
					pIn->trade_dts.second << endl;
#endif //DEBUG

	startTransaction();
	// Isolation level required by Clause 7.4.1.3
	setReadCommitted();
	execute(pIn, pOut);
	commitTransaction();

#ifdef DEBUG
	cout << pid << " - Trade Lookup Frame 4 (output)" << endl <<
			pid << " -- holding_history_id[0]: " <<
					pOut->trade_info[0].holding_history_id << endl <<
			pid << " -- holding_history_trade_id[0]: " <<
					pOut->trade_info[0].holding_history_trade_id << endl <<
			pid << " -- quantity_before[0]: " <<
					pOut->trade_info[0].quantity_before << endl <<
			pid << " -- quantity_after[0]: " <<
					pOut->trade_info[0].quantity_after << endl <<
			pid << " -- num_found: " << pOut->num_found << endl <<
			pid << " -- trade_id: " << pOut->trade_id << endl;
	cout << pid << " >>> TLF4" << endl;
#endif //DEBUG
}