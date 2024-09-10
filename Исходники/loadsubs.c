ULONG SetupTempFiles( INSTANCE   *ulpInstance,
                      ULONG      ulParam1 )


{

  ULONG ulrc;

  CHAR  TempPath[ CCHMAXPATH ]; // holds path for temp files


  /**********************************************
  * Query the default path to place temp files and
  * pass it on to the IO Proc
  **********************************************/

  ulrc = mciQuerySysValue( MSV_WORKPATH, TempPath );

  if ( !ulrc )
     {
     return (MCIERR_INI_FILE);
     }

  /*****************************************************
  * This message illustrates the use of mmioSendMessage:
  * we are asking the IO Proc that we have loaded to
  * make all subsequent changes temporary (i.e. if no
  * save message is sent, then the file will remain in
  * the original condition.
  *****************************************************/

  ulrc = mmioSendMessage( ulpInstance->hmmio,
                          MMIOM_TEMPCHANGE,
                          ( LONG ) TempPath,
                          0 );
  if (ulrc)
     {
     /* Use mmioGetLastError to get additional detail about the error */

     ulrc = mmioGetLastError( ulpInstance->hmmio );

     /* Cannot write means that the disk is full */

     if (ulrc == MMIOERR_CANNOTWRITE )
        {
        return MCIERR_TARGET_DEVICE_FULL;
        }
     else
        {
        return ( ulrc );
        }

     } /* if there is an error */

  /* Flag to indicate that temporary changes are active */

  ulpInstance->ulUsingTemp = MCI_TRUE;

  return ( ulrc );


} /* SetupTempFiles */