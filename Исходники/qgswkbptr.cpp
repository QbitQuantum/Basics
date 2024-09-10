QgsWkbPtr::QgsWkbPtr( QByteArray &wkb )
{
    mP = reinterpret_cast<unsigned char*>( wkb.data() );
    mStart = mP;
    mEnd = mP + wkb.length();
}