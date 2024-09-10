 StubDriver(const char *name, bool verbose = true) {
     settings.setPluginName(name);
     settings.setVerboseMode(verbose);
     YarpPluginSelector selector;
     selector.scan();
     if (!settings.setSelector(selector)) return;
     init();
 }