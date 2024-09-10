NTSTATUS
LsapLookupSids(PLSAPR_SID_ENUM_BUFFER SidEnumBuffer,
               PLSAPR_TRANSLATED_NAME OutputNames)
{
    static const UNICODE_STRING UserName = RTL_CONSTANT_STRING(L"Administrator");
    PWELL_KNOWN_SID ptr;
    ULONG Mapped = 0;
    ULONG i;
    NTSTATUS Status;

    PSID *Sids = (PSID *) SidEnumBuffer->SidInfo;

TRACE("LsapLookupSids(%p, %p)\n", SidEnumBuffer, OutputNames);
TRACE("SidEnumBuffer->Entries: %lu\n", SidEnumBuffer->Entries);
TRACE("SidEnumBuffer->SidInfo: %p\n", SidEnumBuffer->SidInfo);

    for (i = 0; i < SidEnumBuffer->Entries; i++)
    {
TRACE("i: %lu\n", i);
        ptr = LsapLookupWellKnownSid(Sids[i]);
        if (ptr != NULL)
        {
            OutputNames[i].Use = ptr->NameUse;

            OutputNames[i].DomainIndex = i; /* Fixme */

            OutputNames[i].Name.Buffer = MIDL_user_allocate(ptr->Name.MaximumLength);
            OutputNames[i].Name.Length = ptr->Name.Length;
            OutputNames[i].Name.MaximumLength = ptr->Name.MaximumLength;
            RtlCopyMemory(OutputNames[i].Name.Buffer, ptr->Name.Buffer, ptr->Name.MaximumLength);

            Mapped++;
        }
        else
        {
            OutputNames[i].Use = SidTypeWellKnownGroup;
            OutputNames[i].DomainIndex = i;
            OutputNames[i].Name.Buffer = MIDL_user_allocate(UserName.MaximumLength);
            OutputNames[i].Name.Length = UserName.Length;
            OutputNames[i].Name.MaximumLength = UserName.MaximumLength;
            RtlCopyMemory(OutputNames[i].Name.Buffer, UserName.Buffer, UserName.MaximumLength);

            Mapped++;
        }
    }

    if (Mapped == 0)
        Status = STATUS_NONE_MAPPED;
    else if (Mapped < SidEnumBuffer->Entries)
        Status = STATUS_SOME_NOT_MAPPED;
    else
        Status = STATUS_SUCCESS;

    return Status;
}