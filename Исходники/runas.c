static VOID PhpAddAccountsToComboBox(
    _In_ HWND ComboBoxHandle
    )
{
    LSA_HANDLE policyHandle;
    LSA_ENUMERATION_HANDLE enumerationContext = 0;
    PLSA_ENUMERATION_INFORMATION buffer;
    ULONG count;
    ULONG i;
    PPH_STRING name;
    SID_NAME_USE nameUse;

    if (NT_SUCCESS(PhOpenLsaPolicy(&policyHandle, POLICY_VIEW_LOCAL_INFORMATION, NULL)))
    {
        while (NT_SUCCESS(LsaEnumerateAccounts(
            policyHandle,
            &enumerationContext,
            &buffer,
            0x100,
            &count
            )))
        {
            for (i = 0; i < count; i++)
            {
                name = PhGetSidFullName(buffer[i].Sid, TRUE, &nameUse);

                if (name)
                {
                    if (nameUse == SidTypeUser)
                        ComboBox_AddString(ComboBoxHandle, name->Buffer);

                    PhDereferenceObject(name);
                }
            }

            LsaFreeMemory(buffer);
        }

        LsaClose(policyHandle);
    }
}