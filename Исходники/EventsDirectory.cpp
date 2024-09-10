bool CEventsDirectory::GetDirectory(const CURL& url, CFileItemList &items)
{
  items.ClearProperties();
  items.SetContent("events");

  CEventLog& log = CEventLog::GetInstance();
  Events events;

  std::string hostname = url.GetHostName();
  if (hostname.empty())
    events = log.Get();
  else
  {
    bool includeHigherLevels = false;
    // check if we should only retrieve events from a specific level or
    // also from all higher levels
    if (StringUtils::EndsWith(hostname, "+"))
    {
      includeHigherLevels = true;

      // remove the "+" from the end of the hostname
      hostname = hostname.substr(0, hostname.size() - 1);
    }

    EventLevel level = EventLevelFromString(hostname);

    // get the events of the specified level(s)
    events = log.Get(level, includeHigherLevels);
  }

  for (auto eventItem : events)
    items.Add(EventToFileItem(eventItem));

  return true;
}