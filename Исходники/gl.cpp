void InitializeExtensions(glProc (*getProcAddress)(const char *)) {
    std::call_once(initializeExtensionsOnce, [getProcAddress] {
        const char * extensionsPtr = reinterpret_cast<const char *>(
            MBGL_CHECK_ERROR(glGetString(GL_EXTENSIONS)));

        if (!extensionsPtr)
            return;

        const std::string extensions = extensionsPtr;
        for (auto fn : ExtensionFunctionBase::functions()) {
            for (auto probe : fn->probes) {
                if (extensions.find(probe.first) != std::string::npos) {
                    fn->ptr = getProcAddress(probe.second);
                    break;
                }
            }
        }
    });
}