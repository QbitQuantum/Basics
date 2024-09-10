int wmain(int argc, wchar_t* argv[])
{
    HRESULT hr = S_OK;
    HANDLE completionEvent = NULL;
    IXpsPrintJob* job = NULL;
    IXpsPrintJobStream* jobStream = NULL;
    IXpsOMObjectFactory* xpsFactory = NULL;
    IOpcPartUri* partUri = NULL;
    IXpsOMPackageWriter* packageWriter = NULL;
    XPS_SIZE pageSize = {816, 1056};
    IXpsOMPage* xpsPage = NULL;
    IXpsOMFontResource* fontResource = NULL;
    XPS_POINT origin = {50.0f, 200.0f};
    XPS_JOB_STATUS jobStatus = {};

    if (argc < 2 || argc > 3)
    {
        Usage(argv[0]);
        return 1;
    }

    if (FAILED(hr = CoInitializeEx(0, COINIT_MULTITHREADED)))
    {
        fwprintf(stderr, L"ERROR: CoInitializeEx failed with HRESULT 0x%X\n", hr);
        return 1;
    }

    if (SUCCEEDED(hr))
    {
        completionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (!completionEvent)
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
            fwprintf(stderr, L"ERROR: Could not create competion event: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = StartXpsPrintJob(
                    argv[1],
                    NULL,
                    argc == 3 ? argv[2] : NULL,
                    NULL,
                    completionEvent,
                    NULL,
                    0,
                    &job,
                    &jobStream,
                    NULL
                    )))
        {
            fwprintf(stderr, L"ERROR: Could not start XPS print job: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = CoCreateInstance(
                    __uuidof(XpsOMObjectFactory),
                    NULL,
                    CLSCTX_INPROC_SERVER,
                    __uuidof(IXpsOMObjectFactory),
                    reinterpret_cast<void**>(&xpsFactory)
                    )
                )
            )
        {
            fwprintf(stderr, L"ERROR: Could not create XPS OM Object Factory: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = xpsFactory->CreatePartUri(L"/FixedDocumentSequence.fdseq", &partUri)))
        {
            fwprintf(stderr, L"ERROR: Could not create part URI: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = xpsFactory->CreatePackageWriterOnStream(
                    jobStream,
                    TRUE,
                    XPS_INTERLEAVING_ON,
                    partUri,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    &packageWriter
                    )
                )
           )
        {
            fwprintf(stderr, L"ERROR: Could not create package writer: 0x%X\n", hr);
        }
    }

    if (partUri)
    {
        partUri->Release();
        partUri = NULL;
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = xpsFactory->CreatePartUri(L"/Documents/1/FixedDocument.fdoc", &partUri)))
        {
            fwprintf(stderr, L"ERROR: Could not create part URI: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = packageWriter->StartNewDocument(partUri, NULL, NULL, NULL, NULL)))
        {
            fwprintf(stderr, L"ERROR: Could not start new document: 0x%X\n", hr);
        }
    }

    if (partUri)
    {
        partUri->Release();
        partUri = NULL;
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = xpsFactory->CreatePartUri(L"/Documents/1/Pages/1.fpage", &partUri)))
        {
            fwprintf(stderr, L"ERROR: Could not create part URI: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = xpsFactory->CreatePage(&pageSize, L"en-US", partUri, &xpsPage)))
        {
            fwprintf(stderr, L"ERROR: Could not create page: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = CreateFontResourceForFont(xpsFactory, g_fontName, &fontResource)))
        {
            // Error already reported.
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = AddGlyphs(
                    xpsFactory,
                    xpsPage,
                    fontResource,
                    L"XPS",
                    &origin,
                    72.0f,
                    XPS_STYLE_SIMULATION_NONE)))
        {
            // Error already reported.
        }
    }

    if (SUCCEEDED(hr))
    {
        origin.x = 420.0f;
        origin.y = 300.0f;

        if (FAILED(hr = AddGlyphs(
                    xpsFactory,
                    xpsPage,
                    fontResource,
                    L"Print with Confidence",
                    &origin,
                    36.0f,
                    XPS_STYLE_SIMULATION_ITALIC)))
        {
            // Error already reported.
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = packageWriter->AddPage(
                    xpsPage,
                    &pageSize,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                    )))
        {
            fwprintf(stderr, L"ERROR: Could not add page to document: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = packageWriter->Close()))
        {
            fwprintf(stderr, L"ERROR: Could not close package writer: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = jobStream->Close()))
        {
            fwprintf(stderr, L"ERROR: Could not close job stream: %08X\n", hr);
        }
    }
    else
    {
        // Only cancel the job if we succeeded in creating one in the first place.
        if (job)
        {
            // Tell the XPS Print API that we're giving up.  Don't overwrite hr with the return from
            // this function.
            job->Cancel();
        }
    }


    if (SUCCEEDED(hr))
    {
        wprintf(L"Waiting for job completion...\n");

        if (WaitForSingleObject(completionEvent, INFINITE) != WAIT_OBJECT_0)
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
            fwprintf(stderr, L"ERROR: Wait for completion event failed: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        if (FAILED(hr = job->GetJobStatus(&jobStatus)))
        {
            fwprintf(stderr, L"ERROR: Could not get job status: %08X\n", hr);
        }
    }

    if (SUCCEEDED(hr))
    {
        switch (jobStatus.completion)
        {
            case XPS_JOB_COMPLETED:
                break;
            case XPS_JOB_CANCELLED:
                fwprintf(stderr, L"ERROR: job was cancelled\n");
                hr = E_FAIL;
                break;
            case XPS_JOB_FAILED:
                fwprintf(stderr, L"ERROR: Print job failed: %08X\n", jobStatus.jobStatus);
                hr = E_FAIL;
                break;
            default:
                fwprintf(stderr, L"ERROR: unexpected failure\n");
                hr = E_UNEXPECTED;
                break;
        }
    }

    if (SUCCEEDED(hr))
    {
        wprintf(L"Done!\n");
    }

    if (fontResource)
    {
        fontResource->Release();
        fontResource = NULL;
    }

    if (xpsPage)
    {
        xpsPage->Release();
        xpsPage = NULL;
    }

    if (packageWriter)
    {
        packageWriter->Release();
        packageWriter = NULL;
    }

    if (partUri)
    {
        partUri->Release();
        partUri = NULL;
    }

    if (xpsFactory)
    {
        xpsFactory->Release();
        xpsFactory = NULL;
    }

    if (jobStream)
    {
        jobStream->Release();
        jobStream = NULL;
    }

    if (job)
    {
        job->Release();
        job = NULL;
    }

    if (completionEvent)
    {
        CloseHandle(completionEvent);
        completionEvent = NULL;
    }

    CoUninitialize();

    return SUCCEEDED(hr) ? 0 : 1;
}