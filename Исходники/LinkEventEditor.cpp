LinkEventEditor::LinkEventEditor(wxWindow* parent,
                                 LinkEvent& event,
                                 const gd::Project& project)
    : LinkEventEditorBase(parent), editedEvent(event), project(project) {
  // Add all the scenes and external events into the combobox.
  for (std::size_t i = 0; i < project.GetExternalEventsCount(); ++i)
    m_eventsComboBox->Append(project.GetExternalEvents(i).GetName());
  for (std::size_t i = 0; i < project.GetLayoutsCount(); ++i)
    m_eventsComboBox->Append(project.GetLayout(i).GetName());

  m_includeAllEventsRadio->SetValue(editedEvent.GetIncludeConfig() ==
                                    LinkEvent::INCLUDE_ALL);
  m_includeEventsGroupRadio->SetValue(editedEvent.GetIncludeConfig() ==
                                      LinkEvent::INCLUDE_EVENTS_GROUP);
  m_includeEventsByIndexRadio->SetValue(editedEvent.GetIncludeConfig() ==
                                        LinkEvent::INCLUDE_BY_INDEX);

  m_eventsComboBox->SetValue(editedEvent.GetTarget());
  if (editedEvent.GetIncludeConfig() == LinkEvent::INCLUDE_EVENTS_GROUP) {
    m_eventsGroupComboBox->SetValue(editedEvent.GetEventsGroupName());
  } else if (editedEvent.GetIncludeConfig() == LinkEvent::INCLUDE_BY_INDEX) {
    m_startTextCtrl->SetValue(
        gd::String::From<std::size_t>(editedEvent.GetIncludeStart() + 1));
    m_endTextCtrl->SetValue(
        gd::String::From<std::size_t>(editedEvent.GetIncludeEnd() + 1));
  }

  // Display the deprecated features if the event was using them
  m_includeEventsByIndexRadio->Show(editedEvent.GetIncludeConfig() ==
                                    LinkEvent::INCLUDE_BY_INDEX);
  m_deprecatedPanel->Show(editedEvent.GetIncludeConfig() ==
                          LinkEvent::INCLUDE_BY_INDEX);
  GetSizer()->Fit(this);

  EnableControls();
  UpdateEventsGroupsList();
}