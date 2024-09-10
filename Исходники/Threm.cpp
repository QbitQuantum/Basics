void Threm::start() {
	_thremContext->isStarted = true;

#ifdef LOG
	LOG << "Threm::start" << endl;
	LOG << "Free heap " << ESP.getFreeHeap() << endl;
#endif

	spiffsOk = SPIFFS.begin();

	if (!spiffsOk) {
#ifdef LOG
		LOG << "SPIFFS failed" << endl;
#endif
	}

	ESP8266WebServer* server = _thremContext->getServer();

	IThremPlugin* plugin;
	PluginMeta* meta;

	for (int i = 0; i < _plugins->size(); i++) {
		plugin = _plugins->get(i);
		bool canEnable = true;
		int pluginId = plugin->getUniqueId();
		{
			String state = getJsonStateFor(pluginId);
			yield();

			StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
			JsonObject& root = jsonBuffer.parseObject(state);
			if (!root.success()) {
#ifdef LOG
				LOG << "Failed to parse config for " << String(plugin->getUniqueId()) << endl;
#endif
			}
			else {
				bool isDisabled = root["off"];
				if (isDisabled) {
					canEnable = false;
				}
			}

			if (canEnable) {
				canEnable = plugin->init(_thremContext, root);
			}
		}



		meta = _pluginMeta->get(i);
		meta->isEnabled = canEnable;
#ifdef DEBUG
		DEBUG << String(plugin->getName()) << " enabled=" << canEnable << endl;
#endif
		_pluginMeta->set(i, meta);

		yield();
	}
#ifdef DEBUG
	DEBUG << "Plugins declared: " << _plugins->size() << endl;
#endif

#ifdef LOG
	LOG << getJsonState() << endl;
#endif

#ifdef DEBUG
	DEBUG << "default callbacks setup." << endl;
#endif

	server->onNotFound([=](){
		IThremPlugin*plugin;
		PluginMeta* meta;

		String uri = server->uri();
		for (int i = 0; i < _plugins->size(); i++) {
			plugin = _plugins->get(i);
			meta = _pluginMeta->get(i);
			if (meta->isEnabled) {
				if (plugin->handleNotFound(_thremContext, uri)) {
#ifdef LOG
					LOG << "NotFound handled by: " << plugin->getName() << endl;
#endif
					return;
				}
			}
		}

		String message = "File Not Found\n\n";
		message += "URI: ";
		message += server->uri();
		message += "\nMethod: ";
		message += (server->method() == HTTP_GET) ? "GET" : "POST";
		message += "\nArguments: ";
		message += server->args();
		message += "\n";

		for (uint8_t i = 0; i < server->args(); i++) {
			message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
		}
		server->sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
		server->sendHeader("Pragma", "no-cache");
		server->sendHeader("Expires", "-1");
		server->send(404, "text/plain", message);
	});
#ifdef DEBUG
	DEBUG << "Starting webserver." << endl;
#endif
	server->begin();
#ifdef DEBUG
	DEBUG << "Web server started." << endl;
#endif
	}