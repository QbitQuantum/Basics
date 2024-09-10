bool ExceptionEncounteredSenderTest::testExceptionEncounteredSucceeds(
    const std::string& unparsedDirective,
    avs::ExceptionErrorType error,
    const std::string& errorDescription) {
    bool done = false;
    m_exceptionEncounteredEvent =
        std::make_shared<ExceptionEncounteredEvent>(unparsedDirective, error, errorDescription);

    EXPECT_CALL(*m_mockMessageSender, sendMessage(_))
        .WillOnce(Invoke(m_exceptionEncounteredEvent.get(), &ExceptionEncounteredEvent::verifyMessage));
    m_exceptionEncounteredEvent->send(m_exceptionEncounteredSender);
    done = true;
    return done;
}