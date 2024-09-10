void
NfcConsumer::OnConnectError()
{
    CHROMIUM_LOG("NFC: %s\n", __FUNCTION__);
    CloseSocket();
}