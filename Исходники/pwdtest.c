int _CRTAPI1
main(
    IN int argc,
    IN char ** argv
    )
/*++

Routine Description:

    Drive the password changing.

Arguments:

    argc - the number of command-line arguments.

    argv - an array of pointers to the arguments.

Return Value:

    Exit status

--*/
{
    NTSTATUS Status;
    MSV1_0_CHANGEPASSWORD_REQUEST Request;
    PMSV1_0_CHANGEPASSWORD_RESPONSE ReturnBuffer;
    ULONG ReturnBufferSize;
    NTSTATUS ProtocolStatus;
    OBJECT_ATTRIBUTES LSAObjectAttributes;
    UNICODE_STRING LocalComputerName = { 0, 0, NULL };
    PPOLICY_PRIMARY_DOMAIN_INFO PrimaryDomainInfo = NULL;

    if ( argc < 5 ) {
        fprintf( stderr,
            "Usage: pwdtest DomainName UserName OldPassword NewPassword\n" );
        return(1);
    }

    //
    // Set up MSV1_0.dll environment.
    //

    MspHeap = RtlProcessHeap();

    Status = NlInitialize();

    if ( !NT_SUCCESS( Status ) ) {
        printf("pwdtest: NlInitialize failed, status %x\n", Status);
        return(1);
    }

    Lsa.AllocateClientBuffer = LsapAllocateClientBuffer;
    Lsa.FreeClientBuffer = LsapFreeClientBuffer;
    Lsa.CopyToClientBuffer = LsapCopyToClientBuffer;



    //
    // Open the LSA policy database in case change password needs it
    //

    InitializeObjectAttributes( &LSAObjectAttributes,
                                  NULL,             // Name
                                  0,                // Attributes
                                  NULL,             // Root
                                  NULL );           // Security Descriptor

    Status = LsaOpenPolicy( &LocalComputerName,
                            &LSAObjectAttributes,
                            POLICY_VIEW_LOCAL_INFORMATION,
                            &NlpPolicyHandle );

    if( !NT_SUCCESS(Status) ) {
        printf("pwdtest: LsaOpenPolicy failed, status %x\n", Status);
        return(1);
    }


    //
    // Get the name of our domain.
    //

    Status = LsaQueryInformationPolicy(
                    NlpPolicyHandle,
                    PolicyPrimaryDomainInformation,
                    (PVOID *) &PrimaryDomainInfo );

    if( !NT_SUCCESS(Status) ) {
        KdPrint(("pwdtest: LsaQueryInformationPolicy failed, status %x\n",
                 Status));
        return(1);
    }

    NlpSamDomainName = PrimaryDomainInfo->Name;



    //
    // Build the request message
    //

    Request.MessageType = MsV1_0ChangePassword;
    RtlCreateUnicodeStringFromAsciiz( &Request.DomainName, argv[1] );
    RtlCreateUnicodeStringFromAsciiz( &Request.AccountName, argv[2] );
    RtlCreateUnicodeStringFromAsciiz( &Request.OldPassword, argv[3] );
    RtlCreateUnicodeStringFromAsciiz( &Request.NewPassword, argv[4] );

    Status = MspLm20ChangePassword( NULL,
                                    &Request,
                                    &Request,
                                    0x7FFFFFFF,
                                    (PVOID *) &ReturnBuffer,
                                    &ReturnBufferSize,
                                    &ProtocolStatus );

    printf( "Status = 0x%lx  0x%lx\n", Status, ProtocolStatus );

    if ( ProtocolStatus == STATUS_CANT_DISABLE_MANDATORY ) {
        printf( "Are you running as SYSTEM?\n" );
    }

    if ( ReturnBufferSize != 0 ) {
        printf( "PasswordInfoValid %ld\n", ReturnBuffer->PasswordInfoValid );
        if ( ReturnBuffer->PasswordInfoValid ) {
            printf( "Min length: %ld  PasswordHistory: %ld  Prop 0x%lx\n",
                ReturnBuffer->DomainPasswordInfo.MinPasswordLength,
                ReturnBuffer->DomainPasswordInfo.PasswordHistoryLength,
                ReturnBuffer->DomainPasswordInfo.PasswordProperties );
        }
    }
    return 0;


}