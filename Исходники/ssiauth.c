VOID
NlComputeChallenge(
    OUT PNETLOGON_CREDENTIAL Challenge
    )

/*++

Routine Description:

    Generates a 64 bit challenge

    Make an 8 byte seed by filling in BigTime i.e. seconds
    since Jan 1 1970 in lower four bytes and a counter in
    upper four bytes. Counter is incremented after each use.
    This seed is used as encryption key to encrypt standard
    text which will be used as challenge.

Arguments:

    Challenge - Returns the computed challenge

Return Value:

    None.

--*/
{
    NTSTATUS Status;
    char    Seed[PWLEN];
    LM_OWF_PASSWORD BigChallenge;
    LARGE_INTEGER TimeNow;


    RtlZeroMemory(Seed, sizeof(Seed) );

    //
    // we need to remember ClientChallenge and RequestorName for future use
    // put these into shared seg SSISEG
    // NlGlobalSessionCounter is a global initialized to 0 at UAS init time
    //


    Status = NtQuerySystemTime( &TimeNow );
    NlAssert( NT_SUCCESS(Status) );

    Status = RtlTimeToSecondsSince1970( &TimeNow, ((unsigned long * ) Seed) );
    NlAssert( NT_SUCCESS(Status) );

    *((unsigned long * ) & Seed[4]) = NlGlobalSessionCounter++;

    //
    // Create ClientChallenge
    //
    // NOTE: RtlCalculateLmOwfPassword() will generate 16 byte txt
    //

    Status = RtlCalculateLmOwfPassword(Seed, &BigChallenge);
    NlAssert( NT_SUCCESS(Status) );

    //
    // we need (or will use) only 8 bytes of this info
    //

    RtlCopyMemory(Challenge, &BigChallenge, sizeof(Challenge) );

    return;
}