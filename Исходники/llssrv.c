BOOL
NTIsPDC(
   LPTSTR ServerName
   )

/*++

Routine Description:


Arguments:


Return Value:

   None.

--*/

{
   static TCHAR Serv[MAX_COMPUTERNAME_LENGTH + 3];
   UNICODE_STRING us;
   NTSTATUS ret;
   OBJECT_ATTRIBUTES oa;
   ACCESS_MASK am;
   SECURITY_QUALITY_OF_SERVICE qos;
   LSA_HANDLE hLSA;
   PPOLICY_LSA_SERVER_ROLE_INFO pvBuffer;
   BOOL IsPDC = FALSE;

   if (ServerName[0] == TEXT('\\'))
      lstrcpy(Serv, ServerName);
   else
      wsprintf(Serv, TEXT("\\\\%s"), ServerName);

   // Set up unicode string structure
   us.Length = lstrlen(Serv) * sizeof(TCHAR);
   us.MaximumLength = us.Length + sizeof(TCHAR);
   us.Buffer = Serv;

   // only need read access
   am = POLICY_READ | POLICY_VIEW_LOCAL_INFORMATION;

   // set up quality of service
   qos.Length = sizeof(SECURITY_QUALITY_OF_SERVICE);
   qos.ImpersonationLevel = SecurityImpersonation;
   qos.ContextTrackingMode = SECURITY_DYNAMIC_TRACKING;
   qos.EffectiveOnly = FALSE;

   // Macro sets everything except security field
   InitializeObjectAttributes( &oa, NULL, 0L, NULL, NULL );
   oa.SecurityQualityOfService = &qos;

   ret = LsaOpenPolicy(&us, &oa, am, &hLSA);

   if (!ret) {
      ret = LsaQueryInformationPolicy(hLSA, PolicyLsaServerRoleInformation, (PVOID *) &pvBuffer);
      LsaClose(hLSA);
      if ((!ret) && (pvBuffer != NULL)) {
         if (pvBuffer->LsaServerRole == PolicyServerRolePrimary)
            IsPDC = TRUE;

         LsaFreeMemory((PVOID) pvBuffer);
      }
   }

   return IsPDC;

} // NTIsPDC