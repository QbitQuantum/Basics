String::String( const double& val_ ) {

    int          run1      ;
    char        *char_value;
    char        *tmp       ;
    char        *dummy     ;
    BooleanType  dot       ;

    const int precision = 16;

    dot = BT_FALSE;

    char_value = (char*)malloc(MAX_LENGTH_STRING*sizeof(char));
    tmp        = (char*)malloc(MAX_LENGTH_STRING*sizeof(char));

    dummy = gcvt( val_ , precision , char_value );

    length = 0;
    run1 = 0;

    while( char_value[run1] == '1' || char_value[run1] == '0' ||
            char_value[run1] == '3' || char_value[run1] == '2' ||
            char_value[run1] == '5' || char_value[run1] == '4' ||
            char_value[run1] == '7' || char_value[run1] == '6' ||
            char_value[run1] == '9' || char_value[run1] == '8' ||
            char_value[run1] == '.' || char_value[run1] == 'e' ||
            char_value[run1] == 'n' || char_value[run1] == 'a' ||
            char_value[run1] == 'i' || char_value[run1] == 'n' ||
            char_value[run1] == 'f' || char_value[run1] == ' ' ||
            char_value[run1] == '+' || char_value[run1] == '-' ) {

        if( dot == BT_FALSE && char_value[run1] == 'e' ) {
            tmp[length] = '.';
            length++;
            dot = BT_TRUE;
        }
        tmp[length] = char_value[run1];
        length++;
        if( char_value[run1] == '.' ) dot = BT_TRUE;
        run1++;
    }
    free(char_value);

    if( dot == BT_FALSE ) {
        tmp[length] = '.';
        length++;
    }

    tmp[length] = '\0';
    length++;

    name = new char[length];
    for( run1 = 0; run1 < (int) length; run1++ )
        name[run1] = tmp[run1];

    free(tmp);
}