void
init_system_mib(void)
{

#ifdef HAVE_UNAME
    struct utsname  utsName;

    uname(&utsName);
    snprintf(version_descr, sizeof(version_descr),
            "%s %s %s %s %s", utsName.sysname,
            utsName.nodename, utsName.release, utsName.version,
            utsName.machine);
    version_descr[ sizeof(version_descr)-1 ] = 0;
#else
#if HAVE_EXECV
    struct extensible extmp;

    /*
     * set default values of system stuff 
     */
    sprintf(extmp.command, "%s -a", UNAMEPROG);
    /*
     * setup defaults 
     */
    extmp.type = EXECPROC;
    extmp.next = NULL;
    exec_command(&extmp);
    strncpy(version_descr, extmp.output, sizeof(version_descr));
    version_descr[sizeof(version_descr) - 1] = 0;
    version_descr[strlen(version_descr) - 1] = 0;       /* chomp new line */
#else
#if (defined (WIN32) && defined (HAVE_WIN32_PLATFORM_SDK)) || defined (mingw32)
    windowsOSVersionString(version_descr, sizeof(version_descr));
#else
    strcpy(version_descr, "unknown");
#endif
#endif
#endif

#ifdef HAVE_GETHOSTNAME
    gethostname(sysName, sizeof(sysName));
#else
#ifdef HAVE_UNAME
    strncpy(sysName, utsName.nodename, sizeof(sysName));
#else
#if defined (HAVE_EXECV) && !defined (mingw32)
    sprintf(extmp.command, "%s -n", UNAMEPROG);
    /*
     * setup defaults 
     */
    extmp.type = EXECPROC;
    extmp.next = NULL;
    exec_command(&extmp);
    strncpy(sysName, extmp.output, sizeof(sysName));
    sysName[strlen(sysName) - 1] = 0;   /* chomp new line */
#else
    strcpy(sysName, "unknown");
#endif                          /* HAVE_EXECV */
#endif                          /* HAVE_UNAME */
#endif                          /* HAVE_GETHOSTNAME */

#if (defined (WIN32) && defined (HAVE_WIN32_PLATFORM_SDK)) || defined (mingw32)
    {
      HKEY hKey;
      /* Default sysContact is the registered windows user */
      if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                       "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0,
                       KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) {
          char registeredOwner[256] = "";
          DWORD registeredOwnerSz = 256;
          if (RegQueryValueEx(hKey, "RegisteredOwner", NULL, NULL,
                              (LPBYTE)registeredOwner,
                              &registeredOwnerSz) == ERROR_SUCCESS) {
              strcpy(sysContact, registeredOwner);
          }
          RegCloseKey(hKey);
      }
    }
