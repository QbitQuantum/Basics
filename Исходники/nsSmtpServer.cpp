NS_IMETHODIMP
nsSmtpServer::GetPassword(nsACString& aPassword)
{
    if (m_password.IsEmpty() && !m_logonFailed)
    {
      // try to avoid prompting the user for another password. If the user has set
      // the appropriate pref, we'll use the password from an incoming server, if
      // the user has already logged onto that server.

      // if this is set, we'll only use this, and not the other prefs
      // user_pref("mail.smtpserver.smtp1.incomingAccount", "server1");

      // if this is set, we'll accept an exact match of user name and server
      // user_pref("mail.smtp.useMatchingHostNameServer", true);

      // if this is set, and we don't find an exact match of user and host name,
      // we'll accept a match of username and domain, where domain
      // is everything after the first '.'
      // user_pref("mail.smtp.useMatchingDomainServer", true);

      nsCString accountKey;
      bool useMatchingHostNameServer = false;
      bool useMatchingDomainServer = false;
      mPrefBranch->GetCharPref("incomingAccount", getter_Copies(accountKey));

      nsCOMPtr<nsIMsgAccountManager> accountManager = do_GetService(NS_MSGACCOUNTMANAGER_CONTRACTID);
      nsCOMPtr<nsIMsgIncomingServer> incomingServerToUse;
      if (accountManager)
      {
        if (!accountKey.IsEmpty())
          accountManager->GetIncomingServer(accountKey, getter_AddRefs(incomingServerToUse));
        else
        {
          nsresult rv;
          nsCOMPtr<nsIPrefBranch> prefBranch(do_GetService(NS_PREFSERVICE_CONTRACTID, &rv));
          NS_ENSURE_SUCCESS(rv,rv);
          prefBranch->GetBoolPref("mail.smtp.useMatchingHostNameServer", &useMatchingHostNameServer);
          prefBranch->GetBoolPref("mail.smtp.useMatchingDomainServer", &useMatchingDomainServer);
          if (useMatchingHostNameServer || useMatchingDomainServer)
          {
            nsCString userName;
            nsCString hostName;
            GetHostname(hostName);
            GetUsername(userName);
            if (useMatchingHostNameServer)
              // pass in empty type and port=0, to match imap and pop3.
              accountManager->FindRealServer(userName, hostName, EmptyCString(), 0, getter_AddRefs(incomingServerToUse));
            int32_t dotPos = -1;
            if (!incomingServerToUse && useMatchingDomainServer
              && (dotPos = hostName.FindChar('.')) != kNotFound)
            {
              hostName.Cut(0, dotPos);
              nsCOMPtr<nsISupportsArray> allServers;
              accountManager->GetAllServers(getter_AddRefs(allServers));
              if (allServers)
              {
                uint32_t count = 0;
                allServers->Count(&count);
                uint32_t i;
                for (i = 0; i < count; i++)
                {
                  nsCOMPtr<nsIMsgIncomingServer> server = do_QueryElementAt(allServers, i);
                  if (server)
                  {
                    nsCString serverUserName;
                    nsCString serverHostName;
                    server->GetRealUsername(serverUserName);
                    server->GetRealHostName(serverHostName);
                    if (serverUserName.Equals(userName))
                    {
                      int32_t serverDotPos = serverHostName.FindChar('.');
                      if (serverDotPos != kNotFound)
                      {
                        serverHostName.Cut(0, serverDotPos);
                        if (serverHostName.Equals(hostName))
                        {
                          incomingServerToUse = server;
                          break;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (incomingServerToUse)
        return incomingServerToUse->GetPassword(aPassword);
    }
    aPassword = m_password;
    return NS_OK;
}