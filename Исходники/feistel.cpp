static int strHex2Digit( std::string &strHex )
{
    int iLength = strHex.length();
    if( iLength % 2 != 0 )
        return -1;
    
    std::string strTemp;
    char        chDigit;
    
    int iLoop = iLength / 2;
    for( int i = 0; i < iLoop; i++ )
    {
        if( strHex[ i * 2 ] >= 'a' )    // 输入的十六进制串需要是小写字母
            chDigit = strHex[ i * 2 ] - 'a' + 10;
        else
            chDigit = strHex[ i * 2 ] - '0';
        
        chDigit *= 16;
        
        if( strHex[ i * 2 + 1 ] >= 'a' )    // 输入的十六进制串需要是小写字母
            chDigit += strHex[ i * 2 + 1 ] - 'a' + 10;
        else
            chDigit += strHex[ i * 2 + 1 ] - '0';
        
        strTemp.append( 1, chDigit );
    }
    
    strHex.swap( strTemp );
    return 0;
}