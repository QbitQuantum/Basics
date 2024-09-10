VOID _CRTAPI1
main (int argc, char *argv[])
{


    BOOL Result;
    LPSTR lpFileName;
    SECURITY_DESCRIPTOR SecurityDescriptor;
//    CHAR Dacl[256];
    HANDLE TokenHandle;


    //
    // We expect a file...
    //
    if (argc <= 1) {

        printf("Must specify a file name");
        return;
    }


    lpFileName = argv[1];

#if VERBOSE

    printf("Filename is %s\n", lpFileName );

#endif



    Result = VariableInitialization();

    if ( !Result ) {
        printf("Out of memory\n");
        return;
    }




    Result = GetTokenHandle( &TokenHandle );

    if ( !Result ) {

        //
        // This should not happen
        //

        printf("Unable to obtain the handle to our token, exiting\n");
        return;
    }






    //
    // Attempt to put a NULL Dacl on the object
    //

    InitializeSecurityDescriptor( &SecurityDescriptor, SECURITY_DESCRIPTOR_REVISION );



//    Result = InitializeAcl ( (PACL)Dacl, 256, ACL_REVISION2 );
//
//    if ( !Result ) {
//        printf("Unable to initialize Acl, exiting\n");
//        return;
//    }
//
//
//    Result = AddAccessAllowedAce (
//                 (PACL)Dacl,
//                 ACL_REVISION2,
//                 GENERIC_ALL,
//                 AliasAdminsSid
//                 );
//
//
//
//    if ( !Result ) {
//        printf("Unable to create required ACL, error code = %d\n", GetLastError());
//        printf("Exiting\n");
//        return;
//    }


    Result = SetSecurityDescriptorDacl (
                 &SecurityDescriptor,
                 TRUE,
                 NULL,
                 FALSE
                 );



    if ( !Result ) {
        printf("SetSecurityDescriptorDacl failed, error code = %d\n", GetLastError());
        printf("Exiting\n");
        return;
    }

    Result = SetFileSecurity(
                 lpFileName,
                 DACL_SECURITY_INFORMATION,
                 &SecurityDescriptor
                 );

    if ( !Result ) {

#if VERBOSE

        printf("SetFileSecurity failed, error code = %d\n", GetLastError());

#endif

    } else {

        printf("Successful, protection removed\n");
        return;
    }



    //
    // That didn't work.
    //


    //
    // Attempt to make Administrator the owner of the file.
    //


    Result = SetSecurityDescriptorOwner (
                 &SecurityDescriptor,
                 AliasAdminsSid,
                 FALSE
                 );

    if ( !Result ) {
        printf("SetSecurityDescriptorOwner failed, lasterror = %d\n", GetLastError());
        return;
    }


    Result = SetFileSecurity(
                 lpFileName,
                 OWNER_SECURITY_INFORMATION,
                 &SecurityDescriptor
                 );

    if ( Result ) {

#if VERBOSE

        printf("Owner successfully changed to Admin\n");

#endif

    } else {

        //
        // That didn't work either.
        //

#if VERBOSE

        printf("Opening file for WRITE_OWNER failed\n");
        printf("Attempting to assert TakeOwnership privilege\n");

#endif

        //
        // Assert TakeOwnership privilege, then try again
        //

        Result = AssertTakeOwnership( TokenHandle );

        if ( !Result ) {
            printf("Could not enable SeTakeOwnership privilege\n");
            printf("Log on as Administrator and try again\n");
            return;
        }

        Result = SetFileSecurity(
                     lpFileName,
                     OWNER_SECURITY_INFORMATION,
                     &SecurityDescriptor
                     );

        if ( Result ) {

#if VERBOSE
            printf("Owner successfully changed to Administrator\n");

#endif

        } else {

            printf("Unable to assign Administrator as owner\n");
            printf("Log on as Administrator and try again\n");
            return;
        }

    }

    //
    // Try to put a benign DACL onto the file again
    //

    Result = SetFileSecurity(
                 lpFileName,
                 DACL_SECURITY_INFORMATION,
                 &SecurityDescriptor
                 );

    if ( !Result ) {

        //
        // There's no hope.  Something is screwed up.
        //

        printf("SetFileSecurity unexpectedly failed, error code = %d\n", GetLastError());

    } else {

        printf("Successful, protection removed\n");
        return;
    }
}