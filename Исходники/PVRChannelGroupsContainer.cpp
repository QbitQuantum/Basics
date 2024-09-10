bool CPVRChannelGroupsContainer::FilterDirectory(const CURL &url, CFileItemList &results) const
{
    if (!results.IsEmpty())
    {
        if (url.HasOption("view"))
        {
            const std::string view(url.GetOption("view"));
            if (view == "lastplayed")
            {
                // remove channels never played so far
                for (int i = 0; i < results.Size(); ++i)
                {
                    const CPVRChannelPtr channel(results.Get(i)->GetPVRChannelInfoTag());
                    time_t lastWatched = channel->LastWatched();
                    if (!lastWatched)
                    {
                        results.Remove(i);
                        --i;
                    }
                }
            }
            else
            {
                CLog::Log(LOGERROR, "CPVRChannelGroupsContainer - %s - unsupported value '%s' for url parameter 'view'", __FUNCTION__, view.c_str());
                return false;
            }
        }
    }
    return true;
}