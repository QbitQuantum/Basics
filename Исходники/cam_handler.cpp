bool CamHandler::service( HttpRequest& request, HttpResponse& response )
{
    if ( request.getPath() != "/jpg-image" )
        return false;

    QString data = QString::fromAscii( request.getBody() );
    QRegExp re( "(\\w{1,})\\s{0,}=\\s{0,}(-{0,1}\\d{1,})" );
    int pos = 0;
    while ( ( pos = re.indexIn( data, pos ) ) != -1 )
    {
        QString key   = re.cap( 1 );
        QString value = re.cap( 2 );
        pos += re.matchedLength();
        if ( key == "quality" )
        {
            pd->quality = value.toInt();
        }
    }
    
    QImage image = pd->image();

    QBuffer buffer( &pd->data );
    QSize sz = image.size();
    buffer.open(QIODevice::WriteOnly);
    bool res = image.save( &buffer, "JPG", pd->quality );

    response.setHeader("Content-Type", "image/JPG");
    response.write( pd->data, true );

    Sleep::msleep( 100 );

    return true;
}