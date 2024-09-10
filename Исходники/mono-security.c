static ACCESS_MASK
GetRightsFromSid (PSID sid, PACL acl)
{
    ACCESS_MASK rights = 0;
    TRUSTEE trustee;

    BuildTrusteeWithSidW (&trustee, sid);
    if (GetEffectiveRightsFromAcl (acl, &trustee, &rights) != ERROR_SUCCESS)
        return 0;

    return rights;
}