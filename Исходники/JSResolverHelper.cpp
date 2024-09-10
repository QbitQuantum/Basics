QString
JSResolverHelper::readCompressed( const QString& fileName )
{
    return compress( readRaw( fileName ) );
}