int
content_process_main(int argc, char* argv[])
{
    // Check for the absolute minimum number of args we need to move
    // forward here. We expect the last arg to be the child process type.
    if (argc < 1) {
      return 3;
    }

    bool isNuwa = false;
    for (int i = 1; i < argc; i++) {
        isNuwa |= strcmp(argv[i], "-nuwa") == 0;
    }

    XREChildData childData;

#if defined(XP_WIN) && defined(MOZ_SANDBOX)
    if (IsSandboxedProcess()) {
        childData.sandboxTargetServices =
            mozilla::sandboxing::GetInitializedTargetServices();
        if (!childData.sandboxTargetServices) {
            return 1;
        }

        childData.ProvideLogFunction = mozilla::sandboxing::ProvideLogFunction;
    }
#endif

    XRE_SetProcessType(argv[--argc]);

#ifdef MOZ_NUWA_PROCESS
    if (isNuwa) {
        PrepareNuwaProcess();
    }
#endif

#if defined(XP_LINUX) && defined(MOZ_SANDBOX)
    // This has to happen while we're still single-threaded, and on
    // B2G that means before the Android Binder library is
    // initialized.  Additional special handling is needed for Nuwa:
    // the Nuwa process itself needs to be unsandboxed, and the same
    // single-threadedness condition applies to its children; see also
    // AfterNuwaFork().
    mozilla::SandboxEarlyInit(XRE_GetProcessType(), isNuwa);
#endif

#ifdef MOZ_WIDGET_GONK
    // This creates a ThreadPool for binder ipc. A ThreadPool is necessary to
    // receive binder calls, though not necessary to send binder calls.
    // ProcessState::Self() also needs to be called once on the main thread to
    // register the main thread with the binder driver.

#ifdef MOZ_NUWA_PROCESS
    if (!isNuwa) {
        InitializeBinder(nullptr);
    } else {
        NuwaAddFinalConstructor(&InitializeBinder, nullptr);
    }
#else
    InitializeBinder(nullptr);
#endif
#endif

#ifdef XP_WIN
    // For plugins, this is done in PluginProcessChild::Init, as we need to
    // avoid it for unsupported plugins.  See PluginProcessChild::Init for
    // the details.
    if (XRE_GetProcessType() != GeckoProcessType_Plugin) {
        mozilla::SanitizeEnvironmentVariables();
        SetDllDirectoryW(L"");
    }
#endif
#if !defined(MOZ_WIDGET_ANDROID) && !defined(MOZ_WIDGET_GONK) && defined(MOZ_PLUGIN_CONTAINER)
    // On desktop, the GMPLoader lives in plugin-container, so that its
    // code can be covered by an EME/GMP vendor's voucher.
    nsAutoPtr<mozilla::gmp::SandboxStarter> starter(MakeSandboxStarter());
    if (XRE_GetProcessType() == GeckoProcessType_GMPlugin) {
        childData.gmpLoader = mozilla::gmp::CreateGMPLoader(starter);
    }
#endif
    nsresult rv = XRE_InitChildProcess(argc, argv, &childData);
    NS_ENSURE_SUCCESS(rv, 1);

    return 0;
}