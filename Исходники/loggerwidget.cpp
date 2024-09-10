void LoggerWidget::save()
{
    QString file = KFileDialog::getSaveFileName( QString::null, QString::null, this );
    if ( !file.isNull() ) {
        QFile f( file );
        if ( f.exists() ) {
            int result = KMessageBox::warningContinueCancel( this,
		   i18n( "Log file exists, overwrite?" ),
                   i18n( "KDat: Save Log" ), 
                   i18n("&Overwrite"));
            if (result != KMessageBox::Continue)
                return;
        }
        if ( f.open( IO_WriteOnly ) ) {
            QCString line;
            for ( int i = 0; i < _mle->numLines(); i++ ) {
                line = _mle->textLine( i ).utf8();
                f.writeBlock( line, line.length() );
                f.writeBlock( "\n", 1 );
            }
            f.close();
        }
    }
}