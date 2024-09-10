bool EppUtil::getTextAsBool( const DOMNode &root )
{
	DOMString str = getText(root);

	unsigned int length = str.length();
	if ( length == 1 && (str.charAt(0) == (XMLCh)'1') )
	{
		return true;
	}
	else if ( length == 4 )
	{
		XMLCh c;

		c = str.charAt(0);
		if ( c != (XMLCh)'t' && c != (XMLCh)'T' )
			return false;

		c = str.charAt(1);
		if ( c != (XMLCh)'r' && c != (XMLCh)'R' )
			return false;

		c = str.charAt(2);
		if ( c != (XMLCh)'u' && c != (XMLCh)'U' )
			return false;

		c = str.charAt(3);
		if ( c != (XMLCh)'e' && c != (XMLCh)'E' )
			return false;

		return true;
	}
	return false;
}