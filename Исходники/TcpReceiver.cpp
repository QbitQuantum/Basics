TcpReceiver::TcpReceiver(int port)
    : GuiFrame(0, 0)
    , CThread(CThread::eAttributeAffCore0 | CThread::eAttributePinnedAff)
    , exitRequested(false)
    , serverPort(port)
    , serverSocket(-1)
    , progressWindow("Receiving file...")
{
    width = progressWindow.getWidth();
    height = progressWindow.getHeight();
    append(&progressWindow);
    resumeThread();
}