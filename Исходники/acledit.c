BOOL
EditDefaultDacl(
    HWND    hwndOwner,
    HANDLE  Instance,
    HANDLE  MyToken
    )
{
    NTSTATUS Status;
    BOOL    Success = FALSE;
    DWORD   EditResult;
    HANDLE  Token = NULL;
    PTOKEN_DEFAULT_DACL DefaultDacl = NULL;
    PSECURITY_DESCRIPTOR SecurityDescriptor = NULL;
    PTOKEN_OWNER Owner = NULL;
    PTOKEN_PRIMARY_GROUP PrimaryGroup = NULL;
    WCHAR string[MAX_STRING_LENGTH];

    //
    // Get the window text so we can use it as the token name
    //

    GetWindowTextW(((PMYTOKEN)MyToken)->hwnd, string, sizeof(string)/sizeof(*string));


    //
    // Get a handle to the token
    //

    Token = OpenToken(MyToken, TOKEN_QUERY);

    if (Token == NULL) {
        DbgPrint("SECEDIT : Failed to open the token with TOKEN_QUERY access\n");
        goto CleanupAndExit;
    }


    //
    // Read the default DACL from the token
    //

    if (!GetTokenInfo(Token, TokenDefaultDacl, (PPVOID)&DefaultDacl)) {
        DbgPrint("SECEDIT : Failed to read default DACL from token\n");
        goto CleanupAndExit;
    }


    //
    // Get the owner and group of the token
    //

    if (!GetTokenInfo(Token, TokenOwner, (PPVOID)&Owner)) {
        DbgPrint("SECEDIT : Failed to read owner from token\n");
        goto CleanupAndExit;
    }

    if (!GetTokenInfo(Token, TokenPrimaryGroup, (PPVOID)&PrimaryGroup)) {
        DbgPrint("SECEDIT : Failed to read primary group from token\n");
        goto CleanupAndExit;
    }




    //
    // Create a security descriptor
    //

    SecurityDescriptor = Alloc(SECURITY_DESCRIPTOR_MIN_LENGTH);

    if (SecurityDescriptor == NULL) {
        DbgPrint("SECEDIT : Failed to allocate security descriptor\n");
        goto CleanupAndExit;
    }

    Status = RtlCreateSecurityDescriptor(SecurityDescriptor, SECURITY_DESCRIPTOR_REVISION);
    ASSERT(NT_SUCCESS(Status));




    //
    // Set the DACL on the security descriptor
    //

    Status = RtlSetDaclSecurityDescriptor(
                        SecurityDescriptor,
                        TRUE,   // DACL present
                        DefaultDacl->DefaultDacl,
                        FALSE   // DACL defaulted
                        );
    ASSERT(NT_SUCCESS(Status));

    //
    // Put the owner and group in the security descriptor to keep the
    // ACL editor happy
    //

    Status = RtlSetOwnerSecurityDescriptor(
                        SecurityDescriptor,
                        Owner->Owner,
                        FALSE // Owner defaulted
                        );
    ASSERT(NT_SUCCESS(Status));


    Status = RtlSetGroupSecurityDescriptor(
                        SecurityDescriptor,
                        PrimaryGroup->PrimaryGroup,
                        FALSE // Owner defaulted
                        );
    ASSERT(NT_SUCCESS(Status));



    ASSERT(RtlValidSecurityDescriptor(SecurityDescriptor));

    //
    // Call the ACL editor, it will call our ApplySecurity function
    // to store any ACL changes in the token.
    //

    Success = EditTokenDefaultAcl(
                        hwndOwner,
                        Instance,
                        string,
                        MyToken,
                        SecurityDescriptor,
                        &EditResult
                        );
    if (!Success) {
        DbgPrint("SECEDIT: Failed to edit token DACL\n");
    }

CleanupAndExit:

    if (DefaultDacl != NULL) {
        FreeTokenInfo(DefaultDacl);
    }
    if (SecurityDescriptor != NULL) {
        FreeTokenInfo(SecurityDescriptor);
    }
    if (PrimaryGroup != NULL) {
        FreeTokenInfo(PrimaryGroup);
    }
    if (Owner != NULL) {
        FreeTokenInfo(Owner);
    }

    if (Token != NULL) {
        CloseToken(Token);
    }


    return(Success);
}