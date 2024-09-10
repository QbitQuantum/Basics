UINT32 PrvScenarioAppContainerEnumExisting()
{
   UINT32                       status           = NO_ERROR;
   UINT32                       numAppContainers = 0;
   INET_FIREWALL_APP_CONTAINER* pAppContainers   = 0;

   status = NetworkIsolationEnumAppContainers(NETISO_FLAG_FORCE_COMPUTE_BINARIES,
                                              (DWORD*)&numAppContainers,
                                              &pAppContainers);

   HLPR_BAIL_ON_FAILURE(status);

   for(UINT32 containerIndex = 0;
       containerIndex < numAppContainers;
       containerIndex++)
   {
      status = PrvScenarioAppContainerAddFwpmObjects(pAppContainers[containerIndex].appContainerSid,
                                                     pAppContainers[containerIndex].userSid,
                                                     pAppContainers[containerIndex].displayName);
      HLPR_BAIL_ON_FAILURE(status);
   }

   HLPR_BAIL_LABEL:

   return status;
}