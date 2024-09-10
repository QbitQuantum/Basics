Sluift::Response SluiftClient::doSendRequest(std::shared_ptr<Request> request, int timeout) {
    requestResponse.reset();
    requestError.reset();
    requestResponseReceived = false;
    request->send();

    Watchdog watchdog(timeout, networkFactories->getTimerFactory());
    while (!watchdog.getTimedOut() && !requestResponseReceived) {
        eventLoop->runUntilEvents();
    }
    return Sluift::Response(requestResponse, watchdog.getTimedOut() ?
            std::make_shared<ErrorPayload>(ErrorPayload::RemoteServerTimeout) : requestError);
}