void DeepSkyObject::setCatalog( const QString &cat ) {
    if ( cat.toUpper() == "M" ) Catalog = (unsigned char)CAT_MESSIER;
    else if ( cat.toUpper() == "NGC" ) Catalog = (unsigned char)CAT_NGC;
    else if ( cat.toUpper() == "IC"  ) Catalog = (unsigned char)CAT_IC;
    else Catalog = (unsigned char)CAT_UNKNOWN;
}