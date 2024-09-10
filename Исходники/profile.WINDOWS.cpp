/* returns TRUE if a user's environment was loaded; otherwise, FALSE.*/
BOOL
OwnerProfile::environment ( Env &env ) {

    dprintf ( D_FULLDEBUG, "In OwnerProfile::environment()\n" );

    priv_state  priv    = PRIV_UNKNOWN;
    PVOID       penv    = NULL;
    PWSTR       w_penv  = NULL,
                w_tmp   = NULL;
    PSTR        tmp     = NULL;    
    BOOL        created = FALSE,
                ok      = FALSE;

    __try {

        /* we must do the following as the user or Condor */
        priv = set_condor_priv ();

        /* if we are loading the user's profile, then overwrite 
        any existing environment variables with the values in the 
        user's profile (don't inherit anything from the global
        environment, as we will already have that at when we are 
        called) */
        created = CreateEnvironmentBlock ( 
            &penv, 
            user_token_, 
            FALSE ); /* we already have the current process env */
        ASSERT ( penv );

        dprintf ( 
            D_FULLDEBUG, 
            "OwnerProfile::environment: Loading %s while retrieving "
            "%s's environment (last-error = %u)\n",
            created ? "succeeded" : "failed", 
            user_name_,
            GetLastError () );

        if ( !created ) {
            __leave;
        }

        /* fill the environment with the user's environment values */
        dprintf ( D_FULLDEBUG, "Environment:\n" );
        w_penv = (PWSTR)penv;
        while ( '\0' != *w_penv ) { /* read: while not "\0\0' */
            tmp = ProduceAFromW ( w_penv );
            if ( tmp && strlen ( tmp ) > 0 ) {
                dprintf ( D_FULLDEBUG, "%s\n", tmp );
                env.SetEnv ( tmp );
                delete [] tmp;
            }
            w_penv += wcslen ( w_penv ) + 1;
        }

        /* if we've arrived here, then all it well */
        ok = TRUE;

    }
    __finally {

        /* rid ourselves of the user's environment information */
        if ( penv ) {
            if ( !DestroyEnvironmentBlock ( penv ) ) {
                dprintf ( 
                    D_ALWAYS, 
                    "OwnerProfile::environment: "
                    "DestroyEnvironmentBlock() failed "
                    "(last-error = %u)\n", 
                    GetLastError () );
            }
        }

        /* return to previous privilege level */
        set_priv ( priv );

    }

    return ok;

}