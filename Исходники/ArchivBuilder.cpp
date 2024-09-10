void ArchivBuilder::build( QByteArray stubData, QString fileName ) {
    QTemporaryFile tmpArchiv;
    tmpArchiv.open();
    qDebug() << "Will create temporarty file: " << tmpArchiv.fileName();
    QDataStream ds( &tmpArchiv );
    ds.writeRawData( stubData, stubData.size() );

    // Set dataMarker
    for( uint i = 0; i < ArchivBuilder::DATA_MARKER_LENGTH - 1; i++ ) {
        ds.writeRawData( ArchivBuilder::DATA_MARKER + i , 1 );
    }

    // qDebug() << "Marker size: " << ArchivBuilder::DATA_MARKER_LENGTH;
    ds.writeRawData( ArchivBuilder::DATA_MARKER_REPLACECHAR + 0 , 1 );
    QByteArray indexData = _index->compressedIndexData();
    int indexSize = indexData.size();
    qDebug() << "Index size: " << indexSize;
    QString indexSizeString;
    indexSizeString.setNum( indexSize );
    ds.writeRawData( indexSizeString.toAscii(), indexSizeString.toAscii().size() );
    ds.writeRawData( "\n", 1 );
    // qDebug() << "Wrote size string: " << indexSizeString.toAscii();
    ds.writeRawData( indexData, indexData.size() );
    QByteArray archivData = _data->data();
    ds.writeRawData( archivData, archivData.size() );
    qDebug() << "Wrote data section of size: " <<  archivData.size();

    if ( QFileInfo( fileName ).exists() ) {
        QFile( fileName ).remove();
        // QFile( fileName ).rename( QString( "%1_back_%2" ).arg( fileName ).arg( RedBullPlayer::Tools::UuidCreator::create() ) );
    }

    if(  tmpArchiv.copy( fileName ) ) {
        qDebug() << "Created Archive at: " << QFileInfo( fileName ) .absoluteFilePath();
    } else {
        qWarning() << "Could not copy archiv file to: " <<  QFileInfo( fileName ) .absoluteFilePath();
    }

    qDebug() << "Will create temporarty file: " << tmpArchiv.fileName();
    tmpArchiv.close();
    tmpArchiv.remove();
}