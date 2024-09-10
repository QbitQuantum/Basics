void EventsChangesNotifier::GetScenesAndExternalEventsLinkedTo(
    const gd::EventsList& events,
    gd::Project& project,
    std::vector<gd::Layout*>& layouts,
    std::vector<gd::ExternalEvents*>& externalEvents) {
  for (std::size_t i = 0; i < events.size(); ++i) {
    try {
      const gd::LinkEvent& linkEvent =
          dynamic_cast<const gd::LinkEvent&>(events[i]);

      // We've got a link event, search now linked scene/external events
      if (project.HasExternalEventsNamed(linkEvent.GetTarget())) {
        gd::ExternalEvents& linkedExternalEvents =
            project.GetExternalEvents(linkEvent.GetTarget());

        // Protect against circular references
        if (find(externalEvents.begin(),
                 externalEvents.end(),
                 &linkedExternalEvents) == externalEvents.end()) {
          externalEvents.push_back(&linkedExternalEvents);
          GetScenesAndExternalEventsLinkedTo(linkedExternalEvents.GetEvents(),
                                             project,
                                             layouts,
                                             externalEvents);
        }
      } else if (project.HasLayoutNamed(linkEvent.GetTarget())) {
        gd::Layout& linkedLayout = project.GetLayout(linkEvent.GetTarget());

        // Protect against circular references
        if (find(layouts.begin(), layouts.end(), &linkedLayout) ==
            layouts.end()) {
          layouts.push_back(&linkedLayout);
          GetScenesAndExternalEventsLinkedTo(
              linkedLayout.GetEvents(), project, layouts, externalEvents);
        }
      }
    } catch (...) {
    }

    if (events[i].CanHaveSubEvents())
      GetScenesAndExternalEventsLinkedTo(
          events[i].GetSubEvents(), project, layouts, externalEvents);
  }
}