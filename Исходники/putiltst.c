static void TestVersion(void)
{
    UVersionInfo versionArray = {0x01, 0x00, 0x02, 0x02};
    UVersionInfo versionArray2 = {0x01, 0x00, 0x02, 0x02};
    char versionString[17]; /* xxx.xxx.xxx.xxx\0 */
    UChar versionUString[] = { 0x0031, 0x002E, 0x0030, 0x002E,
                               0x0032, 0x002E, 0x0038, 0x0000 }; /* 1.0.2.8 */
    UBool isModified = FALSE;
    UVersionInfo version;
    UErrorCode status = U_ZERO_ERROR;

    log_verbose("Testing the API u_versionToString().....\n");
    u_versionToString(versionArray, versionString);
    if(strcmp(versionString, "1.0.2.2") != 0){
        log_err("ERROR: u_versionToString() failed. Expected: 1.0.2.2, Got=%s\n", versionString);
    }
    log_verbose("Testing the API u_versionToString().....with versionArray=NULL\n");
    u_versionToString(NULL, versionString);
    if(strcmp(versionString, "") != 0){
        log_err("ERROR: u_versionToString() failed. with versionArray=NULL. It should just return\n");
    }
    log_verbose("Testing the API u_versionToString().....with versionArray=NULL\n");
    u_versionToString(NULL, versionString);
    if(strcmp(versionString, "") != 0){
        log_err("ERROR: u_versionToString() failed . It should just return\n");
    }
    log_verbose("Testing the API u_versionToString().....with versionString=NULL\n");
    u_versionToString(versionArray, NULL);
    if(strcmp(versionString, "") != 0){
        log_err("ERROR: u_versionToString() failed. with versionArray=NULL  It should just return\n");
    }
    versionArray[0] = 0x0a;
    log_verbose("Testing the API u_versionToString().....\n");
    u_versionToString(versionArray, versionString);
    if(strcmp(versionString, "10.0.2.2") != 0){
        log_err("ERROR: u_versionToString() failed. Expected: 10.0.2.2, Got=%s\n", versionString);
    }
    versionArray[0] = 0xa0;
    u_versionToString(versionArray, versionString);
    if(strcmp(versionString, "160.0.2.2") != 0){
        log_err("ERROR: u_versionToString() failed. Expected: 160.0.2.2, Got=%s\n", versionString);
    }
    versionArray[0] = 0xa0;
    versionArray[1] = 0xa0;
    u_versionToString(versionArray, versionString);
    if(strcmp(versionString, "160.160.2.2") != 0){
        log_err("ERROR: u_versionToString() failed. Expected: 160.160.2.2, Got=%s\n", versionString);
    }
    versionArray[0] = 0x01;
    versionArray[1] = 0x0a;
    u_versionToString(versionArray, versionString);
    if(strcmp(versionString, "1.10.2.2") != 0){
        log_err("ERROR: u_versionToString() failed. Expected: 160.160.2.2, Got=%s\n", versionString);
    }

    log_verbose("Testing the API u_versionFromString() ....\n");
    u_versionFromString(versionArray, "1.3.5.6");
    u_versionToString(versionArray, versionString);
    if(strcmp(versionString, "1.3.5.6") != 0){
        log_err("ERROR: u_getVersion() failed. Expected: 1.3.5.6, Got=%s\n",  versionString);
    }
    log_verbose("Testing the API u_versionFromString() where versionArray=NULL....\n");
    u_versionFromString(NULL, "1.3.5.6");
    u_versionToString(versionArray, versionString);
    if(strcmp(versionString, "1.3.5.6") != 0){
        log_err("ERROR: u_getVersion() failed. Expected: 1.3.5.6, Got=%s\n",  versionString);
    }

    log_verbose("Testing the API u_getVersion().....\n");
    u_getVersion(versionArray);
    u_versionToString(versionArray, versionString);
    if(strcmp(versionString, U_ICU_VERSION) != 0){
        log_err("ERROR: u_getVersion() failed. Got=%s, expected %s\n",  versionString, U_ICU_VERSION);
    }
    /* test unicode */
    log_verbose("Testing u_versionFromUString...\n");
    u_versionFromString(versionArray,"1.0.2.8");
    u_versionFromUString(versionArray2, versionUString);
    u_versionToString(versionArray2, versionString); 
    if(memcmp(versionArray, versionArray2, sizeof(UVersionInfo))) {
       log_err("FAIL: u_versionFromUString produced a different result - not 1.0.2.8 but %s [%x.%x.%x.%x]\n", 
          versionString,
        (int)versionArray2[0],
        (int)versionArray2[1],
        (int)versionArray2[2],
        (int)versionArray2[3]);
    } 
    else {
       log_verbose(" from UString: %s\n", versionString);
    }

    /* Test the data version API for better code coverage */
    u_getDataVersion(version, &status);
    if (U_FAILURE(status)) {
        log_data_err("ERROR: Unable to get data version. %s\n", u_errorName(status));
    } else {
        u_isDataOlder(version, &isModified, &status);
        if (U_FAILURE(status)) {
            log_err("ERROR: Unable to compare data version. %s\n", u_errorName(status));
        }
    }
}