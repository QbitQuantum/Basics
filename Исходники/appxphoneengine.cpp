bool AppxPhoneEngine::remove()
{
    Q_D(AppxPhoneEngine);
    qCDebug(lcWinRtRunner) << __FUNCTION__;

    if (!connect())
        return false;

    if (!d->connection)
        return false;

    ComPtr<ICcConnection3> connection;
    HRESULT hr = d->connection.As(&connection);
    RETURN_FALSE_IF_FAILED("Failed to obtain connection object");

    _bstr_t app = wchar(d->productId);
    hr = connection->UninstallApplication(app);
    RETURN_FALSE_IF_FAILED("Failed to uninstall the package");

    return true;
}