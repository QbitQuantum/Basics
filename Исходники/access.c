BOOLEAN
SrvIsKerberosAvailable(
    VOID
    )
/*++

Routine Description:

    Checks whether Kerberos is one of the supported security packages.

Arguments:


Return Value:

    TRUE if Kerberos is available, FALSE if otherwise or error.

--*/

{
    NTSTATUS Status;
    ULONG PackageCount, Index;
    PSecPkgInfoW Packages;
    BOOLEAN FoundKerberos = FALSE;

    //
    // Get the list of packages from the security driver
    //

    Status = EnumerateSecurityPackages(
                &PackageCount,
                &Packages
                );
    if (!NT_SUCCESS(Status)) {
        return(FALSE);
    }

    //
    // Loop through the list looking for Kerberos
    //

    for (Index = 0; Index < PackageCount ; Index++ ) {
        if (!_wcsicmp(Packages[Index].Name, MICROSOFT_KERBEROS_NAME_W)) {
            FoundKerberos = TRUE;
            break;
        }
    }

    FreeContextBuffer(Packages);
    return(FoundKerberos);

}