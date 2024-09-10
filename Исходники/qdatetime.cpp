QString QTime::toString() const
{
    QString buf;
    buf.sprintf( "%.2d:%.2d:%.2d", hour(), minute(), second() );
    return buf;
}