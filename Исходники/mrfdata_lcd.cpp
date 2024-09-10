u_int32_t MrfData_LCD::pos2LCD( const int& p )
{
    // upper line starts with 128, lower one with 192
    u_int32_t value = ( isUpper() ) ? 128 : 192;

    if ( p > 0 && p < 16 ) {
        value += p;
    }

    return value;
}