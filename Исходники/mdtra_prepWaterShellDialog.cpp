void MDTRA_PrepWaterShellDialog :: exec_on_prep( void )
{
	int streamIndex = sCombo->itemData( sCombo->currentIndex() ).toInt();
	const MDTRA_Stream *pStream = m_pMainWindow->getProject()->fetchStreamByIndex( streamIndex );

	if (!pStream || !pStream->pdb) {
		QMessageBox::warning(this, tr(APPLICATION_TITLE_SMALL), tr("Bad stream(s) selected!"));
		return;
	}

	txtOutput->clear();
	btnRun->setEnabled( false );

	char tempBuf[512];
	int errNo = 0;
	FILE *tempFp = NULL;

	if ( !*m_szTempName )
		tmpnam_s( m_szTempName );

	if ( ( errNo = (int)fopen_s( &tempFp, m_szTempName, "w" ) ) != 0 ) {
		strerror_s( tempBuf, sizeof(tempBuf), errNo );
		QString cmdErr = QString( "* Could not open temp file:\n   %1\n* %2 gave the error message:\n   \"%3\"\n" ).arg( m_szTempName ).arg( s_OSName ).arg( QString::fromLocal8Bit( tempBuf ) );
		txtOutput->appendPlainText( cmdErr );
		btnRun->setEnabled( true );
		if ( tempFp ) 
			fclose( tempFp );
		return;
	}

	int trajectoryMin = 1;
	int trajectoryMax = pStream->files.count();
	if (trajectoryRange->isChecked()) {
		trajectoryMin = MDTRA_MAX( trajectoryMin, sIndex->value() );
		trajectoryMax = MDTRA_MIN( trajectoryMax, eIndex->value());
	}

	// write stream data
	for ( int i = trajectoryMin - 1; i < trajectoryMax; ++i )
		fprintf_s( tempFp, "%s\n", pStream->files.at( i ).toLocal8Bit().data() );

	fclose( tempFp );

	// build command line
	QString cmdName, cmdArgs, cmdOutFile;
#if defined(WIN32)
	cmdName = "./utils/" PREP_PROGRAM_NAME ".exe";
#else
	cmdName = "./utils/" PREP_PROGRAM_NAME;
#endif
	cmdOutFile = txtOutputPDB->text();
#if QT_VERSION >= 0x040700
	if ( cmdOutFile.isEmpty() )
		cmdOutFile = txtOutputPDB->placeholderText();
#endif
	cmdArgs = QString( "-i \"%1\" -o \"%2\"" ).arg( m_szTempName ).arg( cmdOutFile );

	QString cmdReport = QString( "** Executing...\n** Command: %1\n** Parameters: %2\n" ).arg( cmdName ).arg( cmdArgs );
	txtOutput->appendPlainText( cmdReport );

	// execute prep program
	m_pPipe = new MDTRA_Pipe( cmdName, cmdArgs, txtOutput );
	if ( m_pPipe ) {
		if ( m_pPipe->exec() ) {
			if ( m_bInterrupt )
				txtOutput->appendPlainText( QString( "** Interrupted by user.\n" ) );
			else
				txtOutput->appendPlainText( QString( "** Finished!\n" ) );
		}
		delete m_pPipe;
		m_pPipe = NULL;
	}

	m_bInterrupt = false;

#if defined(WIN32)
	_unlink( m_szTempName );
#else
	unlink( m_szTempName );
#endif
	btnRun->setEnabled( true );
}