int main( int pArgc, const char** pArgs )
{
   const char* lQueryPtr;
   char  lQuery[4096];
   char  lOp[12];
   char* lPathEnd;
   union semun lNULL;
   int   lLock;        /* Semaphore */
   int   lMemId;       /* Shared memory */
   struct sembuf lSemOp;
   union  semun lArg;

   int          lDuration;
   char         lTrackName[80];
   char         lUser[80];
   unsigned int lChkSum;
   int          lCraft;

   int          lTotalTime;
   int          lNbLap;
   int          lNbPlayer;


   #ifdef _NO_IPC_
 
      gGlobalState.Read();
   #endif


   #ifdef _FAST_CGI_
   while( FCGI_Accept() >= 0 )
   #endif
   {
      lQuery[0] = 0;
      lOp[0]    = 0;

      if( getenv( "DOCUMENT_NAME" ) != NULL )
      {
         if( pArgc >=2 )
         {
            sprintf( lQuery, "=%s", pArgs[1] );
         }

      }
      else
      {
         /* Send the header required by the server in in CGI mode */
         printf("Content-type: text/plain%c%c", 10, 10);


         lQueryPtr = getenv( "QUERY_STRING" );


         if( lQueryPtr != NULL )
         {
            StrMaxCopy( lQuery, lQueryPtr, 4096 );
            UnpadQuery( lQuery );
         }
      }

      #ifndef _FAST_CGI_
         /* Change the local directory */
         lPathEnd = strrchr( pArgs[0], '/' );

         if( lPathEnd != NULL )
         {
            *lPathEnd = 0;
            chdir( pArgs[0] );
         }
      #endif



      sscanf( lQuery, "=%11s", lOp );


      if( !strcmp( lOp, "RESET" ) )
      {
         printf( "RESET OK\n\n" );

         #ifdef _NO_IPC_
            /*
            // gGlobalState.Clear();
            // sleep( 2 );
            // return 0;
            // break;
            */
         #else

            lLock  = semget( IR_SEM_KEY, 1, 0777 );
            lMemId = shmget( IR_SHMEM_KEY, 1 /*sizeof( ISState )*/, 0666 );

            if( lLock != -1 )
            {

               semctl( lLock, 0, IPC_RMID, lNULL );
            }

            if( lMemId != -1 )
            {
               shmctl( lMemId, IPC_RMID, NULL );
            }

         #endif


         #ifdef _FAST_CGI_
            break;
         #endif

      }
      else
      {
         ISState* lState = NULL;

         #ifdef _NO_IPC_
            lState = &gGlobalState;

         #else


            lSemOp.sem_flg = 0;  /*Avoid corruption but must not core-dump SEM_UNDO;  // Risky but prevents dead-lock */
            lSemOp.sem_num  = 0;

            /* First try to create the structure for the first time */
            /* Lock the data struct */
            lLock = semget( IR_SEM_KEY, 1, 0777|IPC_CREAT|IPC_EXCL );

            if( lLock != -1 )
            {
               
               /* Initialize the newly created semaphore */
               lArg.val = 1;
 
               semctl( lLock, 0, SETVAL, lArg );
            }
            else
            {
               lLock = semget( IR_SEM_KEY, 1, 0777 );
            }

            if( lLock == -1 )
            {
               printf( "Unable to get semaphore\n" );
            }
            else
            {
               lSemOp.sem_op   = -1;

               if( semop( lLock, &lSemOp, 1 ) == -1 )
               {
                  printf( "Unable to decrement semaphore\n" );
                  lLock = -1;
               }
               else
               {

                  /* From here we can work safely */

                  lMemId = shmget( IR_SHMEM_KEY, sizeof( ISState ), 0666|IPC_CREAT|IPC_EXCL );

                  if( lMemId != -1 )
                  {
                     lState = (ISState*)shmat( lMemId, NULL, 0 );

                     if( (int)lState == -1 )
                     {
                        lState = NULL;
                     }

                     if( lState == NULL )
                     {
                        printf( "Unable to attach shmem\n" );
                     }
                     else
                     {
                        StateRead( lState );

                     }
                  }
                  else
                  {
                     lMemId = shmget( IR_SHMEM_KEY, sizeof( ISState ), 0666 );

                     if( lMemId == -1 )
                     {
                        printf( "Unable to get shmem\n" );
                     }
                     else
                     {
                        lState = (ISState*)shmat( lMemId, NULL, 0 );

                        if( (int)lState == -1 )
                        {
                           lState = NULL;
                        }

                        if( lState == NULL )
                        {
                           printf( "Unable to attach shmem\n" );
                        }
                     }
                  }
               }
            }

         #endif
   
         if( lState != NULL )
         {
            if( !strcmp( lOp, "BESTLAPS" )  )
            {

               /* Return the score table */
               StatePrintLap( lState, 0 );
            }
            else if( !strcmp( lOp, "BESTLAPS1" )  )
            {
               StatePrintLap( lState, 1 );
            }
            else if( !strcmp( lOp, "BESTLAPS2" )  )
            {
               StatePrintLap( lState, 2 );
            }
            else if( !strcmp( lOp, "BESTTIME1" )  )
            {
               StatePrintRace( lState, 0 );
            }
            else if( !strcmp( lOp, "BESTTIME2" )  )
            {
               StatePrintRace( lState, 1 );
            }
            else if( !strcmp( lOp, "BESTTIME3" )  )
            {
               StatePrintRace( lState, 2 );
            }
            else if( !strcmp( lOp, "BESTTIME4" )  )
            {
               StatePrintRace( lState, 3 );
            }
            else if( !strcmp( lOp, "BESTTIME5" )  )
            {
               StatePrintRace( lState, 4 );
            }
            else if( !strcmp( lOp, "LAPTIME" ) )
            {

               if( sscanf( lQuery, "%*s %d %s %s %u %d", &lDuration, lTrackName, lUser, &lChkSum, &lCraft )==5 )
               {
                  Unpad( lTrackName );
                  Unpad( lUser );
                  Filter( lUser );

                  StateAddLapRecord( lState, lTrackName, lChkSum, lUser, lDuration, lCraft );                  
               }
               printf( "OK\n\n" );
            }
            else if( !strcmp( lOp, "RESULT" ) )
            {
               if( sscanf( lQuery, "%*s %d %s %s %u %d %d %d %d", &lDuration, lTrackName, lUser, &lChkSum, &lCraft, &lTotalTime, &lNbLap, &lNbPlayer )==8 )
               {
                  Unpad( lTrackName );
                  Unpad( lUser );
                  Filter( lUser );

                  StateAddLapRecord( lState, lTrackName, lChkSum, lUser, lDuration, lCraft );
                  StateAddRaceRecord( lState, lTrackName, lChkSum, lUser, lTotalTime, lCraft, lNbLap, lNbPlayer );
               }
               printf( "OK\n\n" );
   
            }
            else if( !strcmp( lOp, "RESET_WEEK" ) )
            {
               StateResetWeekly( lState );
               printf( "RESET_WEEK OK\n\n" );
            }
            else
            {
               printf( "Score Server (c)1997 GrokkSoft inc.\n\n" );
            }
         }

         #ifdef _NO_IPC_
            lState = NULL;
         #else
   
            /* Release lock */
            if( lLock != -1 )
            {
               lSemOp.sem_op   = 1;

               semop( lLock, &lSemOp, 1 );

               /* Release memory */
               if( lState != NULL )
               {
                  shmdt( (char*)lState );
               }
            }
                  
         #endif               
      }
   }

   return 0;
}