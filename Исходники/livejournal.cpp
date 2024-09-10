void LiveJournalClient::messageUpdated()
{
    Contact *contact;
    LiveJournalUserData *data = findContact(this->data.owner.User.ptr, contact);
    if (data == NULL)
        return;
    Message *msg = new Message(MessageUpdated);
    msg->setContact(contact->id());
    msg->setClient(dataName(data).c_str());
    msg->setFlags(MESSAGE_TEMP | MESSAGE_NOVIEW);
    Event e(EventMessageReceived, msg);
    if (!e.process())
        delete msg;
}