bool CoreEngine::init(const QString &dllEnginePath, QString *errorMessage)
{
    enum {  bufLen = 10240 };
    // Load the DLL
    DebuggerEngineLibrary lib;
    if (!lib.init(dllEnginePath, &m_dbengDLL, errorMessage))
        return false;
    // Initialize the COM interfaces
    HRESULT hr;
    hr = lib.debugCreate( __uuidof(IDebugClient5), reinterpret_cast<void**>(&m_cif.debugClient));
    if (FAILED(hr)) {
        *errorMessage = QString::fromLatin1("Creation of IDebugClient5 failed: %1").arg(msgDebugEngineComResult(hr));
        return false;
    }

    hr = lib.debugCreate( __uuidof(IDebugControl4), reinterpret_cast<void**>(&m_cif.debugControl));
    if (FAILED(hr)) {
        *errorMessage = QString::fromLatin1("Creation of IDebugControl4 failed: %1").arg(msgDebugEngineComResult(hr));
        return false;
    }

    hr = lib.debugCreate( __uuidof(IDebugSystemObjects4), reinterpret_cast<void**>(&m_cif.debugSystemObjects));
    if (FAILED(hr)) {
        *errorMessage = QString::fromLatin1("Creation of IDebugSystemObjects4 failed: %1").arg(msgDebugEngineComResult(hr));
        return false;
    }

    hr = lib.debugCreate( __uuidof(IDebugSymbols3), reinterpret_cast<void**>(&m_cif.debugSymbols));
    if (FAILED(hr)) {
        *errorMessage = QString::fromLatin1("Creation of IDebugSymbols3 failed: %1").arg(msgDebugEngineComResult(hr));
        return false;
    }
    hr = m_cif.debugSymbols->SetSymbolOptions(defaultSymbolOptions);
    if (FAILED(hr)) {
        *errorMessage = msgComFailed("SetSymbolOptions", hr);
        return false;
    }

    WCHAR buf[bufLen];
    hr = m_cif.debugSymbols->GetImagePathWide(buf, bufLen, 0);
    if (FAILED(hr)) {
        *errorMessage = msgComFailed("GetImagePathWide", hr);
        return false;
    }
    m_baseImagePath = QString::fromWCharArray(buf);

    hr = lib.debugCreate( __uuidof(IDebugRegisters2), reinterpret_cast<void**>(&m_cif.debugRegisters));
    if (FAILED(hr)) {
        *errorMessage = QString::fromLatin1("Creation of IDebugRegisters2 failed: %1").arg(msgDebugEngineComResult(hr));
        return false;
    }

    hr = lib.debugCreate( __uuidof(IDebugDataSpaces4), reinterpret_cast<void**>(&m_cif.debugDataSpaces));
    if (FAILED(hr)) {
        *errorMessage = QString::fromLatin1("Creation of IDebugDataSpaces4 failed: %1").arg(msgDebugEngineComResult(hr));
        return false;
    }

    if (debug)
        qDebug() << QString::fromLatin1("CDB Initialization succeeded, interrupt time out %1s.").arg(getInterruptTimeOutSecs(m_cif.debugControl));
    return true;
}