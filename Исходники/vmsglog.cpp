static bool parseFortranId( WString &str, unsigned j, char *help ) {

    char        groupid[2];
    char        num[50];
    char        *table;
    unsigned    id;
    unsigned    i;
    bool        ret;

    ret = TRUE;
    if( isalpha( str[j] ) && isalpha( str[j+1] ) && str[j+2] == '-' ) {
        groupid[0] = str[j];
        groupid[1] = str[j+1];
        j += 3;
    } else {
        ret = FALSE;
    }
    if( !isdigit( str[j] ) ) ret = FALSE;
    if( ret ) {
        i=0;
        while( isdigit( str[j] ) ) {
            num[i] = str[j];
            j++;
            i++;
        }
        num[i] = '\0';
        id = GROUP_INCREMENT;
        table = fortranGrpCodes;
        for( ;; ) {
            if( table[0] == '\0' && table[1] == '\0' ) {
                ret = FALSE;
                break;
            }
            if( groupid[0] == table[0] && groupid[1] == table[1] ) {
                id += atoi( num );
                ltoa( id, help, 10 );
                break;
            }
            id += GROUP_INCREMENT;
            table += 2;
        }
    }
    return( ret );
}