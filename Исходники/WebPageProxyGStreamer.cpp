void WebPageProxy::requestInstallMissingMediaPlugins(const String& details)
{
    CString detail = details.utf8();
    const char* detailArray[2] = { detail.data(), nullptr };
    ref();
    GUniquePtr<GstInstallPluginsContext> context = m_pageClient.createGstInstallPluginsContext();
    GstInstallPluginsReturn result = gst_install_plugins_async(detailArray, context.get(), [](GstInstallPluginsReturn result, gpointer userData) {
        RefPtr<WebPageProxy> page = adoptRef(static_cast<WebPageProxy*>(userData));
        if (page->isValid())
            page->send(Messages::WebPage::DidEndRequestInstallMissingMediaPlugins(static_cast<uint32_t>(result)));
    }, this);

    if (result != GST_INSTALL_PLUGINS_STARTED_OK) {
        // If the installer didn't start, the callback will not be called, so remove the ref manually.
        deref();
        send(Messages::WebPage::DidEndRequestInstallMissingMediaPlugins(static_cast<uint32_t>(result)));
        WTFLogAlways("Missing GStreamer Plugin: %s\n", detail.data());
    }
}