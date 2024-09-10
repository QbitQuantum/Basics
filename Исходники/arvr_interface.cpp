void ARVRInterface::set_is_initialized(bool p_initialized) {
	if (p_initialized) {
		if (!is_initialized()) {
			initialize();
		};
	} else {
		if (is_initialized()) {
			uninitialize();
		};
	};
};