/**
 * Called when SLP discovery completes.
 */
void SimpleE133Controller::DiscoveryCallback(bool ok, const URLEntries &urls) {
  if (ok) {
    URLEntries::const_iterator iter;
    UID uid(0, 0);
    IPV4Address ip;
    for (iter = urls.begin(); iter != urls.end(); ++iter) {
      OLA_INFO << "Located " << *iter;
      if (!ola::e133::ParseE133URL(iter->url(), &uid, &ip))
        continue;

      if (uid.IsBroadcast()) {
        OLA_WARN << "UID " << uid << "@" << ip << " is broadcast";
        continue;
      }
      AddUID(uid, ip);
    }
  }
  m_uid_list_updated = true;
  m_ss.Terminate();
}