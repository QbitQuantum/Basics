CString CHttpClient::GetLastErrorString()
{
    CString strError("Unknown");

    switch (GetLastError())
    {
    case HTTP_ERROR_SOCKET_PREPARE_FAILED:
        strError.Set("Failed to prepare socket");
        break;
    case HTTP_ERROR_INVALID_HOST:
        strError.Set("Invalid host");
        break;
    case HTTP_ERROR_IOCTL_FAILED:
        strError.Set("IoCtl failed");
        break;
    case HTTP_ERROR_CONNECTION_FAILED:
        strError.Set("Connection failed");
        break;
    case HTTP_ERROR_SEND_FAILED:
        strError.Set("Send failed");
        break;
    case HTTP_ERROR_REQUEST_TIMEOUT:
        strError.Set("Request timed out");
        break;
    case HTTP_ERROR_NO_HEADER:
        strError.Set("No header");
        break;
    }

    return strError;
}