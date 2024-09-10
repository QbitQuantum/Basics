void
IAXVoIPLink::iaxOutgoingInvite(IAXCall* call)
{
    ost::MutexLock m(mutexIAX_);

    call->session = iax_session_new();

    IAXAccount *account = dynamic_cast<IAXAccount *>(Manager::instance().getAccount(accountID_));
    std::string username(account->getUsername());
    std::string strNum(username + ":" + account->getPassword() + "@" + account->getHostname() + "/" + call->getPeerNumber());

    /** @todo Make preference dynamic, and configurable */
    int audio_format_preferred = call->getFirstMatchingFormat(call->getSupportedFormat(accountID_), accountID_);
    int audio_format_capability = call->getSupportedFormat(accountID_);

    iax_call(call->session, username.c_str(), username.c_str(), strNum.c_str(),
             NULL, 0, audio_format_preferred, audio_format_capability);
}