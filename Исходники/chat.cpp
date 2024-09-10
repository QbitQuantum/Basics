void Chat::runLeaveChat()
{
    QLOG_TRACE() << __PRETTY_FUNCTION__;
    bool success = true;
    QString message;

    try {
        sdc::ByteSeq plainLog;

        Ice::OutputStreamPtr out = Ice::createOutputStream(sessionPrx->ice_getCommunicator());
        QMutexLocker logLocker(&logMutex);
        out->write(log);
        out->finished(plainLog);
        logLocker.unlock();

        QSharedPointer<const LoginUser> user = session.getUser();
        sdc::SecureContainer cryptLog;

        cryptLog.data = user->encrypt(plainLog);
        cryptLog.signature = user->sign(plainLog);

        sessionPrx->saveLog(chatID.toStdString(),
                            QDateTime::currentDateTimeUtc().toTime_t(), cryptLog);

        sessionPrx->leaveChat(chatID.toStdString());

    } catch (const sdc::LogException &e) {
        success = false;
        message = e.what.c_str();
    } catch (const sdc::SessionException &e) {
        success = false;
        message = e.what.c_str();
    } catch (const sdc::InterServerException &e) {
        success = false;
        message = e.what.c_str();
    } catch (const sdc::SecurityException &e) {
        success = false;
        message = e.what();
    } catch (...) {
        success = false;
        message = "Unexpected exception";
    }

    emit leaveChatCompleted(chatID);
    emit leaveChatCompleted(success, message);
}