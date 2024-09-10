void* createInstance(ServiceFunc* serviceFunc) {
    DbgEngPlugin* plugin = new DbgEngPlugin;

    HRESULT hr = DebugCreate(__uuidof(IDebugClient), (void**)&plugin->debugClient);
    assert(SUCCEEDED(hr));

    hr = plugin->debugClient->SetEventCallbacks(plugin);
    assert(SUCCEEDED(hr));

    hr = plugin->debugClient->QueryInterface(__uuidof(IDebugControl), (void**)&plugin->debugControl);
    assert(SUCCEEDED(hr));

    return plugin;
}