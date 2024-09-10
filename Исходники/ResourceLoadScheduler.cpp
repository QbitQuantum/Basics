void ResourceLoadScheduler::crossOriginRedirectReceived(ResourceLoader* resourceLoader, const KURL& redirectURL)
{
    HostInformation* oldHost = hostForURL(resourceLoader->url());
    ASSERT(oldHost);
    HostInformation* newHost = hostForURL(redirectURL, CreateIfNotFound);

    if (oldHost->name() == newHost->name())
        return;
    
    newHost->addLoadInProgress(resourceLoader);
    oldHost->remove(resourceLoader);
}