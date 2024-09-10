AppxEngine::AppxEngine(Runner *runner, AppxEnginePrivate *dd)
    : d_ptr(dd)
{
    Q_D(AppxEngine);
    if (d->hasFatalError)
        return;

    d->runner = runner;
    d->processHandle = NULL;
    d->pid = -1;
    d->exitCode = UINT_MAX;

    if (!getManifestFile(runner->app(), &d->manifest)) {
        qCWarning(lcWinRtRunner) << "Unable to determine manifest file from" << runner->app();
        d->hasFatalError = true;
        return;
    }

    HRESULT hr;
    hr = RoGetActivationFactory(HString::MakeReference(RuntimeClass_Windows_Foundation_Uri).Get(),
                                IID_PPV_ARGS(&d->uriFactory));
    CHECK_RESULT_FATAL("Failed to instantiate URI factory.", return);

    hr = CoCreateInstance(CLSID_AppxFactory, nullptr, CLSCTX_INPROC_SERVER,
                          IID_IAppxFactory, &d->packageFactory);
    CHECK_RESULT_FATAL("Failed to instantiate package factory.", return);

    ComPtr<IStream> manifestStream;
    hr = SHCreateStreamOnFile(wchar(d->manifest), STGM_READ, &manifestStream);
    CHECK_RESULT_FATAL("Failed to open manifest stream.", return);

    ComPtr<IAppxManifestReader> manifestReader;
    hr = d->packageFactory->CreateManifestReader(manifestStream.Get(), &manifestReader);
    if (FAILED(hr)) {
        qCWarning(lcWinRtRunner).nospace() << "Failed to instantiate manifest reader. (0x"
                                           << QByteArray::number(hr, 16).constData()
                                           << ' ' << qt_error_string(hr) << ')';
        // ### TODO: read detailed error from event log directly
        if (hr == APPX_E_INVALID_MANIFEST) {
            qCWarning(lcWinRtRunner) << "More information on the error can "
                                      "be found in the event log under "
                                      "Microsoft\\Windows\\AppxPackagingOM";
        }
        d->hasFatalError = true;
        return;
    }

    ComPtr<IAppxManifestPackageId> packageId;
    hr = manifestReader->GetPackageId(&packageId);
    CHECK_RESULT_FATAL("Unable to obtain the package ID from the manifest.", return);

    APPX_PACKAGE_ARCHITECTURE arch;
    hr = packageId->GetArchitecture(&arch);
    CHECK_RESULT_FATAL("Failed to retrieve the app's architecture.", return);
    d->packageArchitecture = toProcessorArchitecture(arch);

    LPWSTR packageFullName;
    hr = packageId->GetPackageFullName(&packageFullName);
    CHECK_RESULT_FATAL("Unable to obtain the package full name from the manifest.", return);
    d->packageFullName = QString::fromWCharArray(packageFullName);
    CoTaskMemFree(packageFullName);

    LPWSTR packageFamilyName;
    hr = packageId->GetPackageFamilyName(&packageFamilyName);
    CHECK_RESULT_FATAL("Unable to obtain the package full family name from the manifest.", return);
    d->packageFamilyName = QString::fromWCharArray(packageFamilyName);
    CoTaskMemFree(packageFamilyName);

    ComPtr<IAppxManifestApplicationsEnumerator> applications;
    hr = manifestReader->GetApplications(&applications);
    CHECK_RESULT_FATAL("Failed to get a list of applications from the manifest.", return);

    BOOL hasCurrent;
    hr = applications->GetHasCurrent(&hasCurrent);
    CHECK_RESULT_FATAL("Failed to iterate over applications in the manifest.", return);

    // For now, we are only interested in the first application
    ComPtr<IAppxManifestApplication> application;
    hr = applications->GetCurrent(&application);
    CHECK_RESULT_FATAL("Failed to access the first application in the manifest.", return);

    LPWSTR executable;
    application->GetStringValue(L"Executable", &executable);
    CHECK_RESULT_FATAL("Failed to retrieve the application executable from the manifest.", return);
    d->executable = QFileInfo(d->manifest).absoluteDir()
            .absoluteFilePath(QString::fromWCharArray(executable));
    CoTaskMemFree(executable);

    ComPtr<IAppxManifestPackageDependenciesEnumerator> dependencies;
    hr = manifestReader->GetPackageDependencies(&dependencies);
    CHECK_RESULT_FATAL("Failed to retrieve the package dependencies from the manifest.", return);

    hr = dependencies->GetHasCurrent(&hasCurrent);
    CHECK_RESULT_FATAL("Failed to iterate over dependencies in the manifest.", return);
    while (SUCCEEDED(hr) && hasCurrent) {
        ComPtr<IAppxManifestPackageDependency> dependency;
        hr = dependencies->GetCurrent(&dependency);
        CHECK_RESULT_FATAL("Failed to access dependency in the manifest.", return);

        LPWSTR name;
        hr = dependency->GetName(&name);
        CHECK_RESULT_FATAL("Failed to access dependency name.", return);
        d->dependencies.insert(QString::fromWCharArray(name));
        CoTaskMemFree(name);
        hr = dependencies->MoveNext(&hasCurrent);
    }
}