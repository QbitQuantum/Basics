// Call Customer Position Frame 2
void CCustomerPositionDB::DoCustomerPositionFrame2(
		const TCustomerPositionFrame2Input *pIn,
		TCustomerPositionFrame2Output *pOut)
{
#ifdef DEBUG
	m_coutLock.lock();
	cout << "<<< CPF2" << endl;
	cout << "- Customer Position Frame 2 (input)" << endl <<
			"-- cust_id: " << pIn->acct_id << endl;
	m_coutLock.unlock();
#endif // DEBUG

	execute(pIn, pOut);
	commitTransaction();

#ifdef DEBUG
	m_coutLock.lock();
	cout << "- Customer Position Frame 2 (output)" << endl <<
			"-- hist_len: " << pOut->hist_len << endl;
	for (int i = 0; i < pOut->hist_len; i++) {
		cout << "-- trade_id[" << i << "]: " << pOut->trade_id[i] << endl <<
				"-- symbol[" << i << "]: " << pOut->symbol[i] << endl <<
				"-- qty[" << i << "]: " << pOut->qty[i] << endl <<
				"-- trade_status[" << i << "]: " << pOut->trade_status[i] <<
						endl <<
				"-- hist_dts[" << i << "]: " <<
						pOut->hist_dts[i].year << "-" <<
						pOut->hist_dts[i].month << "-" <<
						pOut->hist_dts[i].day << " " <<
						pOut->hist_dts[i].hour << ":" <<
						pOut->hist_dts[i].minute << ":" <<
						pOut->hist_dts[i].second << endl;
	}
	cout << ">>> CPF2" << endl;
	m_coutLock.unlock();
#endif // DEBUG
}