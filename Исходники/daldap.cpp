    SecAccessFlags getPermissions(const char *key,const char *obj,IUserDescriptor *udesc,unsigned auditflags,const char * reqSignature, CDateTime * reqUTCTimestamp)
    {
        if (!ldapsecurity||((getLDAPflags()&DLF_ENABLED)==0)) 
            return SecAccess_Full;
        StringBuffer username;
        StringBuffer password;
        if (udesc) 
        {
            udesc->getUserName(username);
            udesc->getPassword(password);
        }
        else
        {
            WARNLOG("NULL UserDescriptor in daldap.cpp getPermissions('%s')",key ? key : "NULL");
        }

        if (0 == username.length())
        {
            username.append(filesdefaultuser);
            decrypt(password, filesdefaultpassword);
        }

        Owned<ISecUser> user = ldapsecurity->createUser(username);
        user->credentials().setPassword(password);

        bool authenticated = false;

        //Check that the digital signature provided by the caller (signature of
        //caller's "scope;username;timeStamp") matches what we expect it to be
        if (!isEmptyString(reqSignature))
        {
            if (nullptr == pDSM)
                pDSM = queryDigitalSignatureManagerInstanceFromEnv();
            if (pDSM && pDSM->isDigiVerifierConfigured())
            {
                StringBuffer requestTimestamp;
                reqUTCTimestamp->getString(requestTimestamp, false);//extract timestamp string from Dali request

                CDateTime now;
                now.setNow();
                if (now.compare(*reqUTCTimestamp) < 0)//timestamp from the future?
                {
                    ERRLOG("LDAP: getPermissions(%s) scope=%s user=%s Request digital signature timestamp %s from the future",key?key:"NULL",obj?obj:"NULL",username.str(), requestTimestamp.str());
                    return SecAccess_None;//deny
                }

                CDateTime expiry;
                expiry.set(now);
                expiry.adjustTime(requestSignatureExpiryMinutes);//compute expiration timestamp

                if (expiry.compare(*reqUTCTimestamp) < 0)//timestamp too far in the past?
                {
                    ERRLOG("LDAP: getPermissions(%s) scope=%s user=%s Expired request digital signature timestamp %s",key?key:"NULL",obj?obj:"NULL",username.str(), requestTimestamp.str());
                    return SecAccess_None;//deny
                }

                VStringBuffer expectedStr("%s;%s;%s", obj, username.str(), requestTimestamp.str());
                StringBuffer b64Signature(reqSignature);// signature of scope;user;timestamp

                if (!pDSM->digiVerify(expectedStr, b64Signature))//does the digital signature match what we expect?
                {
                    ERRLOG("LDAP: getPermissions(%s) scope=%s user=%s fails digital signature verification",key?key:"NULL",obj?obj:"NULL",username.str());
                    return SecAccess_None;//deny
                }

                authenticated = true;//Digital signature verified
            }
            else
                ERRLOG("LDAP: getPermissions(%s) scope=%s user=%s digital signature support not available",key?key:"NULL",obj?obj:"NULL",username.str());
        }

        if (!authenticated && !ldapsecurity->authenticateUser(*user, NULL))
        {
            ERRLOG("LDAP: getPermissions(%s) scope=%s user=%s fails LDAP authentication",key?key:"NULL",obj?obj:"NULL",username.str());
            return SecAccess_None;//deny
        }

        bool filescope = stricmp(key,"Scope")==0;
        bool wuscope = stricmp(key,"workunit")==0;

        if (filescope || wuscope) {
            SecAccessFlags perm = SecAccess_None;
            unsigned start = msTick();
            if (filescope)
                perm=ldapsecurity->authorizeFileScope(*user, obj);
            else if (wuscope)
                perm=ldapsecurity->authorizeWorkunitScope(*user, obj);
            if (perm == SecAccess_Unavailable)
                perm = SecAccess_None;

            unsigned taken = msTick()-start;
#ifndef _DEBUG
            if (taken>100) 
#endif
            {
                PROGLOG("LDAP: getPermissions(%s) scope=%s user=%s returns %d in %d ms",key?key:"NULL",obj?obj:"NULL",username.str(),perm,taken);
            }
            if (auditflags&DALI_LDAP_AUDIT_REPORT) {
                StringBuffer auditstr;
                if ((auditflags&DALI_LDAP_READ_WANTED)&&!HASREADPERMISSION(perm)) 
                    auditstr.append("Lookup Access Denied");
                else if ((auditflags&DALI_LDAP_WRITE_WANTED)&&!HASWRITEPERMISSION(perm)) 
                    auditstr.append("Create Access Denied");
                if (auditstr.length()) {
                    auditstr.append(":\n\tProcess:\tdaserver");
                    auditstr.appendf("\n\tUser:\t%s",username.str());
                    auditstr.appendf("\n\tScope:\t%s\n",obj?obj:"");
                    SYSLOG(AUDIT_TYPE_ACCESS_FAILURE,auditstr.str());
                }
            }
            return perm;
        }
        return SecAccess_Full;
    }