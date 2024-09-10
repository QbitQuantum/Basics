int main(int argc, char **argv)
{
   int pipes[ 2 ];
   int new_argc;
   const char** new_argv;
   char helper_num[ 1024 ];
   unsigned i;
   char** orig_environ = NULL;
   char header[ 7 ];
   if( pipe( pipes ) < 0 ) {
      perror( "pipe()" );
      return 1;
   }
   if( argc < 0 || argc > 1000 )
       abort(); /* paranoid */
   set_protection( getpid(), 1 );
   switch( fork()) {
      case -1:
         perror( "fork()" );
         return 1;
      default: /* parent, drop privileges and exec */
         if (setgid(getgid())) {
             perror("setgid()");
             return 1;
         }
         if (setuid(getuid()) || geteuid() != getuid()) {
            perror("setuid()");
            return 1;
         }
         close( pipes[ 0 ] );
         /* read original environment passed by start_kdeinit_wrapper */
         if( read( 0, header, 7 ) == 7 && strncmp( header, "environ", 7 ) == 0 ) {
             unsigned count;
             if( read( 0, &count, sizeof( unsigned )) == sizeof( unsigned )
                 && count && count < (1<<16)) {
                 char** env = malloc(( count + 1 ) * sizeof( char* ));
                 int ok = 1;
                 for( i = 0;
                      i < count && ok;
                      ++i ) {
                     unsigned len;
                     if( read( 0, &len, sizeof( unsigned )) == sizeof( unsigned )
                         && len && len < (1<<12)) {
                         env[ i ] = malloc( len + 1 );
                         if( (unsigned) read( 0, env[ i ], len ) == len ) {
                             env[ i ][ len ] = '\0';
                         } else {
                             ok = 0;
                         }
                     }
                 }
                 if( ok ) {
                   env[ i ] = NULL;
                   orig_environ = env;
                 }
             }
         }
         if(argc == 0)
            return 1;
         new_argc = argc + 2;
         new_argv = malloc( sizeof( char* ) * ( new_argc + 1 ));
         if( new_argv == NULL )
            return 1;
         new_argv[ 0 ] = EXECUTE;
         new_argv[ 1 ] = "--oom-pipe";
         sprintf( helper_num, "%d", pipes[ 1 ] );
         new_argv[ 2 ] = helper_num;
         for( i = 1;
              i <= (unsigned) argc;
              ++i )
             new_argv[ i + 2 ] = argv[ i ];
         if( orig_environ )
             execve(EXECUTE, (char**)new_argv, orig_environ);
         else
             execv(EXECUTE, (char**)new_argv);
         perror(EXECUTE);
         return 1;
      case 0: /* child, keep privileges and do the privileged work */
         close( pipes[ 1 ] );
         for(;;) {
            pid_t pid = 0;
            int ret = read( pipes[ 0 ], &pid, sizeof( pid_t ));
            if( ret < 0 && errno == EINTR )
               continue;
            if( ret <= 0 ) /* pipe closed or error, exit */
               _exit(0);
            if( pid != 0 ) {
                if (set_protection( pid, 0 ))
                    kill( pid, SIGUSR1 );
            }
         }
   }
}