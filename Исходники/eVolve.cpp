v1::scheduler::Event evolve(const StatusUpdateMessage& message)
{
  v1::scheduler::Event event;
  event.set_type(v1::scheduler::Event::UPDATE);

  v1::scheduler::Event::Update* update = event.mutable_update();

  update->mutable_status()->CopyFrom(evolve(message.update().status()));

  if (message.update().has_slave_id()) {
    update->mutable_status()->mutable_agent_id()->CopyFrom(
        evolve(message.update().slave_id()));
  }

  if (message.update().has_executor_id()) {
    update->mutable_status()->mutable_executor_id()->CopyFrom(
        evolve(message.update().executor_id()));
  }

  update->mutable_status()->set_timestamp(message.update().timestamp());

  // If the update does not have a 'uuid', it does not need
  // acknowledging. However, prior to 0.23.0, the update uuid
  // was required and always set. In 0.24.0, we can rely on the
  // update uuid check here, until then we must still check for
  // this being sent from the driver (from == UPID()) or from
  // the master (pid == UPID()).
  // TODO(vinod): Get rid of this logic in 0.25.0 because master
  // and slave correctly set task status in 0.24.0.
  if (!message.update().has_uuid() || message.update().uuid() == "") {
    update->mutable_status()->clear_uuid();
  } else if (UPID(message.pid()) == UPID()) {
    update->mutable_status()->clear_uuid();
  } else {
    update->mutable_status()->set_uuid(message.update().uuid());
  }

  return event;
}