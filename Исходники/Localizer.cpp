void clLocalizer::SetLocale( const LString& LocaleName )
{
	guard( "%s", LocaleName.c_str() );

	ClearLocalization();

	FLocaleName = LocaleName;

	const LString FileName( FLocalePath + "/Localizer-" + LocaleName + ".txt" );

	if ( Env->FileSystem->FileExists( FileName ) )
	{
		Env->Logger->LogP( L_NOTICE, "Reading locale from %s", FileName.c_str() );

		iIStream* Stream = Env->FileSystem->CreateFileReader( FileName );

		while ( !Stream->Eof() )
		{
			LString Line = Stream->ReadLine();

			size_t SepPos = Line.find( "~" );

			FATAL( SepPos == Line.npos, "Invalid locale translation file format: missing ~" );

			LString Text( Line.substr( 0, SepPos ) );
			LString Translation( Line.substr( SepPos + 1, Line.length() - SepPos - 1 ) );

			FTranslations[ Text ] = Translation;
		}

		delete( Stream );
	}
	else
	{
		Env->Logger->LogP( L_NOTICE, "Locale %s not found", FileName.c_str() );
	}

	this->SendAsync( L_EVENT_LOCALE_CHANGED, LEventArgs(), false );

	unguard();
}