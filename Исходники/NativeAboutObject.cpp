QStatus NativeAboutObject::GetAboutData(
    /* [in] */ ajn::MsgArg* msgArg,
    /* [in] */ const char* language)
{
    QStatus status = ER_FAIL;
    if (mAboutDataListenerRef != NULL) {
        AutoPtr<IMap> announceArg;
        ECode ec = mAboutDataListenerRef->GetAboutData(String(language), (IMap**)&announceArg);
        // check for ErrorReplyBusException exception
        status = CheckForThrownException(ec);
        if (ER_OK == status) {
            // Marshal the returned value
            if (Marshal("a{sv}", announceArg.Get(), msgArg) == NULL) {
                Logger::E("NativeAboutObject", "GetMsgArgAnnounce() marshaling error");
                return ER_FAIL;
            }
        }
        else {
            Logger::E("NativeAboutObject", "GetMsgArg exception with status %s", QCC_StatusText(status));
            return status;
        }
    }
    return ER_OK;
}