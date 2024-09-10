int SmartCardReader::transmit( )
{
    char tempstr[262];
    char tempstr2[262];
    int index;

    sprintf( tempstr, ">" );
    for( index = 0; index <= SendLen-1  ; index++ )
    {

        sprintf( tempstr, "%s %02X", tempstr, SendBuff[index] );

    }

    sprintf( tempstr, "%s\n", tempstr );

    //DisplayOut( tempstr, BLACK );

    retCode = SCardTransmit(card,
                            NULL,
                            SendBuff,
                            SendLen,
                            NULL,
                            RecvBuff,
                            &RecvLen);

    cout << "buff : " << endl << RecvBuff << endl ;
    cout << "vlen" << endl << RecvLen << endl ;
    if( retCode != SCARD_S_SUCCESS )
    {
        ofLogError( " SCardTransmit Error " ) << getSCardErrorMessage( retCode ) ;
        //DisplayOut( GetScardErrMsg( retCode ), RED );


    }
    else
    {
        ofLogNotice( "transmit was a success!" ) ;
        sprintf( tempstr2, ">" );
        for( index = 0; index <= RecvLen - 1; index++ )
        {

            sprintf( tempstr2, "%s %02X",tempstr2, RecvBuff[index] );

        }
        sprintf( tempstr2, "%s \n", tempstr2 );
        cout << tempstr2 << endl ;


        //DisplayOut( tempstr2, BLACK );


    }

    return retCode;
}