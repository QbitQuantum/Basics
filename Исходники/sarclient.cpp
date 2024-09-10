void SarClient::stop()
{
    if (_mmNotificationClientRegistered) {
        _mmEnumerator->UnregisterEndpointNotificationCallback(
            _mmNotificationClient);
        _mmNotificationClientRegistered = false;
    }

    if (_mmNotificationClient) {
        _mmNotificationClient->Release();
        _mmNotificationClient = nullptr;
    }

    if (_mmEnumerator) {
        _mmEnumerator = nullptr;
    }

    if (_device != INVALID_HANDLE_VALUE) {
        CancelIoEx(_device, nullptr);
        CloseHandle(_device);
        _device = INVALID_HANDLE_VALUE;
    }

    if (_completionPort) {
        CloseHandle(_completionPort);
        _completionPort = nullptr;
    }
}