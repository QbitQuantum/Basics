double hb_secondsCPU( int n )
{
   double d = 0.0;

#if defined( HB_OS_WIN ) && ! defined( HB_OS_WIN_CE ) && ! defined( HB_OS_UNIX )
   FILETIME Create, Exit, Kernel, User;
#endif

#if defined( HB_OS_OS2 )
   static ULONG s_timer_interval = 0;

   QSGREC ** pBuf;
#endif

   if( ( n < 1 || n > 3 ) && ( n < 11 || n > 13 ) )
      n = 3;

#if defined( HB_OS_UNIX ) && ! defined( HB_OS_VXWORKS )
   {
      struct tms tm;

      times( &tm );

      if( n > 10 )
      {
         n -= 10;
         if( n & 1 )
            d += tm.tms_cutime;
         if( n & 2 )
            d += tm.tms_cstime;
      }
      if( n & 1 )
         d += tm.tms_utime;
      if( n & 2 )
         d += tm.tms_stime;

      /* In POSIX-1996 the CLK_TCK symbol is mentioned as obsolescent */
      #if 0
      d /= CLK_TCK;
      #endif
      d /= ( double ) sysconf( _SC_CLK_TCK );
   }
#else
   if( n > 10 )
      n -= 10;
#if defined( HB_OS_WIN ) && ! defined( HB_OS_WIN_CE )
   if( hb_iswinnt() &&
       GetProcessTimes( GetCurrentProcess(), &Create, &Exit, &Kernel, &User ) )
   {
      if( n & 1 )
      {
         d += ( double ) ( ( ( HB_MAXINT ) User.dwHighDateTime << 32 ) +
                             ( HB_MAXINT ) User.dwLowDateTime );
      }
      if( n & 2 )
      {
         d += ( double ) ( ( ( HB_MAXINT ) Kernel.dwHighDateTime << 32 ) +
                             ( HB_MAXINT ) Kernel.dwLowDateTime );
      }
      d /= 10000000.0;
   }
   else
#elif defined( HB_OS_OS2 )

   if( s_timer_interval == 0 )
      DosQuerySysInfo( QSV_TIMER_INTERVAL, QSV_TIMER_INTERVAL, ( PVOID ) &s_timer_interval, sizeof( ULONG ) );

   pBuf = ( QSGREC ** ) hb_xalloc( BUFSIZE );

   if( pBuf )
   {
#if defined( __GNUC__ )
      APIRET rc = DosQuerySysState( QS_PROCESS, 0L, _getpid(), 0L, pBuf, BUFSIZE );
#else
      APIRET rc = DosQuerySysState( QS_PROCESS, 0L, getpid(), 0L, pBuf, BUFSIZE );
#endif

      if( rc == NO_ERROR )
      {
         QSGREC * pGrec = *pBuf;
         QSPREC * pPrec = ( QSPREC * ) ( ( ULONG ) pGrec + sizeof( QSGREC ) );
         QSTREC * pTrec = pPrec->pThrdRec;

         int i;

         for( i = 0; i < pPrec->cTCB; i++, pTrec++ )
         {
            if( n & 1 )
               d += pTrec->usertime;

            if( n & 2 )
               d += pTrec->systime;
         }

         d = d * 10.0 / s_timer_interval;
      }

      hb_xfree( pBuf );
   }
   else

#endif
   {
      /* TODO: this code is only for DOS and other platforms which cannot
               calculate process time */

      if( n & 1 )
         d = hb_dateSeconds();
   }
#endif
   return d;
}