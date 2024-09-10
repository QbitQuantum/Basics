BOOLEAN
SidTranslation(
    PSID Sid,
    PSTRING AccountName
    )
// AccountName is expected to have a large maximum length

{
    if (RtlEqualSid(Sid, WorldSid)) {
        RtlInitString( AccountName, "WORLD");
        return(TRUE);
    }

    if (RtlEqualSid(Sid, LocalSid)) {
        RtlInitString( AccountName, "LOCAL");

        return(TRUE);
    }

    if (RtlEqualSid(Sid, NetworkSid)) {
        RtlInitString( AccountName, "NETWORK");

        return(TRUE);
    }

    if (RtlEqualSid(Sid, BatchSid)) {
        RtlInitString( AccountName, "BATCH");

        return(TRUE);
    }

    if (RtlEqualSid(Sid, InteractiveSid)) {
        RtlInitString( AccountName, "INTERACTIVE");
        return(TRUE);
    }

    if (RtlEqualSid(Sid, LocalSystemSid)) {
        RtlInitString( AccountName, "SYSTEM");
        return(TRUE);
    }

    if (RtlEqualSid(Sid, LocalManagerSid)) {
        RtlInitString( AccountName, "LOCAL MANAGER");
        return(TRUE);
    }

    if (RtlEqualSid(Sid, LocalAdminSid)) {
        RtlInitString( AccountName, "LOCAL ADMIN");
        return(TRUE);
    }

    return(FALSE);

}