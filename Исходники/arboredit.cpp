LPTSTR CArborEdit::FloatToString(LPTSTR buff,double r)
{
	_TCHAR *buffer;
	LPTSTR startbuffptr;
	int dec,sign;  // must use static, don't assume SS==DS
	int i;

	startbuffptr = buff;

	if (EditStyleIs(EDIT_CURRENCY))
	{
		buffer = fcvt((double)r, m_iCurDigits, &dec, &sign);
		*buff++ = m_cCurrency1;
		if( m_cCurrency2 != ' ') *buff++ = m_cCurrency2;
		// copy the negative sign if less than zero
		if (sign) *buff++ = '-';

		if( dec <= 0 ) *buff++ = '0'; 
		// copy the non-fractional part before the decimal place
		for(i=0; i<dec; i++)
		{
			if( ((dec-i) % 3 ) == 0 && (i !=0 ) ) *buff++ = m_cThousand;
			*buff++ = *buffer++;
		}
		// copy the decimal point into the string 
		*buff++ =  m_cDecimal;
		if ( dec < 0 )
			for( i = 1; i <=  m_iCurDigits &&  i <= (dec * (-1)); *buff++ = '0', i++ );
	}
	else if(EditStyleIs(EDIT_FLOAT))
	{
		buffer = fcvt((double)r, m_iNumberOfDigits, &dec, &sign);
		// copy the negative sign if less than zero
		if (sign) *buff++ = '-';
		if( dec <= 0 ) *buff++ = '0'; 
		// copy the non-fractional part before the decimal place
		for(i=0; i<dec; *buff++ = *buffer++, i++);
		// copy the decimal point into the string 
		*buff++ =  '.';

		if ( dec < 0 )
			for( i = 1; i <= m_iNumberOfDigits &&  i <= (dec * (-1)); *buff++ = '0', i++ );
	}
	else 	 
		return buff;
 
	*buff = '\0';   // don't assume NULL termination
	// copy the fractional part after the decimal place
	lstrcat(buff,buffer);
	buff = startbuffptr;
	return startbuffptr;
}