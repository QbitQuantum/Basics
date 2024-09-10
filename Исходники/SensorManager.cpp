void SensorManager::retrieveStatistics(bool ignoreshutdown)
{
	const char* xmlpre = "<vermont>\n\t<sensorData time=\"%s\" host=\"%s\">\n";
	const char* xmlpost = "\t</sensorData>\n</vermont>\n";
	const char* xmlglobals = "\t\t<%s>%s</%s>\n";

	string lockfile = outputFilename + ".lock";

	// we must not wait for the graph lock, else there may be a race condition with
	// the ConfigManager
	while (!graphIS->tryLockGraph()) {
		if (smExitFlag) break;
		timespec timeout = { 0, 200000 };
		nanosleep(&timeout, NULL);
	}

	if (!ignoreshutdown && smExitFlag) return;

	const char* openflags = (append ? "a" : "w");
	FILE* file = fopen(outputFilename.c_str(), openflags);
	if (!file) {
		THROWEXCEPTION("failed to reopen file %s", outputFilename.c_str());
		perror("error:");
	}

	time_t curtime = time(0);
	char curtimestr[100];
	ctime_r(&curtime, curtimestr);
	curtimestr[strlen(curtimestr)-1] = 0;
	fprintf(file, xmlpre, curtimestr, hostname);
	char text[100];
	snprintf(text, 100, "%u", static_cast<uint32_t>(getpid()));
	fprintf(file, xmlglobals, "pid", text, "pid");
	char lasttimestr[100];
	ctime_r(&lasttime, lasttimestr);
	lasttimestr[strlen(lasttimestr)-1] = 0;
	fprintf(file, xmlglobals, "lastTime", lasttimestr, "lastTime");

#if defined(__linux__)
	const char* xmlglobalsuint = "\t\t<%s>%u</%s>\n";
	ThreadCPUInterface::SystemInfo si = ThreadCPUInterface::getSystemInfo();

	fprintf(file, "\t\t<jiffyFrequency>%llu</jiffyFrequency>\n", hertzValue);
	fprintf(file, xmlglobalsuint, "processorAmount", si.noCPUs, "processorAmount");
	for (uint16_t i=0; i<si.sysJiffies.size(); i++) {
		double sysutil = (si.sysJiffies[i]-lastSystemInfo.sysJiffies[i])/(static_cast<double>(curtime)-lasttime)/hertzValue*100;
		double userutil = (si.userJiffies[i]-lastSystemInfo.userJiffies[i])/(static_cast<double>(curtime)-lasttime)/hertzValue*100;
		fprintf(file, "\t\t<processor id=\"%u\"><util type=\"system\">%.2f</util><util type=\"user\">%.2f</util></processor>\n",
				i, sysutil, userutil);
	}
	fprintf(file, "\t\t<memory><free type=\"bytes\">%llu</free><total type=\"bytes\">%llu</total></memory>\n",
			si.freeMemory, si.totalMemory);
	lastSystemInfo = si;
#endif

	//DPRINTF("*** sensor data at %s", ctime(&curtime));

	Graph* g = graphIS->getGraph();
	vector<CfgNode*> nodes = g->getNodes();
	vector<CfgNode*>::iterator iter = nodes.begin();
	while (iter != nodes.end()) {
		Cfg* cfg = (*iter)->getCfg();
		Sensor* s = cfg->getInstance();
		vector<uint32_t> nextids = cfg->getNext();
		writeSensorXML(file, s, cfg->getName().c_str(), cfg->getID(), true, curtime, lasttime, &nextids);

		iter++;
	}

	// iterate through all non-module sensors
	mutex.lock();
	list<SensorEntry>::const_iterator siter = sensors.begin();
	while (siter != sensors.end()) {
		writeSensorXML(file, siter->sensor, siter->name.c_str(), siter->id, false, curtime, lasttime, NULL);
		siter++;
	}
	mutex.unlock();

	fprintf(file, "%s", xmlpost);
	fclose(file);



	graphIS->unlockGraph();
}