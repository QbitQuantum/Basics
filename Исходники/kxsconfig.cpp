//---------------------------------------------------------------------------
void KXSConfigDialog::slotPreviewExited(KProcess *)
{
    if ( mKilled ) {
	mKilled = false;
	mPreviewProc->clearArguments();
	TQString saver;
	saver.sprintf( "%s -window-id 0x%lX", mFilename.latin1(), long(mPreview->winId()) );
	saver += command();
	kdDebug() << "Command: " <<  saver << endl;

	unsigned int i = 0;
	TQString word;
	saver = saver.stripWhiteSpace();
	while ( !saver[i].isSpace() ) word += saver[i++];
	//work around a KStandarDirs::findExe() "feature" where it looks in $KDEDIR/bin first no matter what and sometimes finds the wrong executable
	TQFileInfo checkExe;
	TQString saverdir = TQString("%1/%2").tqarg(XSCREENSAVER_HACKS_DIR).tqarg(word);
	TQString path;
	checkExe.setFile(saverdir);
	if (checkExe.exists() && checkExe.isExecutable() && checkExe.isFile())
	{
		path = saverdir;
	}
	if (!path.isEmpty()) {
	    (*mPreviewProc) << path;

	    bool inQuotes = false;
	    while ( i < saver.length() ) {
		word = "";
		while ( saver[i].isSpace() && i < saver.length() ) i++;
		while ( (!saver[i].isSpace() || inQuotes) && i < saver.length() ) {
		    if ( saver[i] == '\"' ) {
			inQuotes = !inQuotes;
		    } else {
			word += saver[i];
		    }
		    i++;
		}
		if (!word.isEmpty()) {
		    (*mPreviewProc) << word;
		}
	    }

	    mPreviewProc->start();
	}
    } else {
	// stops us from spawning the hack really fast, but still not the best
	TQString path = KStandardDirs::findExe(mFilename, XSCREENSAVER_HACKS_DIR);
	if ( TQFile::exists(path) ) {
	    mKilled = true;
	    slotChanged();
	}
    }
}