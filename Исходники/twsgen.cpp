bool gen_csv()
{
	TwsXml file;
	if( ! file.openFile(filep) ) {
		return false;
	}

	if( max_expiryp != NULL ) {
		struct tm tm_tmp;
		memset(&tm_tmp, 0, sizeof(struct tm));
		if( ib_strptime( &tm_tmp, max_expiryp ) == -1 ) {
			fprintf( stderr, "error, "
				"max-expiry must be IB's format YYYYMMDD.\n" );
			return false;
		}
		DEBUG_PRINTF("skipping expiries newer than: '%s'", max_expiryp );
	}

	xmlNodePtr xn;
	int count_docs = 0;
	while( (xn = file.nextXmlNode()) != NULL ) {
		count_docs++;
		PacketHistData *phd = PacketHistData::fromXml( xn );

		if( max_expiryp != NULL ) {
			const std::string &expiry = phd->getRequest().ibContract.expiry;
			if( !expiry.empty() && strcmp(max_expiryp, expiry.c_str() ) < 0 ) {
				goto cont;
			}
		}

		if( !no_convp ) {
			phd->dump( true /* printFormatDates */);
		} else {
			phd->dumpXml();
		}
cont:
		delete phd;
	}
	fprintf( stderr, "notice, %d xml docs parsed from file '%s'\n",
		count_docs, filep );

	return true;
}