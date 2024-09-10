/**
 * This operator outputs a CST object to the screen
 **/
ostream& operator <<(	ostream& cout, 
						const CST& a)
{
	if (&a)
	{
		char* tmptm = new char[100];
		asctime_s(tmptm, 100, &a.SellTime);

		cout << "############################################################" << endl
			 << "Ticket Info" << endl
			 << "------------------------------------------------------------" << endl
			 << "Paydesk ID: ";

		cout.fill('0');
		cout.width(8);

		cout << a.PaydeskID << endl
			 << "Ticket ID: ";

		cout.fill('0');
		cout.width(8);

		cout << a.TicketID << endl
			 << "SellTime: " 
			 << tmptm << endl
		     << a.Rt
		     << "Passenger: " 
			 << a.Passenger << endl
			 << "############################################################" << endl;
		return cout;
	}
	else
	{
		cout << "############################################################" << endl
			 << "There is no such a ticket" << endl
			 << "############################################################" << endl;
		return cout;
	}
}