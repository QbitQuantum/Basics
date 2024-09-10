void ConnectionClient::finishProcess()
{
    TIME_SCOPE_DURATION("ConnectionClient::finishProcess");

    processAliveTimer.stop();

    disconnectProcessFinished();
    endProcess();
    disconnectFromServer();
    terminateProcess();
    killProcess();

    process_.reset();

    serverProxy_.resetCounter();
}