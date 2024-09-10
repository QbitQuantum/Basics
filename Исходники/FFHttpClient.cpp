//FFHttpClientDelegate
void FFHttpClient::didSendRequest()
{
    CCHttpClient *httpClient = CCHttpClient::getInstance();
    httpClient->setTimeoutForConnect(30);
    httpClient->send(mHttpRequest);
}