void MasterRegistration::PerformRegistration() {
  AvahiEntryGroup *group = NULL;
  if (m_entry_group) {
    group = m_entry_group;
    m_entry_group = NULL;
  } else {
    group = m_client->CreateEntryGroup(entry_group_callback, this);
    if (!group) {
      OLA_WARN << "avahi_entry_group_new() failed: "
               << m_client->GetLastError();
      return;
    }
  }

  if (!AddGroupEntry(group)) {
    avahi_entry_group_free(group);
  } else {
    m_entry_group = group;
  }
}