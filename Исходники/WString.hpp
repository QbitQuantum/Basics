// Right most number of characters
WString WString::Right ( int iCount ) const
{
    return SubStr ( (int)length () - iCount, iCount );
}