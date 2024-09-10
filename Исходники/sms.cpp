void SMSClient::phonebookEntry(int index, int type, const QString &phone, const QString &name)
{
    bool bNew = false;
    Contact *contact;
    ContactList::ContactIterator it;
    while ((contact = ++it) != NULL){
        smsUserData *data;
        ClientDataIterator itd(contact->clientData);
        while ((data = (smsUserData*)(++itd)) != NULL){
            if (name == QString::fromUtf8(data->Name.ptr))
                break;
        }
        if (data)
            break;
    }
    if (contact == NULL){
        contact = getContacts()->contactByPhone(phone.latin1());
        if (contact->getFlags() & CONTACT_TEMPORARY){
            bNew = true;
            contact->setFlags(contact->getFlags() & ~CONTACT_TEMPORARY);
            contact->setName(name);
        }
    }
    QString phones = contact->getPhones();
    bool bFound = false;
    while (!phones.isEmpty()){
        QString item = getToken(phones, ';', false);
        QString number = getToken(item, ',');
        if (number == phone){
            bFound = true;
            break;
        }
    }
    if (!bFound){
        phones = contact->getPhones();
        if (!phones.isEmpty())
            phones += ";";
        contact->setPhones(phones + phone + ",,2/-");
    }
    smsUserData *data = (smsUserData*)contact->clientData.createData(this);
    set_str(&data->Phone.ptr, phone.utf8());
    set_str(&data->Name.ptr, name.utf8());
    data->Index.value = index;
    data->Type.value  = type;
    if (bNew){
        Event e(EventContactChanged, contact);
        e.process();
    }
}