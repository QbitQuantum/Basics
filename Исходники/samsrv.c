VOID
NTAPI
SamIFree_SAMPR_GET_GROUPS_BUFFER(PSAMPR_GET_GROUPS_BUFFER Ptr)
{
    if (Ptr != NULL)
    {
        if (Ptr->Groups != NULL)
            MIDL_user_free(Ptr->Groups);

        MIDL_user_free(Ptr);
    }
}