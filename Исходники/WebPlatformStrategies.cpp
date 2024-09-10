void WebPlatformStrategies::getWebVisiblePluginInfo(const Page* page, Vector<PluginInfo>& plugins)
{
    ASSERT_ARG(page, page);
    ASSERT_ARG(plugins, plugins.isEmpty());

    getPluginInfo(page, plugins);

#if PLATFORM(MAC)
    if (Document* document = page->mainFrame().document()) {
        if (SecurityOrigin* securityOrigin = document->securityOrigin()) {
            if (securityOrigin->isLocal())
                return;
        }
    }
    
    for (int32_t i = plugins.size() - 1; i >= 0; --i) {
        PluginInfo& info = plugins.at(i);
        PluginLoadClientPolicy clientPolicy = info.clientLoadPolicy;
        // Allow built-in plugins. Also tentatively allow plugins that the client might later selectively permit.
        if (info.isApplicationPlugin || clientPolicy == PluginLoadClientPolicyAsk)
            continue;

        if (clientPolicy == PluginLoadClientPolicyBlock)
            plugins.remove(i);
    }
#endif
}