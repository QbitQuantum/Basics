void ServerSocketInterface::readClient()
{
    QByteArray data = socket->readAll();
    servatrice->incRxBytes(data.size());
    inputBuffer.append(data);

    do {
        if (!messageInProgress) {
            if (inputBuffer.size() >= 4) {
                messageLength =   (((quint32) (unsigned char) inputBuffer[0]) << 24)
                                + (((quint32) (unsigned char) inputBuffer[1]) << 16)
                                + (((quint32) (unsigned char) inputBuffer[2]) << 8)
                                + ((quint32) (unsigned char) inputBuffer[3]);
                inputBuffer.remove(0, 4);
                messageInProgress = true;
            } else
                return;
        }
        if (inputBuffer.size() < messageLength)
            return;

        CommandContainer newCommandContainer;
        try {
            newCommandContainer.ParseFromArray(inputBuffer.data(), messageLength);
        }
        catch(std::exception &e) {
            qDebug() << "Caught std::exception in" << __FILE__ << __LINE__ << 
#ifdef _MSC_VER // Visual Studio
                __FUNCTION__;
#else
                __PRETTY_FUNCTION__;
#endif
            qDebug() << "Exception:" << e.what();
            qDebug() << "Message coming from:" << getAddress();
            qDebug() << "Message length:" << messageLength;
            qDebug() << "Message content:" << inputBuffer.toHex();
        }
        catch(...) {
            qDebug() << "Unhandled exception in" << __FILE__ << __LINE__ <<
#ifdef _MSC_VER // Visual Studio
                __FUNCTION__;
#else
                __PRETTY_FUNCTION__;
#endif
            qDebug() << "Message coming from:" << getAddress();
        }

        inputBuffer.remove(0, messageLength);
        messageInProgress = false;

        // dirty hack to make v13 client display the correct error message
        if (handshakeStarted)
            processCommandContainer(newCommandContainer);
        else if (!newCommandContainer.has_cmd_id()) {
            handshakeStarted = true;
            if (!initSession())
                prepareDestroy();
        }
        // end of hack
    } while (!inputBuffer.isEmpty());
}