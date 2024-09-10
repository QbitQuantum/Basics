bool oculusAvailable() {
    static std::once_flag once;
    static bool result { false };
    std::call_once(once, [&] {

        static const QString DEBUG_FLAG("HIFI_DEBUG_OPENVR");
        static bool enableDebugOpenVR = QProcessEnvironment::systemEnvironment().contains(DEBUG_FLAG);
        if (enableDebugOpenVR) {
            return;
        }

        ovrDetectResult detect = ovr_Detect(0);
        if (!detect.IsOculusServiceRunning || !detect.IsOculusHMDConnected) {
            return;
        }

        DWORD searchResult = SearchPathW(NULL, REQUIRED_OCULUS_DLL, NULL, MAX_PATH, FOUND_PATH, NULL);
        if (searchResult <= 0) {
            return;
        }

        result = true;
    });

    return result;
}