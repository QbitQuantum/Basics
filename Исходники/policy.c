NTSTATUS
LsarQueryDefaultQuota(PLSA_DB_OBJECT PolicyObject,
                      PLSAPR_POLICY_INFORMATION *PolicyInformation)
{
    PPOLICY_DEFAULT_QUOTA_INFO QuotaInfo = NULL;
    ULONG AttributeSize;
    NTSTATUS Status;

    *PolicyInformation = NULL;

    AttributeSize = sizeof(POLICY_DEFAULT_QUOTA_INFO);
    QuotaInfo = MIDL_user_allocate(AttributeSize);
    if (QuotaInfo == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    Status = LsapGetObjectAttribute(PolicyObject,
                                    L"DefQuota",
                                    QuotaInfo,
                                    &AttributeSize);
    if (!NT_SUCCESS(Status))
    {
        MIDL_user_free(QuotaInfo);
    }
    else
    {
        *PolicyInformation = (PLSAPR_POLICY_INFORMATION)QuotaInfo;
    }

    return Status;
}