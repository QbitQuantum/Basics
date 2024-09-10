void AotGraphan::analyzeString( const std::string & str, boost::ptr_vector<Unit> & units ) {
	setupRml();

	try {
		CGraphmatFile file;

		if( !file.LoadDicts() ) { // Загружаем словари
			throw std::logic_error( file.GetLastError() );
		}

		if( !file.LoadStringToGraphan( str ) ) { // Загружаем файл
			throw std::logic_error( file.GetLastError() );
		}

		for( const CGraLine & line : file.GetUnits() ) {
			units.push_back( new Unit( line.GetToken(), line.GetTokenLength(), line.GetInputOffset(), line.IsWordOrNumberOrAbbr() ? Unit::WORD : line.IsPunct() ? Unit::PUNCT : Unit::UNKNOWN ) );
		}
	} catch ( const std::exception & e ) {
		throw e;
	} catch ( const CExpc & e ) {
		throw std::logic_error( "Couldn't init morphology: " + e.m_strCause );
	} catch (...) {
		throw std::logic_error( "Couldn't init morphology due to unknown error" );
	}
}