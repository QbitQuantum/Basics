void touchmind::print::XPSPrint::_PrintMapModel(const touchmind::model::MapModel *pMapModel)
{
    HRESULT hr = S_OK;

    auto node = pMapModel->GetRootNodeModel();
    XPSGeometryBuilder::CalculateTransformMatrix(m_pageSize, m_xpsMargin, node, m_xpsMatrix, m_scale);
    _CreateCanvas();

    m_pTextRenderer = nullptr;
    CHK_HR(XpsDWriteTextRenderer::CreateInstance(m_pXpsFactory, &m_pTextRenderer));
    m_pTextRenderer->SetXpsCanvas(m_pXpsCanvas);
    m_pTextRenderer->SetXpsDictionary(m_pXpsDictionary);
    m_pTextRenderer->SetXpsResources(m_pXpsResources);

    _PrintNodes(node);
    _PrintLinks(pMapModel);

    HANDLE completionEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
    CHK_FATAL_NULL(completionEvent);

    IXpsPrintJob *job = nullptr;
    IXpsPrintJobStream *jobStream = nullptr;
#ifdef PRINT_TICKET_SUPPORT
    IXpsPrintJobStream *printTicketStream = nullptr;
#endif
    hr = StartXpsPrintJob(
             m_deviceName.c_str(),
             pMapModel->HasFileName() ? pMapModel->GetFileName().c_str() : nullptr,
             nullptr,
             nullptr,
             completionEvent,
             nullptr,
             0,
             &job,
             &jobStream,
#ifdef PRINT_TICKET_SUPPORT
             & printTicketStream
#else
             nullptr
#endif
         );
    if (FAILED(hr)) {
        LOG(SEVERITY_LEVEL_ERROR) << L"StartXpsPrintJob failed, hr = " << std::hex << hr;
    }

    if (SUCCEEDED(hr)) {
        hr = m_pXpsPackage->WriteToStream(jobStream, FALSE);
        if (FAILED(hr)) {
            LOG(SEVERITY_LEVEL_ERROR) << L"IXpsOMPackage::WriteToStream failed, hr = " << std::hex << hr;
        }
    }

#ifdef PRINT_TICKET_SUPPORT
    if (SUCCEEDED(hr)) {
        PrintTicketHelper::CreatePrintTicket(m_deviceName, m_pPDX, printTicketStream);
    }
#endif

    hr = jobStream->Close();
#ifdef PRINT_TICKET_SUPPORT
    hr = printTicketStream->Close();
#endif

    if (WaitForSingleObject(completionEvent, INFINITE) == WAIT_OBJECT_0) {
        XPS_JOB_STATUS jobStatus;
        hr = job->GetJobStatus(&jobStatus);

        switch (jobStatus.completion) {
        case XPS_JOB_COMPLETED:
            hr = S_OK;
            break;
        case XPS_JOB_CANCELLED:
            hr = E_FAIL;
            break;
        case XPS_JOB_FAILED:
            hr = E_FAIL;
            break;
        default:
            hr = E_UNEXPECTED;
            break;
        }

        CloseHandle(completionEvent);
    } else {
        hr  = HRESULT_FROM_WIN32(GetLastError());
    }

    m_pTextRenderer->DiscardResources();
    m_pTextRenderer->DeleteTemporaryFiles();
    m_pTextRenderer = nullptr;
}