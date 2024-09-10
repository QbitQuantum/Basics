ARVRInterfaceGDNative::~ARVRInterfaceGDNative() {
	printf("Destruct gdnative interface\n");

	if (is_initialized()) {
		uninitialize();
	};

	// cleanup after ourselves
	cleanup();
}