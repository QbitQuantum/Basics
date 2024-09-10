void ExtractToken( QString & buffer, const QString & string, int & pos, bool & isNumber )
{
	buffer.clear();
	if ( string.isNull() || pos >= string.length() )
		return;

	isNumber = false;
	QChar curr = string[ pos ];
	if ( curr == '-' || curr == '+' || curr.isDigit() )
	{
		if ( curr == '-' || curr == '+' )
			INCBUF();

		if ( !curr.isNull() && curr.isDigit() )
		{
			isNumber = true;
			while ( curr.isDigit() )
				INCBUF();

			if ( curr == '.' )
			{
				INCBUF();
				while ( curr.isDigit() )
					INCBUF();
			}

			if ( !curr.isNull() && curr.toLower() == 'e' )
			{
				INCBUF();
				if ( curr == '-' || curr == '+' )
					INCBUF();

				if ( curr.isNull() || !curr.isDigit() )
					isNumber = false;
				else
					while ( curr.isDigit() )
						INCBUF();
			}
		}
	}

	if ( !isNumber )
	{
		while ( curr != '-' && curr != '+' && !curr.isDigit() && pos < string.length() )
			INCBUF();
	}
}