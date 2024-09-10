void KgpgApp::slotFileSave()
{
    TQString filn=Docname.path();
    if (filn.isEmpty()) {
    	slotFileSaveAs();
    	return;
    }
    TQTextCodec*cod=TQTextCodec::codecForName (textEncoding.ascii());
        // slotStatusMsg(i18n("Saving file..."));
    if (!checkEncoding(cod)) {
	KMessageBox::sorry(this,i18n("The document could not been saved, as the selected encoding cannot encode every unicode character in it."));
	return;
    }

    KTempFile tmpfile;
    if (Docname.isLocalFile()) {
    TQFile f(filn);
    if ( !f.open( IO_WriteOnly ) ) {
	KMessageBox::sorry(this,i18n("The document could not be saved, please check your permissions and disk space."));
        return;
    }
    TQTextStream t( &f );
    t.setCodec(cod);
    //t.setEncoding( TQTextStream::Latin1 );
    t << view->editor->text();//.utf8();
    f.close();
    }
    else {
	/*FIXME  use following code:
	 TQFile f( fName );
00983         if ( !f.open( IO_ReadOnly ) )
00984             return;
00985         TQFileInfo info ( f );
00986         smModificationTime = new TQTime( info.lastModified().time() );
00987         TQTextStream t(&f);
00988         t.setEncoding( TQTextStream::Latin1 );
00989         TQString s = t.readLine();
00990         f.close();

*/
	TQTextStream *stream = tmpfile.textStream();
	stream->setCodec(cod);
    	*stream << view->editor->text();//.utf8();
   	tmpfile.close();
	if(!TDEIO::NetAccess::upload(tmpfile.name(), Docname,this)) {
	    KMessageBox::sorry(this,i18n("The document could not be saved, please check your permissions and disk space."));
	    tmpfile.unlink();
            return;
	}
	tmpfile.unlink();
    }

    fileSave->setEnabled(false);
    setCaption(Docname.fileName(),false);
}