bool ForwardPlugin::processEvent(Event *e)
{
    if (e->type() == eEventMessageReceived){
        EventMessage *em = static_cast<EventMessage*>(e);
        Message *msg = em->msg();
        if (msg->type() == MessageStatus)
            return false;
        QString text = msg->getPlainText();
        if (text.isEmpty())
            return false;
        if (msg->type() == MessageSMS){
            SMSMessage *sms = static_cast<SMSMessage*>(msg);
            QString phone = sms->getPhone();
            bool bMyPhone;
            SIM::PropertyHubPtr data = getContacts()->getUserData("forward");
            bMyPhone = ContactList::cmpPhone(phone, data->value("Phone").toString());
            if (!bMyPhone){
                Group *grp;
                ContactList::GroupIterator it;
                while ((grp = ++it) != NULL){
                    data = grp->getUserData("forward", false);
                    if (data && !data->value("Phone").toString().isEmpty()){
                        bMyPhone = ContactList::cmpPhone(phone, data->value("Phone").toString());
                        break;
                    }
                }
            }
            if (!bMyPhone){
                Contact *contact;
                ContactList::ContactIterator it;
                while ((contact = ++it) != NULL){
                    data = contact->getUserData("forward", false);
                    if (data && !data->value("Phone").toString().isEmpty())
                    {
                        bMyPhone = ContactList::cmpPhone(phone, data->value("Phone").toString());
                        break;
                    }
                }
            }
            if (bMyPhone){
                int n = text.indexOf(": ");
                if (n > 0){
                    QString name = text.left(n);
                    QString msg_text = text.mid(n + 2);
                    Contact *contact;
                    ContactList::ContactIterator it;
                    while ((contact = ++it) != NULL){
                        if (contact->getName() == name){
                            Message *msg = new Message(MessageGeneric);
                            msg->setContact(contact->id());
                            msg->setText(msg_text);
                            void *data;
                            ClientDataIterator it(contact->clientData);
                            while ((data = ++it) != NULL){
                                if (it.client()->send(msg, data))
                                    break;
                            }
                            if (data == NULL)
                                delete msg;
                            return true;
                        }
                    }
                }
            }
        }
        Contact *contact = getContacts()->contact(msg->contact());
        if (contact == NULL)
            return false;
        SIM::PropertyHubPtr data = contact->getUserData("forward");
        if (!data || data->value("Key").toString().isEmpty())
            return false;
        CorePlugin *core = GET_CorePlugin();
        unsigned status = core->getManualStatus();
        if ((status == STATUS_AWAY) || (status == STATUS_NA)){
            text = contact->getName() + ": " + text;
            unsigned flags = MESSAGE_NOHISTORY;
            if (data->value("Send1st").toBool())
                flags |= MESSAGE_1ST_PART;
            if (data->value("Translit").toBool())
                flags |= MESSAGE_TRANSLIT;
            SMSMessage *m = new SMSMessage;
            m->setPhone(data->value("Phone").toString());
            m->setText(text);
            m->setFlags(flags);
            unsigned i;
            for (i = 0; i < getContacts()->nClients(); i++){
                Client *client = getContacts()->getClient(i);
                if (client->send(m, NULL))
                    break;
            }
            if (i >= getContacts()->nClients())
                delete m;
        }
    }
    return false;
}