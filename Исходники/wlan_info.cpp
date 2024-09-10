int cgiMain() {
	ConfigCommon cfg;
	getProperty gPc(gPc.P_OTC);
	getProperty gPs(gPs.P_SCAN);
	int i = gPs.getInt(INTERF);
	getInfo();
	
	cfg.putHeader("Pegasus Wireless CYNALYNX - Information");
	cfg.startPage("Information","The information on this page shows the current system status and settings.");
	cfg.putSubtitle("Current connectivity information");
	cfg.dispRow("Radio MAC address", glbStr[MAC]);
	cfg.dispRow("Current IP address", glbStr[IP]);
	cfg.dispRow("Current Channel", gPs.getStr(CHANNEL));
	if (i == 0)
	cfg.dispRow("RF activities detected", gPs.getStr(RFDETECT), true);
	else
	cfg.dispRow("RF activities detected", cfg.getFValue("%s &nbsp;&nbsp;&nbsp;</font> <font class=f1 color=red>WARNING:Interference",  gPs.getStr(RFDETECT)), true);
	cfg.skipRow();
	cfg.dispRow("Moderator IP", glbStr[MODERATOR]);
	cfg.dispRow("PSM IP address", glbStr[PSM]);
	cfg.skipRow();
	cfg.putSubtitle("Current configuration setting");
	cfg.dispRow("Device name", gPc.getStr(DEVICENAME));
	cfg.dispRow("SSID", gPs.getStr(SSID));
	cfg.dispRow("Radio Mode", gPs.getStr(MODE)); 
	cfg.skipRow();
	cfg.dispRow("IP address", gPc.getStr(IPADDR)); 
	cfg.dispRow("Subnet mask", gPc.getStr(IPMASK)); 
	cfg.dispRow("Default gateway", gPc.getStr(GATEWAY)); 
	cfg.endPage();
	return 0;
}