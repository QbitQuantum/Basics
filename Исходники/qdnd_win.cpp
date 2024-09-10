/***********************************************
        QDropEvent
************************************************/
QByteArray QDropEvent::encodedData( const char * format ) const
{
#ifdef DEBUG_QDND_WIN
    qDebug( "QDropEvent::encodedData ( %s )", format );
#endif

    QByteArray ba;
    /* Currently we only support TYMED_HGLOBAL ... */
    FORMATETC fmtMemory = { 0,
                            NULL,
                            DVASPECT_CONTENT,
                            -1,
                            TYMED_HGLOBAL };
    STGMEDIUM stm;

    if ( !pIDataObject ) {
        return ba;
    }

    QPtrList<QWindowsMime> all = QWindowsMime::all();
    for ( QWindowsMime * c = all.first(); c ; c = all.next() ) {
        int cf = c->cfFor( format );
        if ( c->canConvert( format, cf ) ) {
            fmtMemory.cfFormat = cf;
            if ( pIDataObject->QueryGetData( &fmtMemory ) == S_OK ) {
                HRESULT hr = pIDataObject->GetData( &fmtMemory, &stm );
                if ( ( hr != S_OK ) || ( !stm.hGlobal ) )
                    continue;
                QByteArray data;
                QBuffer buf ( data );
                buf.open( IO_WriteOnly );
                buf.writeBlock ( ( char* ) GlobalLock( stm.hGlobal ), GlobalSize ( stm.hGlobal ) );
                buf.close();

                GlobalUnlock ( stm.hGlobal );
                ReleaseStgMedium( &stm );

                ba = c->convertToMime( data, format, cf );
                ReleaseStgMedium( &stm );
                return ba;
            }
        }
    }
    return ba;
}