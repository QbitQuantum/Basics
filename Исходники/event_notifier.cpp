bool EventNotifier::SendCommandEvent(int eventId, void* clientData)
{
    if(_eventsDiabled)
        return false;

    wxCommandEvent evt(eventId);
    evt.SetClientData(clientData);
    return ProcessEvent(evt);
}