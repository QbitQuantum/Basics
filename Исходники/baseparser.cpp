void
BaseParser::_parseUsername( std::string & username ) {

	/**
	 * Convert to uppercase.
	 * Append quotation marks.
	 */
	_toUpper( username );
	_quotationMarks( username );
}