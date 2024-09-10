void WebProcessConnection::destroyPlugin(uint64_t pluginInstanceID, bool asynchronousCreationIncomplete, PassRefPtr<Messages::WebProcessConnection::DestroyPlugin::DelayedReply> reply)
{
    // We return immediately from this synchronous IPC. We want to make sure the plugin destruction is just about to start so audio playback
    // will finish soon after returning. However we don't want to wait for destruction to complete fully as that may take a while.
    reply->send();

    // Ensure we don't clamp any timers during destruction
    ActivityAssertion activityAssertion(PluginProcess::singleton().connectionActivity());

    PluginControllerProxy* pluginControllerProxy = m_pluginControllers.get(pluginInstanceID);
    
    // If there is no PluginControllerProxy then this plug-in doesn't exist yet and we probably have nothing to do.
    if (!pluginControllerProxy) {
        // If the plugin we're supposed to destroy was requested asynchronously and doesn't exist yet,
        // we need to flag the instance ID so it is not created later.
        if (asynchronousCreationIncomplete)
            m_asynchronousInstanceIDsToIgnore.add(pluginInstanceID);
        
        return;
    }
    
    destroyPluginControllerProxy(pluginControllerProxy);
}