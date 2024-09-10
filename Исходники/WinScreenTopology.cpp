ofRectangle ScreenTopology::getScreenRect(int index) {
	int numMonitors = GetSystemMetrics (SM_CMONITORS);
    printf("we have %d monitors\n", numMonitors);
    vector<ofRectangle> monitors;
    if(EnumDisplayMonitors(NULL, NULL, monitorEnumFunc, (LPARAM)&monitors)) {
		return monitors[index];
    }
	return ofRectangle();
}