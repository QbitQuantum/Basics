/**
 * Runtime-load the libpcap shared-object or the winpcap DLL. We
 * load at runtime rather than loadtime to allow this program to 
 * be used to process offline content, and to provide more helpful
 * messages to people who don't realize they need to install PCAP.
 */
void pcaplive_init(struct PCAPLIVE *pl)
{
#ifdef WIN32
	HMODULE hPacket;
	HMODULE hLibpcap;
	HMODULE hAirpcap;

	pl->is_available = 0;
	pl->is_printing_debug = 1;

	/* Look for the Packet.dll */
	hPacket = LoadLibraryA("Packet.dll");
	if (hPacket == NULL) {
		if (pl->is_printing_debug)
		switch (GetLastError()) {
		case ERROR_MOD_NOT_FOUND:
			fprintf(stderr, "%s: not found\n", "Packet.dll");
			return;
		default:
			fprintf(stderr, "%s: couldn't load %d\n", "Packet.dll", (int)GetLastError());
			return;
		}
	}

	/* Look for the Packet.dll */
	hLibpcap = LoadLibraryA("wpcap.dll");
	if (hLibpcap == NULL) {
		if (pl->is_printing_debug)
			fprintf(stderr, "%s: couldn't load %d\n", "wpcap.dll", (int)GetLastError());
		return;
	}

	/* Look for the Packet.dll */
	hAirpcap = LoadLibraryA("airpcap.dll");
	if (hLibpcap == NULL) {
		if (pl->is_printing_debug)
			fprintf(stderr, "%s: couldn't load %d\n", "airpcap.dll", (int)GetLastError());
		return;
	}

#define DOLINK(PCAP_DATALINK, datalink) \
	pl->datalink = (PCAP_DATALINK)GetProcAddress(hLibpcap, "pcap_"#datalink); \
	if (pl->datalink == NULL) pl->func_err=1, pl->datalink = null_##PCAP_DATALINK;
#endif


#ifndef WIN32
#ifndef STATICPCAP
	void *hLibpcap;
	unsigned initial_failure=0;

	pl->is_available = 0;
	pl->is_printing_debug = 1;

	hLibpcap = dlopen("libpcap.so", RTLD_LAZY);
	if (hLibpcap == NULL) {
		fprintf(stderr, "%s: %s\n", "libpcap.so", dlerror());
		fprintf(stderr, "Searching elsewhere for libpcap\n");
		initial_failure = 1;
	}

	if (hLibpcap==NULL)
		hLibpcap = dlopen("libpcap.so.0.9.5", RTLD_LAZY);
	if (hLibpcap==NULL)
		hLibpcap = dlopen("libpcap.so.0.9.4", RTLD_LAZY);
	if (hLibpcap==NULL)
		hLibpcap = dlopen("libpcap.so.0.8", RTLD_LAZY);
	if (hLibpcap==NULL)
		hLibpcap = dlopen("libpcap.A.dylib", RTLD_LAZY);
	if (hLibpcap == NULL) {
		if (pl->is_printing_debug) {
			fprintf(stderr, "%s: couldn't load %d (%s)\n", "libpcap.so", errno, strerror(errno));
		}
	} else if (initial_failure) {
		fprintf(stderr, "Found libpcap\n");
	}

#define DOLINK(PCAP_DATALINK, datalink) \
	pl->datalink = (PCAP_DATALINK)dlsym(hLibpcap, "pcap_"#datalink); \
	if (pl->datalink == NULL) pl->func_err=1, pl->datalink = null_##PCAP_DATALINK;
#else
#define DOLINK(PCAP_DATALINK, datalink) \
	pl->func_err=0, pl->datalink = null_##PCAP_DATALINK;
#endif
#endif

#ifdef WIN32
	DOLINK(PCAP_GET_AIRPCAP_HANDLE, get_airpcap_handle);
	if (pl->func_err) {
		pl->func_err = 0;
	}
	if (hAirpcap) {
		pl->airpcap_set_device_channel = (AIRPCAP_SET_DEVICE_CHANNEL)GetProcAddress(hAirpcap, "AirpcapSetDeviceChannel");
		if (pl->airpcap_set_device_channel == NULL)
			pl->airpcap_set_device_channel = null_AIRPCAP_SET_DEVICE_CHANNEL;
	}
#endif
	


	DOLINK(PCAP_CLOSE			, close);
	DOLINK(PCAP_DATALINK		, datalink);
	DOLINK(PCAP_DISPATCH		, dispatch);
	DOLINK(PCAP_FINDALLDEVS		, findalldevs);
	DOLINK(PCAP_FREEALLDEVS		, freealldevs);
	DOLINK(PCAP_LIB_VERSION		, lib_version);
	DOLINK(PCAP_LOOKUPDEV		, lookupdev);
	DOLINK(PCAP_MAJOR_VERSION	, major_version);
	DOLINK(PCAP_MINOR_VERSION	, minor_version);
	DOLINK(PCAP_OPEN_LIVE		, open_live);
	//DOLINK(PCAP_OPEN_LIVE		, open_live);

	pl->can_transmit = null_CAN_TRANSMIT;

	if (!pl->func_err)
		pl->is_available = 1;
	else
		pl->is_available = 0;
}