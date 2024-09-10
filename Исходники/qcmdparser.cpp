void QCmdParser::ParseDataDomain( QByteArray &data, QString& strInfo, qint8& nIndex )
{
    // data.length( ) >= 4

    qint32 nDomainLen = 4;

    if ( nDomainLen > data.length( ) ) {
        return;
    }

    qint32 nDI = data[ 0 ];
    nDI |= ( data[ 1 ] << 8 );
    nDI |= ( data[ 2 ] << 16 );
    nDI |= ( data[ 3 ] << 24 );

    data.remove( 0, nDomainLen );
    nDomainLen = data.length( );

    strInfo = "";

    switch ( nDI ) {
    case 0x04000300 :
        nIndex = 0;
        break;

    case 0x0400030C : // ÆµÉÁ¹âÃô¿ØÖÆ
        GeLedtIlluminance( data, strInfo );
        nIndex = 1;
        break;

    case 0x04000301 : // ÎÂ¶È
        GetLedTemperature( data, strInfo );
        nIndex = 3;
        break;

    case 0x04000302 : // µÆ¹¤×÷×´Ì¬£¨00 =ÆµÉÁ£»01=ÉÁ¹â£©Ä£Ê½
        GetLedWorkState( data, strInfo );
        nIndex = 4;
        break;

    case 0x04000303 : // ÆµÉÁ´¥·¢·½Ê½£¨00=ÉÏÉýÑØ´¥·¢£»01=ÏÂ½µÑØ´¥·¢£»02=¸úËæÄ£Ê½£©Í¬²½
        GetLedFreqTriggerMode( data, strInfo );
        nIndex = 5;
        break;

    case 0x04000304 : // Êä³öÂö¿í0£¨°Ù·Ö±ÈÏÔÊ¾£©ÆµÉÁÊ±¼ä
        GetLedFreqTime( data, strInfo );
        nIndex = 7;
        break;

    case 0x04000305 : // Êä³öÂö¿í1£¨°Ù·Ö±ÈÏÔÊ¾£©ÉÁ¹âÊ±¼ä
        GetLedFlashTime( data, strInfo );
        nIndex = 8;
        break;

    case 0x04000306 : // Êä³öÂö¿í2£¨°Ù·Ö±ÈÏÔÊ¾£©ÆµÉÁÁÁ¶È
        GetLedFreqBrightness( data, strInfo );
        nIndex = 9;
        break;

    case 0x04000307 : // Êä³öÂö¿í3£¨°Ù·Ö±ÈÏÔÊ¾£©ÉÁ¹âÁÁ¶È
        GetLedFlashBrightness( data, strInfo );
        nIndex = 10;
        break;

    case 0x04000308 : // ÆµÉÁÆµÂÊ
        GetLedFrequency( data, strInfo );
        nIndex = 13;
        break;

    case 0x04000309 : // LEDµÆ¹¤×÷µçÑ¹
        GetLedWorkVoltage( data, strInfo );
        nIndex = 14;
        break;

    case 0x0400030A : // Íâ²¿´¥·¢ÐÅºÅ×´Ì¬£¨00= Õý³££»01 = Òì³££©
        GetLedExternalTriggerSignalState( data, strInfo );
        nIndex = 15;
        break;

    case 0x0400030B : // ÉÁ¹â´¥·¢·½Ê½£¨00=ÉÏÉýÑØ´¥·¢£»01=ÏÂ½µÑØ´¥·¢£»02=¸úËæÄ£Ê½£©Í¬²½
        GetLedFlashTriggerMode( data, strInfo );
        nIndex = 6;
        break;

    case 0x0400030E : // ÆµÉÁ¹âÃô·§Öµ
        GetThreshold( data, strInfo );
        nIndex = 11;
        break;

    case 0x0400030F : // ÉÁ¹â¹âÃô·§Öµ
        GetThreshold( data, strInfo );
        nIndex = 12;
        break;

    case 0x0400030D : // ÉÁ¹â¹âÃô¿ØÖÆ
        GeLedtIlluminance( data, strInfo );
        nIndex = 2;
        break;

    case 0x04000310 : // Ö¡Æµ¿ØÖÆ
        GetFrameFreqControl( data, strInfo );
        nIndex = 16;
        break;
    }
}