#endif

    /* default sysObjectID */
    memcpy(sysObjectID, version_sysoid, version_sysoid_len * sizeof(oid));
    sysObjectIDByteLength = version_sysoid_len * sizeof(oid);

    {
        const oid sysDescr_oid[] = { 1, 3, 6, 1, 2, 1, 1, 1 };
        static netsnmp_watcher_info sysDescr_winfo;
        netsnmp_register_watched_scalar(
            netsnmp_create_handler_registration(
                "mibII/sysDescr", NULL, sysDescr_oid, OID_LENGTH(sysDescr_oid),
                HANDLER_CAN_RONLY),
            netsnmp_init_watcher_info(&sysDescr_winfo, version_descr, 0,
				      ASN_OCTET_STR, WATCHER_SIZE_STRLEN));
    }
    {
        const oid sysObjectID_oid[] = { 1, 3, 6, 1, 2, 1, 1, 2 };
        static netsnmp_watcher_info sysObjectID_winfo;
        netsnmp_register_watched_scalar(
            netsnmp_create_handler_registration(
                "mibII/sysObjectID", NULL,
                sysObjectID_oid, OID_LENGTH(sysObjectID_oid),
                HANDLER_CAN_RONLY),
            netsnmp_init_watcher_info6(
		&sysObjectID_winfo, sysObjectID, 0, ASN_OBJECT_ID,
                WATCHER_MAX_SIZE | WATCHER_SIZE_IS_PTR,
                MAX_OID_LEN, &sysObjectIDByteLength));
    }
    {
        const oid sysUpTime_oid[] = { 1, 3, 6, 1, 2, 1, 1, 3 };
        netsnmp_register_scalar(
            netsnmp_create_handler_registration(
                "mibII/sysUpTime", handle_sysUpTime,
                sysUpTime_oid, OID_LENGTH(sysUpTime_oid),
                HANDLER_CAN_RONLY));
    }
    {
        const oid sysContact_oid[] = { 1, 3, 6, 1, 2, 1, 1, 4 };
        static netsnmp_watcher_info sysContact_winfo;
        netsnmp_register_watched_scalar(
            netsnmp_create_update_handler_registration(
                "mibII/sysContact", sysContact_oid, OID_LENGTH(sysContact_oid),
                HANDLER_CAN_RWRITE, &sysContactSet),
            netsnmp_init_watcher_info(
		&sysContact_winfo, sysContact, SYS_STRING_LEN - 1,
		ASN_OCTET_STR, WATCHER_MAX_SIZE | WATCHER_SIZE_STRLEN));
    }
    {
        const oid sysName_oid[] = { 1, 3, 6, 1, 2, 1, 1, 5 };
        static netsnmp_watcher_info sysName_winfo;
        netsnmp_register_watched_scalar(
            netsnmp_create_update_handler_registration(
                "mibII/sysName", sysName_oid, OID_LENGTH(sysName_oid),
                HANDLER_CAN_RWRITE, &sysNameSet),
            netsnmp_init_watcher_info(
                &sysName_winfo, sysName, SYS_STRING_LEN - 1, ASN_OCTET_STR,
                WATCHER_MAX_SIZE | WATCHER_SIZE_STRLEN));
    }
    {
        const oid sysLocation_oid[] = { 1, 3, 6, 1, 2, 1, 1, 6 };
        static netsnmp_watcher_info sysLocation_winfo;
        netsnmp_register_watched_scalar(
            netsnmp_create_update_handler_registration(
                "mibII/sysLocation", sysLocation_oid,
                OID_LENGTH(sysLocation_oid),
                HANDLER_CAN_RWRITE, &sysLocationSet),
            netsnmp_init_watcher_info(
		&sysLocation_winfo, sysLocation, SYS_STRING_LEN - 1,
		ASN_OCTET_STR, WATCHER_MAX_SIZE | WATCHER_SIZE_STRLEN));
    }
    {
        const oid sysServices_oid[] = { 1, 3, 6, 1, 2, 1, 1, 7 };
        netsnmp_register_read_only_int_scalar(
            "mibII/sysServices", sysServices_oid, OID_LENGTH(sysServices_oid),
            &sysServices, handle_sysServices);
    }
    if (++system_module_count == 3)
        REGISTER_SYSOR_ENTRY(system_module_oid,
                             "The MIB module for SNMPv2 entities");

    sysContactSet = sysLocationSet = sysNameSet = 0;

    /*
     * register our config handlers 
     */
    snmpd_register_config_handler("sysdescr",
                                  system_parse_config_sysdescr, NULL,
                                  "description");
    snmpd_register_config_handler("syslocation",
                                  system_parse_config_sysloc, NULL,
                                  "location");
    snmpd_register_config_handler("syscontact", system_parse_config_syscon,
                                  NULL, "contact-name");
    snmpd_register_config_handler("sysname", system_parse_config_sysname,
                                  NULL, "node-name");
    snmpd_register_config_handler("psyslocation",
                                  system_parse_config_sysloc, NULL, NULL);
    snmpd_register_config_handler("psyscontact",
                                  system_parse_config_syscon, NULL, NULL);
    snmpd_register_config_handler("psysname", system_parse_config_sysname,
                                  NULL, NULL);
    snmpd_register_config_handler("sysservices",
                                  system_parse_config_sysServices, NULL,
                                  "NUMBER");
    snmpd_register_config_handler("sysobjectid",
                                  system_parse_config_sysObjectID, NULL,
                                  "OID");
    snmp_register_callback(SNMP_CALLBACK_LIBRARY, SNMP_CALLBACK_STORE_DATA,
                           system_store, NULL);
}