void ContactsPersonProxy::_setEmail(void* userContext, Handle<Value> value)
{
    ContactsPersonProxy *obj = (ContactsPersonProxy*) userContext;

    if(!value->IsObject()) return;

	Handle<Object> emailObject = value->ToObject();
	Local<Array> emailProperties = emailObject->GetPropertyNames();
	for(int i = 0, len = emailProperties->Length(); i < len; i++)
	{
		Local<String> allEmailsKey = emailProperties->Get(i)->ToString();
		Local<Value> allEmailsValue = emailObject->Get(allEmailsKey);

		AttributeSubKind::Type subKind = AttributeSubKind::Other;

		QString allEmailsKeyString = titanium::V8ValueToQString(allEmailsKey).toLower();
		if(allEmailsKeyString == "work")
		{
			subKind = AttributeSubKind::Work;
		}
		else
		if(allEmailsKeyString == "personal")
		{
			subKind = AttributeSubKind::Personal;
		}
		else
		if(allEmailsKeyString == "home")
		{
			subKind = AttributeSubKind::Home;
		}

		if(!allEmailsValue->IsArray()) return;

		Local<Array> emails = Local<Array>::Cast(allEmailsValue);
		for(int i = 0, len = emails->Length(); i < len; i++)
		{
			Local<Value> emailValue = emails->Get(Number::New(i));
			if(emailValue->IsString() || emailValue->IsNumber())
			{
				 obj->setContactDetails(AttributeKind::Email, subKind, emailValue);
			}
			else
			{
				// Something goes here, throw an error?
			}
		}
	}
}