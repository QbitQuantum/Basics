QByteArray QProcessResponseThread::GetBody( QByteArray &byStream )
{
    return byStream.right( byStream.length( ) - Protocol::nHeadLength );
}