static KWBoolean client( const time_t exitTime,
                       const char *hotUser,
                       const BPS hotBPS,
                       const int hotHandle,
                       const KWBoolean runUUXQT )
{

   CONN_STATE s_state = CONN_INITIALIZE;
   CONN_STATE old_state = CONN_EXIT;

   KWBoolean contacted = KWFalse;
   KWBoolean needUUXQT = KWFalse;

   char sendGrade = ALL_GRADES;

/*--------------------------------------------------------------------*/
/*                      Trap missing modem entry                      */
/*--------------------------------------------------------------------*/

   if ( E_inmodem == NULL )
   {
      printmsg(0,"No modem specified in configuration file or command line");
      panic();
   }

   if (!getmodem(E_inmodem))  /* Initialize modem configuration     */
      panic();                /* Avoid loop if bad modem name       */

   if ( ! IsNetwork() &&
        ( hotUser == NULL ) &&
        (hotHandle == -1 ) &&
        ! suspend_init(M_device))
   {

#ifdef WIN32
      if (!isWinNT())
      {
         printmsg(0,"Unable to set up pipe for suspending; "
                    "may be unsupported in this environment (use NT for modem sharing).");
      }
      else
#endif
      /* else under WIN32, otherwise unconditional */
      {
         printmsg(0,"Unable to set up pipe for suspending; "
                    "is another UUCICO running?" );
         panic();
      }
   }

   while (s_state != CONN_EXIT )
   {
      printmsg(s_state == old_state ? 10 : 4 ,
               "S state = %c", s_state);
      old_state = s_state;

      switch (s_state)
      {
         case CONN_INITIALIZE:
            if (( hotUser == NULL ) && (hotHandle == -1 ))
               s_state = CONN_ANSWER;
            else
               s_state = CONN_HOTMODEM;
            break;

         case CONN_WAIT:
#if !defined(__TURBOC__) || defined(BIT32ENV)
            setTitle("Port %s suspended", M_device);
           s_state = suspend_wait();
#else
           panic();                 /* Why are we here?!           */
#endif
           break;

         case CONN_ANSWER:
            setTitle("Monitoring port %s", M_device);
            s_state = callin( exitTime );
            break;

         case CONN_HOTMODEM:
            s_state = callhot( hotBPS, hotHandle );
            break;

         case CONN_HOTLOGIN:
            if ( hotUser == NULL )        /* User specified to login? */
               s_state = CONN_LOGIN;      /* No --> Process normally  */
            else if ( loginbypass( hotUser ) )
               s_state = CONN_INITSTAT;
            else
               s_state = CONN_DROPLINE;
            break;

         case CONN_LOGIN:
            setTitle("Processing login on %s",
                      M_device );
            if ( login( ) )
               s_state = CONN_INITSTAT;
            else
               s_state = CONN_DROPLINE;
            break;

         case CONN_INITSTAT:
            HostStatus();
            s_state = CONN_PROTOCOL;
            break;

         case CONN_PROTOCOL:
            setTitle("Establishing connection on %s",
                      M_device);
            s_state = startup_client(&sendGrade);
            break;

         case CONN_CLIENT:
            contacted = KWTrue;
            if (bflag[F_MULTITASK])
               dcupdate();

            setTitle("%s connected to %s",
                      securep->myname,
                      hostp->via,
                      M_device);
            s_state = process( POLL_PASSIVE, sendGrade );
            break;

         case CONN_TERMINATE:
            s_state = sysend();
            if ( hostp != NULL )
            {
               dcstats();
               needUUXQT = KWTrue;
            }
            break;

         case CONN_DROPLINE:
            shutDown();
            if ( locked )     /* Cause could get here w/o
                                 locking                    */
               UnlockSystem();
            s_state = CONN_CLEANUP;
            break;

         case CONN_CLEANUP:
            if ( runUUXQT && needUUXQT )
               s_state = CONN_UUXQT;
            else
               s_state = CONN_EXIT;
            break;

         case CONN_UUXQT:
            {
               char buf[100];
               sprintf( buf, "-s %s -x %d", rmtname, debuglevel );
               copylog();
               execute( "uuxqt", buf, NULL, NULL, KWFalse, KWFalse );
               openlog(NULL);
            }
            needUUXQT = KWFalse;
            s_state = CONN_EXIT;
            break;

         case CONN_EXIT:
            break;

         default:
            printmsg(0,"dcpmain: Unknown slave state = %c",s_state );
            panic();
            break;

      } /* switch */

      if ( terminate_processing )
         s_state = CONN_EXIT;

   } /* while */

   return contacted;

} /* client */