bool EventFactory::exists(EventSubscriberID& name_id) {
  return (getInstance().event_subs_.count(name_id) > 0);
}