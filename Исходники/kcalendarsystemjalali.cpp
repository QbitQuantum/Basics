static SDATE jdn_jalali( long jdn )
{
    static SDATE ret;
    int day, month, year;
    int iYear, iMonth, iDay;
    int depoch;
    int cycle;
    int cyear;
    int ycycle;
    int aux1, aux2;
    int yday;

    day = 1;
    month = 1;
    year = 475;
    depoch = jdn - jalali_jdn( year, month, day );
    cycle = ( int ) ( depoch / 1029983 );
    cyear = depoch % 1029983;
    if( cyear == 1029982 ) {
        ycycle = 2820;
    } else {
        aux1 = cyear / 366;
        aux2 = cyear % 366;
        ycycle = ( ( ( 2134 * aux1 ) + ( 2816 * aux2 ) + 2815 ) / 1028522 ) + aux1 + 1;
    }
    iYear = ycycle + ( 2820 * cycle ) + 474;
    if ( iYear <= 0 ) {
        iYear = iYear - 1;
    }
    year = iYear;
    yday = ( jdn - jalali_jdn( year, month, day ) ) + 1;
    if( yday <= 186 ) {
        iMonth = Ceil( ( yday - 1 ) / 31 );
    } else {
        iMonth = Ceil( ( yday - 7 ) / 30 );
    }
    iMonth++;
    month = iMonth;
    iDay = ( jdn - jalali_jdn( year, month, day ) ) + 1;
    ret.day = iDay;
    ret.mon = iMonth;
    ret.year = iYear;

    return ret;
}