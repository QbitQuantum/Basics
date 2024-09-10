void
MessagePort::PostMessage(JSContext* aCx, JS::Handle<JS::Value> aMessage,
                         const Sequence<JSObject*>& aTransferable,
                         ErrorResult& aRv)
{
  // We *must* clone the data here, or the JS::Value could be modified
  // by script

  // Here we want to check if the transerable object list contains
  // this port.
  for (uint32_t i = 0; i < aTransferable.Length(); ++i) {
    JS::Rooted<JSObject*> object(aCx, aTransferable[i]);
    if (!object) {
      continue;
    }

    MessagePort* port = nullptr;
    nsresult rv = UNWRAP_OBJECT(MessagePort, &object, port);
    if (NS_SUCCEEDED(rv) && port == this) {
      aRv.Throw(NS_ERROR_DOM_DATA_CLONE_ERR);
      return;
    }
  }

  JS::Rooted<JS::Value> transferable(aCx, JS::UndefinedValue());

  aRv = nsContentUtils::CreateJSValueFromSequenceOfObject(aCx, aTransferable,
                                                          &transferable);
  if (NS_WARN_IF(aRv.Failed())) {
    return;
  }

  RefPtr<SharedMessagePortMessage> data = new SharedMessagePortMessage();

  UniquePtr<AbstractTimelineMarker> start;
  UniquePtr<AbstractTimelineMarker> end;
  RefPtr<TimelineConsumers> timelines = TimelineConsumers::Get();
  bool isTimelineRecording = timelines && !timelines->IsEmpty();

  if (isTimelineRecording) {
    start = MakeUnique<MessagePortTimelineMarker>(
      ProfileTimelineMessagePortOperationType::SerializeData,
      MarkerTracingType::START);
  }

  data->Write(aCx, aMessage, transferable, aRv);

  if (isTimelineRecording) {
    end = MakeUnique<MessagePortTimelineMarker>(
      ProfileTimelineMessagePortOperationType::SerializeData,
      MarkerTracingType::END);
    timelines->AddMarkerForAllObservedDocShells(start);
    timelines->AddMarkerForAllObservedDocShells(end);
  }

  if (NS_WARN_IF(aRv.Failed())) {
    return;
  }

  // This message has to be ignored.
  if (mState > eStateEntangled) {
    return;
  }

  // If we are unshipped we are connected to the other port on the same thread.
  if (mState == eStateUnshippedEntangled) {
    MOZ_ASSERT(mUnshippedEntangledPort);
    mUnshippedEntangledPort->mMessages.AppendElement(data);
    mUnshippedEntangledPort->Dispatch();
    return;
  }

  // Not entangled yet, but already closed/disentangled.
  if (mState == eStateEntanglingForDisentangle ||
      mState == eStateEntanglingForClose) {
    return;
  }

  RemoveDocFromBFCache();

  // Not entangled yet.
  if (mState == eStateEntangling) {
    mMessagesForTheOtherPort.AppendElement(data);
    return;
  }

  MOZ_ASSERT(mActor);
  MOZ_ASSERT(mMessagesForTheOtherPort.IsEmpty());

  AutoTArray<RefPtr<SharedMessagePortMessage>, 1> array;
  array.AppendElement(data);

  AutoTArray<ClonedMessageData, 1> messages;
  // note: `messages` will borrow the underlying buffer, but this is okay
  // because reverse destruction order means `messages` will be destroyed prior
  // to `array`/`data`.
  SharedMessagePortMessage::FromSharedToMessagesChild(mActor, array, messages);
  mActor->SendPostMessages(messages);
}