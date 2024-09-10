/*
 * @unimplemented
 */
AUTHZAPI
BOOL
WINAPI
AuthzInitializeResourceManager(IN DWORD flags,
                               IN PFN_AUTHZ_DYNAMIC_ACCESS_CHECK pfnAccessCheck  OPTIONAL,
                               IN PFN_AUTHZ_COMPUTE_DYNAMIC_GROUPS pfnComputeDynamicGroups  OPTIONAL,
                               IN PFN_AUTHZ_FREE_DYNAMIC_GROUPS pfnFreeDynamicGroups  OPTIONAL,
                               IN PCWSTR ResourceManagerName  OPTIONAL,
                               IN PAUTHZ_RESOURCE_MANAGER_HANDLE pAuthzResourceManager)
{
    BOOL Ret = FALSE;

    if (pAuthzResourceManager != NULL &&
        !(flags & ~(AUTHZ_RM_FLAG_NO_AUDIT | AUTHZ_RM_FLAG_INITIALIZE_UNDER_IMPERSONATION)))
    {
        PAUTHZ_RESMAN ResMan;
        SIZE_T RequiredSize = sizeof(AUTHZ_RESMAN);

        if (ResourceManagerName != NULL)
        {
            RequiredSize += wcslen(ResourceManagerName) * sizeof(WCHAR);
        }

        ResMan = (PAUTHZ_RESMAN)LocalAlloc(LMEM_FIXED,
                                           RequiredSize);
        if (ResMan != NULL)
        {
            /* initialize the resource manager structure */
#if DBG
            ResMan->Tag = RESMAN_TAG;
#endif

            ResMan->flags = flags;
            ResMan->UserSid = NULL;

            if (ResourceManagerName != NULL)
            {
                wcscpy(ResMan->ResourceManagerName,
                       ResourceManagerName);
            }
            else
                ResMan->ResourceManagerName[0] = UNICODE_NULL;

            ResMan->pfnAccessCheck = pfnAccessCheck;
            ResMan->pfnComputeDynamicGroups = pfnComputeDynamicGroups;
            ResMan->pfnFreeDynamicGroups = pfnFreeDynamicGroups;

            if (!(flags & AUTHZ_RM_FLAG_NO_AUDIT))
            {
                /* FIXME - initialize auditing */
                DPRINT1("Auditing not implemented!\n");
            }

            if (flags & AUTHZ_RM_FLAG_INITIALIZE_UNDER_IMPERSONATION)
            {
                Ret = AuthzpInitUnderImpersonation(ResMan);
            }
            else
            {
                Ret = AuthzpInitSelf(ResMan);
            }

            if (Ret)
            {
                /* finally return the handle */
                *pAuthzResourceManager = (AUTHZ_RESOURCE_MANAGER_HANDLE)ResMan;
            }
            else
            {
                DPRINT1("Querying the token failed!\n");
                LocalFree((HLOCAL)ResMan);
            }
        }
    }
    else
        SetLastError(ERROR_INVALID_PARAMETER);

    return Ret;
}