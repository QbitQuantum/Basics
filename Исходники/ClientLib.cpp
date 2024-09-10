//------------------------------------------------------------------------------
__MC_CLIENT_LIB_API mcResult_t mcWaitNotification(
    mcSessionHandle_t  *session,
    int32_t            timeout
)
{
    mcResult_t mcResult = MC_DRV_OK;
#ifndef WIN32

    // TODO-2012-11-02-gurel: devMutex locking and unlocking had to be commented out
    // below. Otherwise, when there are multiple threads in Nwd TLC side, we endup a
    // deadlock situation, e.g. one thread waits for notification and another one sends
    // notification.

    //devMutex.lock();
    LOG_I("===%s()===", __FUNCTION__);

    do {
        CHECK_NOT_NULL(session);
        LOG_I(" Waiting for notification of session %03x.", session->sessionId);

        Device *device = resolveDeviceId(session->deviceId);
        CHECK_DEVICE(device);

        Session  *nqSession = device->resolveSessionId(session->sessionId);
        CHECK_SESSION(nqSession, session->sessionId);

        Connection *nqconnection = nqSession->notificationConnection;
        uint32_t count = 0;

        // Read notification queue till it's empty
        for (;;) {
            notification_t notification;
            ssize_t numRead = nqconnection->readData(
                                  &notification,
                                  sizeof(notification_t),
                                  timeout);
            // Check for interrupted system call and loop, but only if timeout is infinite
            if ((numRead == -1) && (errno == EINTR)) {
                if (timeout == MC_INFINITE_TIMEOUT) {
                    continue;
                } else if (timeout == MC_INFINITE_TIMEOUT_INTERRUPTIBLE) {
                    mcResult = MC_DRV_ERR_INTERRUPTED_BY_SIGNAL;
                    break;
                }
            }
            //Exit on timeout in first run
            //Later runs have timeout set to 0. -2 means, there is no more data.
            if (count == 0 && numRead == -2 ) {
                LOG_W("Timeout hit at %s", __FUNCTION__);
                mcResult = MC_DRV_ERR_TIMEOUT;
                break;
            }
            if (count == 0 && numRead == 0 ) {
                LOG_E("Connection is dead, removing device.");
                removeDevice(session->deviceId);
                mcResult = MC_DRV_ERR_NOTIFICATION;
                break;
            }
            // After first notification the queue will be drained, Thus we set
            // no timeout for the following reads
            timeout = 0;

            if (numRead != sizeof(notification_t)) {
                if (count == 0) {
                    //failure in first read, notify it
                    mcResult = MC_DRV_ERR_NOTIFICATION;
                    LOG_E("read notification failed, %i bytes received", (int)numRead);
                    break;
                } else {
                    // Read of the n-th notification failed/timeout. We don't tell the
                    // caller, as we got valid notifications before.
                    mcResult = MC_DRV_OK;
                    break;
                }
            }

            count++;
            LOG_I(" Received notification %d for session %03x, payload=%d",
                  count, notification.sessionId, notification.payload);

            if (notification.payload != 0) {
                // Session end point died -> store exit code
                nqSession->setErrorInfo(notification.payload);

                mcResult = MC_DRV_INFO_NOTIFICATION;
                break;
            }
        } // for(;;)

    } while (false);

    //devMutex.unlock();

#endif /* WIN32 */
    return mcResult;
}