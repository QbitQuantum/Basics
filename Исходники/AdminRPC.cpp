/*!
 * @brief       Add a user
 * @param[in]   username
 * @param[in]   password
 * @param[in]   access_level
 * @return      Returns a string, if successful "OK" otherwise an error
 */
QString AdminRPC::addUser(const QString &username, const QString &password, int access_level)
{
    QString result;
    uint64_t fake_session_token = s_last_token++;
    int token = static_cast<int>(fake_session_token);

    // Create and insert a record of this request into m_completion_state
    m_completion_state.insert(token, "");

    qCDebug(logRPC) << "addUser call in progress";

    EventProcessor *tgt = HandlerLocator::getAuthDB_Handler();
    tgt->putq(new CreateAccountMessage({username, password, access_level}, fake_session_token, this));

    QTimer response_timer;
    QTimer timeout;
    timeout.setSingleShot(true);
    QEventLoop loop;
    loop.connect(&timeout, SIGNAL(timeout()), SLOT(quit()));
    loop.connect(this, SIGNAL(responseRecieved()), SLOT(quit()));
    loop.connect(&response_timer, &QTimer::timeout, [=] () {
        if (!m_completion_state[token].isEmpty())
        {
            emit responseRecieved(); // Response recieved we can break out of event loop
            return;
        }
        else
            return;
    });
    response_timer.start(500); // Checks completion status every 500ms
    timeout.start(5000); // Timeout of 5 seconds in case something goes wrong.
    loop.exec();

    if (!m_completion_state[token].isEmpty())
    {
        result = m_completion_state[token];
        response_timer.stop();
        m_completion_state.remove(token); // Tidy up
    }
    else
    {
        result = "Something went wrong";
        response_timer.stop();
        m_completion_state.remove(token);
    }

    return result;
}