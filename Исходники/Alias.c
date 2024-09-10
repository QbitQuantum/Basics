NTSTATUS
SampRemoveAllMembersFromAlias(IN PSAM_DB_OBJECT AliasObject)
{
    HANDLE MembersKeyHandle = NULL;
    PSAMPR_SID_INFORMATION MemberArray = NULL;
    ULONG MemberCount = 0;
    ULONG Index;
    NTSTATUS Status;

    TRACE("(%p)\n", AliasObject);

    /* Open the members key of the alias object */
    Status = SampRegOpenKey(AliasObject->KeyHandle,
                            L"Members",
                            KEY_READ,
                            &MembersKeyHandle);
    if (!NT_SUCCESS(Status))
    {
        ERR("SampRegOpenKey failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    /* Get a list of all members of the alias */
    Status = SampGetMembersInAlias(AliasObject,
                                   &MemberCount,
                                   &MemberArray);
    if (!NT_SUCCESS(Status))
    {
        ERR("SampGetMembersInAlias failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    /* Remove all members from the alias */
    for (Index = 0; Index < MemberCount; Index++)
    {
        Status = SampRemoveMemberFromAlias(AliasObject,
                                           MemberArray[Index].SidPointer);
        if (!NT_SUCCESS(Status))
            goto done;
    }

done:
    if (MemberArray != NULL)
    {
        for (Index = 0; Index < MemberCount; Index++)
        {
            if (MemberArray[Index].SidPointer != NULL)
                midl_user_free(MemberArray[Index].SidPointer);
        }

        midl_user_free(MemberArray);
    }

    SampRegCloseKey(&MembersKeyHandle);

    return Status;
}