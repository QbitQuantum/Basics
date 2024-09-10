void WebPluginInfoProvider::getWebVisiblePluginInfo(WebCore::Page& page, Vector<WebCore::PluginInfo>& plugins)
{
    ASSERT_ARG(plugins, plugins.isEmpty());

    getPluginInfo(page, plugins);

#if PLATFORM(MAC)
    if (auto* document = page.mainFrame().document()) {
        if (auto* securityOrigin = document->securityOrigin()) {
            if (securityOrigin->isLocal())
                return;
        }
    }

    for (int32_t i = plugins.size() - 1; i >= 0; --i) {
        auto& info = plugins.at(i);

        // Allow built-in plugins. Also tentatively allow plugins that the client might later selectively permit.
        if (info.isApplicationPlugin || info.clientLoadPolicy == WebCore::PluginLoadClientPolicyAsk)
            continue;

        if (info.clientLoadPolicy == WebCore::PluginLoadClientPolicyBlock)
            plugins.remove(i);
    }
#endif
}