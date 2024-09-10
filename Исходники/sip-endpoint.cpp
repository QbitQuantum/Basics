SIPURL Opal::Sip::EndPoint::GetRegisteredPartyName (const SIPURL & host)
{
  PString local_address;
  PIPSocket::Address address;
  WORD port;
  PString url;
  SIPURL registration_address;

  /* If we are registered to an account corresponding to host, use it.
  */
  PSafePtr<SIPHandler> info = activeSIPHandlers.FindSIPHandlerByDomain(host.GetHostName (), SIP_PDU::Method_REGISTER, PSafeReadOnly);
  if (info != NULL) {

    return SIPURL ("\"" + GetDefaultDisplayName () + "\" <" + info->GetTargetAddress ().AsString () + ">");
  }
  else {

    /* If we are not registered to host, 
     * then use the default account as outgoing identity.
     * If we are exchanging messages with a peer on our network,
     * then do not use the default account as outgoing identity.
     */
    if (host.GetHostAddress ().GetIpAndPort (address, port) && !manager.IsLocalAddress (address)) {

      Ekiga::Account *account = account_core.find_account ("ekiga.net");

      if (account)
        return SIPURL ("\"" + GetDefaultDisplayName () + "\" <" + PString(account->get_aor ()) + ">");
    }
  }

  /* As a last resort, ie not registered to host, no default account or
   * dialog with a local peer, then use the local address 
   */
  return GetDefaultRegisteredPartyName ();
}