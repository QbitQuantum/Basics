void RSocketServer::onRSocketResume(
    std::shared_ptr<RSocketServiceHandler> serviceHandler,
    std::unique_ptr<DuplexConnection> connection,
    ResumeParameters resumeParams) {
  auto result = serviceHandler->onResume(resumeParams.token);
  if (result.hasError()) {
    stats_->resumeFailedNoState();
    VLOG(3) << "Terminating RESUME attempt from client.  No ServerState found";
    connection->send(
        FrameSerializer::createFrameSerializer(resumeParams.protocolVersion)
            ->serializeOut(Frame_ERROR::rejectedSetup(result.error().what())));
    return;
  }
  const auto serverState = std::move(result.value());
  CHECK(serverState);
  const auto eventBase = folly::EventBaseManager::get()->getExistingEventBase();
  VLOG(2) << "Resuming client on " << eventBase->getName();
  if (!serverState->eventBase_.isInEventBaseThread()) {
    // If the resumed connection is on a different EventBase, then use
    // ScheduledFrameTransport and ScheduledFrameProcessor to ensure the
    // RSocketStateMachine continues to live on the same EventBase and the
    // IO happens in the new EventBase
    auto scheduledFT = std::make_shared<ScheduledFrameTransport>(
        std::make_shared<FrameTransportImpl>(std::move(connection)),
        eventBase, /* Transport EventBase */
        &serverState->eventBase_); /* StateMachine EventBase */
    serverState->eventBase_.runInEventBaseThread(
        [serverState,
         scheduledFT = std::move(scheduledFT),
         resumeParams = std::move(resumeParams)]() mutable {
          serverState->rSocketStateMachine_->resumeServer(
              std::move(scheduledFT), resumeParams);
        });
  } else {
    // If the resumed connection is on the same EventBase, then the
    // RSocketStateMachine and Transport can continue living in the same
    // EventBase without any thread hopping between them.
    serverState->rSocketStateMachine_->resumeServer(
        std::make_shared<FrameTransportImpl>(std::move(connection)),
        resumeParams);
  }
}