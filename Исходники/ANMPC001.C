 void ParseParms( int argc, char *argv[] )
  {
    int     j = 1 ;
    char TempText[80];

    CallCount   = 1;
    Iterations  = 1;
    Delay       = 0; 

    while ( j < argc )  {
       if ( strchr ( "/-(", argv[j][0] ) ) { /* looks like an option  */
          argv[j] = strupr ( argv[j] );             
          switch ( argv[j][1] )  {
            case '?' :                          /* /?:HELP               */
            case 'H' :                          /* /H:                   */
              SayHelp();          
              break;            
          case 'I' :                         /* /I:iterations         */
             Iterations = atoi ( &argv[j][3] );
             if( ( Iterations < 0 ) || ( Iterations  > 32000 ) ) {
                sprintf(TempText,"Iterations out of range 0 used instead of %s",
                                                                     &argv[j][3]);
                Info(TempText);                                                         
                Iterations = 0;
             } else {
                sprintf(TempText,"Iterations changed to %s",&argv[j][3]);
                Info(TempText);                                                         
             } /* endif */
             Unattended = 1;
             break;
          case 'D' :                         /* /D:Delay              */
             Delay = atof ( &argv[j][3] );
             Delay = Delay * 400; /* Make it a reasonable value */
             break;
          case 'S' :                         /* /S:Server             */
             strcpy( EciBlock.eci_system_name, &argv[j][3]);
             sprintf(TempText,"Server Selected = %s",EciBlock.eci_system_name);
             Info(TempText);                                                         
             break;
          case 'U' :                         /* /U:UserID             */
             strcpy( EciBlock.eci_userid, &argv[j][3]);
             sprintf(TempText,"User ID Selected = %s",EciBlock.eci_userid);
             Info(TempText);                                                         
             break;
          case 'P' :                         /* /P:Password           */
             strcpy( EciBlock.eci_password, &argv[j][3]);
             sprintf(TempText,"Password Supplied = %s",EciBlock.eci_password);
             Info(TempText);                                                         
             break;
          default :
             sprintf(TempText,"Ignoring Parameter %s",&argv[j][0]);
             Info(TempText);                                                         
             break;
          } /* endswitch */
       }
     else
       {
         sprintf(TempText,"Parameters must begin with a /=");
         Info(TempText);                                                         
       }
     j++;
  } /* endwhile */
 
 }