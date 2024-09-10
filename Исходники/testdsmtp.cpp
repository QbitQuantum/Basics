void TestDSMTP::html_test()
{
	DSMTP mail;
	DSMTP::ERRNO code;
	DURL server;
	DStringList transaction, charlist;
	DStringList::const_iterator it;
	int i = 2;

	server.setURL( "smtp://localhost.localdomain:25" );

	mail.setHost ( server );
	mail.setSender ( "root@localhost" );
	mail.addReceiver ( "root@localhost" );
	
	DString buffer = "This is just a simple DLibs test, SMTP part\n\n";
	buffer += utf8chars;
	
	charlist = utf8chars.split( " " );
	DString html = "<!DOCTYPE html>\n<html>\n<body>\n<h1>This is just a simple DLibs test, SMTP part</h1>\n";
	html += "<table>\n";
	html += "<tr>\n";
	for ( it = charlist.begin() ; it != charlist.end() ; ++it )
	{
		if ( ! ( i % 16 ) )
		{
			html += "</tr>\n";
			html += "<tr>\n";
		}
		html += "<td>";
		html += it->toHTML();
		html += "</td>\n";
		i++;
	}

	html += "</tr>\n";
	html += "</table>\n";
	html += "</body>\n</html>";
	mail.setEmail ( "DLibs test", buffer, html );
	code = mail.send();
	
	TEST_ASSERT_MSG( mail.getLastError() == DString::empty(), "Error reported when sending email" )
	TEST_ASSERT_MSG( code == DSMTP::SUCCESS, "Email not sent" )
	
	transaction = mail.getTransactionLog();
	for ( it = transaction.begin() ; it != transaction.end() ; it++ )
	{
		std::cout << *it << std::endl;
	}
}