char *MYRTLEXP StrCase( char *str,msCaseTypes type )
  {  int n;

     if ( !str || *str == 0 ) return str;

     switch( type ){
       case      mscLower: StrLwr( str ); break;
       case      mscUpper: StrUpr( str ); break;
       case mscCapitalize: StrLwr( str );
                           str[0] = ToUpper(str[0]);
                        break;
       case    mscUpLower: for ( n = 0; str[n]; n++ )
                             if ( isLower(str[n]) ) return str;
                           return StrCase( str,mscLower );
       case    mscLoUpper: for ( n = 0; str[n]; n++ )
                             if ( isUpper(str[n]) ) return str;
                           return StrCase( str,mscUpper );
       case     mscInvert: for ( n = 0; str[n]; n++ )
                             if ( isUpper(str[n]) )
                               str[n] = ToLower(str[n]);
                              else
                               str[n] = ToUpper(str[n]);
                        break;
     }
 return str;
}