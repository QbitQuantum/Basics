hashValueType String::hashValue() const

// Summary -----------------------------------------------------------------
//
//      Returns the hash value of a string object.
//
// End ---------------------------------------------------------------------
{
    hashValueType	value = hashValueType(0);

    for( int i = 0; i < len; i++ )
    {
        value ^= theString[i];
        value = _rotl( value, 1 );
    }
    return value;
}