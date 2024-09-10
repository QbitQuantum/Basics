//-----------------------------------------------------
//
//-----------------------------------------------------
bool initLDAP(IPropertyTree * ldapProps)
{
    StringAttr serverType( ldapProps->queryProp("@serverType") );
    if (!serverType.length())
    {
        fprintf(stderr, "\nERROR: serverType not set in LDAPServer component");
        return false;
    }

    StringBuffer hpccUser;
    StringBuffer hpccPwd;
    ldapProps->getProp("@systemUser", hpccUser);
    ldapProps->getProp("@systemPassword", hpccPwd);
    if (0==hpccUser.length() || 0==hpccPwd.length())
    {
        fprintf(stderr, "\nERROR: HPCC systemUser credentials not found in configuration");
        return false;
    }

    StringBuffer ldapAddress;
    ldapProps->getProp("@ldapAddress", ldapAddress);

    //Get LDAP admin creds from user
    char buff[100];
    fprintf(stdout, "\nEnter the '%s' LDAP Admin User name on '%s'...",serverType.get(),ldapAddress.str());
    do
    {
        char * line = fgets(buff, sizeof(buff), stdin);
        if (!line)
            return false;
    }
    while (buff[0] == (char)'\n');

    if (buff[strlen(buff)-1] == '\n')
        buff[strlen(buff)-1] = (char)NULL;
    StringAttr ldapUser(buff);

    fprintf(stdout, "Enter the LDAP Admin user '%s' password...",ldapUser.get());
    char * line = fgets(buff, sizeof(buff), stdin);
    if (!line)
        return false;

    if (buff[strlen(buff)-1] == '\n')
        buff[strlen(buff)-1] = (char)NULL;
    StringAttr ldapPwd(buff);
    if (0==ldapUser.length() || 0==ldapPwd.length())
    {
        fprintf(stderr, "\nERROR: Invalid LDAP Admin account credentials entered");
        return false;
    }

    fprintf(stdout, "\nReady to initialize HPCC LDAP Environment, using the following settings");
    fprintf(stdout, "\n\tLDAP Server     : %s", ldapAddress.str());
    fprintf(stdout, "\n\tLDAP Type       : %s", serverType.get());
    fprintf(stdout, "\n\tHPCC Admin User : %s", hpccUser.str());
    fprintf(stdout, "\nProceed?  y/n ");
    for (;;)
    {
        int c = getchar();
        if (c == 'y' || c == 'Y')
            break;
        else if (c == 'n' || c == 'N')
            return true;
    }

    if (stricmp(serverType.get(),"ActiveDirectory"))
        ldapProps->setProp("@systemBasedn", "");

    //Replace system user with LDAP Admin credentials
    ldapProps->setProp("@systemUser", ldapUser);
    ldapProps->setProp("@systemCommonName", ldapUser);
    StringBuffer sb;
    encrypt(sb,ldapPwd);
    ldapProps->setProp("@systemPassword", sb.str());

    //Create security manager. This creates the required OUs
    Owned<ISecManager> secMgr;
    try
    {
        secMgr.setown(newLdapSecManager("initldap", *LINK(ldapProps)));
    }
    catch(IException *e)
    {
        StringBuffer buff;
        e->errorMessage(buff);
        e->Release();
        fprintf(stderr, "\nERROR: Unable to create security manager : %s", buff.str());
        return false;
    }

    //Create HPCC Admin user
    Owned<ISecUser> user = secMgr->createUser(hpccUser.str());
    StringBuffer pwd;
    decrypt(pwd, hpccPwd.str());
    user->credentials().setPassword(pwd.str());
    try { secMgr->addUser(*user.get()); }
    catch(...) {}//user may already exist, so just move on

    //Add HPCC admin user to Administrators group
    CLdapSecManager* ldapSecMgr = dynamic_cast<CLdapSecManager*>(secMgr.get());
    if (!ldapSecMgr)
    {
        fprintf(stderr, "\nERROR: Unable to access CLdapSecManager object");
        return false;
    }
    StringAttr adminGroup;
    bool isActiveDir = true;
    if (0 == stricmp(serverType.get(),"ActiveDirectory"))
        adminGroup.set("Administrators");
    else
        adminGroup.set("Directory Administrators");
    try { ldapSecMgr->changeUserGroup("add", hpccUser.str(), adminGroup); }
    catch(...) {}//user may already be in group so just move on

    fprintf(stdout, "\n\nLDAP Initialization successful\n");
    return true;
}