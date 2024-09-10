static QString
variantListToString( const QVariantList& variantList )
{
    QStringList result;
    for ( const QVariant& variant : variantList )
        result.append( variantToString( variant ) );
    return '{' + result.join(',') + '}';
}