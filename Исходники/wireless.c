void find_wireless_nic(void)
{
	static int found = 0;
	FILE *file;
	int sock;
	struct ifreq ifr;
	struct ethtool_value ethtool;
	struct ethtool_drvinfo driver;
	int ret;

	if (found++)
		return;

	wireless_nic[0] = 0;
	rfkill_path[0] = 0;
	powersave_path[0] = 0;

	strcpy(wireless_nic, "wlan0");

	file = popen("/sbin/iwpriv -a 2> /dev/null", "r");
	if (!file)
		return;
	while (!feof(file)) {
		char line[1024];
		memset(line, 0, 1024);
		if (fgets(line, 1023, file)==NULL)
			break;
		if (strstr(line, "get_power:Power save level")) {
			char *c;
			c = strchr(line, ' ');
			if (c) *c = 0;
			strcpy(wireless_nic, line);
		}
		if (strstr(line, "wlan0:"))
			strcpy(wireless_nic, "wlan0");
	}
	pclose(file);


	if (strlen(wireless_nic)==0)
		return;


	memset(&ifr, 0, sizeof(struct ifreq));
	memset(&ethtool, 0, sizeof(struct ethtool_value));

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock<0)
		return;

	strcpy(ifr.ifr_name, wireless_nic);

	/* Check if the interface is up */
	ret = ioctl(sock, SIOCGIFFLAGS, &ifr);
	if (ret<0) {
		close(sock);
		return;
	}

	memset(&driver, 0, sizeof(driver));
	driver.cmd = ETHTOOL_GDRVINFO;
        ifr.ifr_data = (void*) &driver;
        ret = ioctl(sock, SIOCETHTOOL, &ifr);

	sprintf(rfkill_path,"/sys/bus/pci/devices/%s/rfkill/rfkill0/state", driver.bus_info);
	sprintf(powersave_path,"/sys/bus/pci/devices/%s/power_level", driver.bus_info);
	close(sock);
}