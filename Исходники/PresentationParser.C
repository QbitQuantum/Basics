SetOf<Word>
PresentationParser::parseRelatorList(const VectorOf<Chars>& names,Chars& errMesg)
{
  genNames = names;

  SetOf<Word> result;

  if ( curToken == INIT ) getToken();

  while ( atStartOfWord() ) {
	 Word u = parseWord( names, errMesg );
	 if ( errMesg.length() > 0 ) {
		return result;
	 }

	 if ( curToken != EQUALS )
		result.adjoinElement( u.cyclicallyReduce() );
	 else {
		while ( curToken == EQUALS ) {
		  getToken();
		  Word v = parseWord( names, errMesg );
		  if ( errMesg.length() > 0 ) {
			 return result;
		  }
		  result.adjoinElement( ((Word)(u * v.inverse())).cyclicallyReduce() );
		}
	 }

	 if ( curToken == COMMA ) {
		getToken();
      if ( !atStartOfWord() ) {
		  parseError("Expected a word here");
		  errMesg = parseErrorMessage;
		  return result;
		}
	 }
  }

  return result;
}