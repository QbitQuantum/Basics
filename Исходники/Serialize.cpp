int SerializePart(google::protobuf::Message *message, Handle<Object> subj) {
	NanScope();

	// get a reflection
	const Reflection *r = message->GetReflection();
	const Descriptor *d = message->GetDescriptor();
	
	// build a list of required properties
	vector<string> required;
	for (int i = 0; i < d->field_count(); i++) {
		const FieldDescriptor *field = d->field(i);
		if (field->is_required())
			required.push_back(field->name());
	}

	// build a reflection
	// get properties of passed object
	Local<Array> properties = subj->GetPropertyNames();
	uint32_t len = properties->Length();
	
	// check that all required properties are present
	for (uint32_t i = 0; i < required.size(); i++) {
		Handle<String> key = String::New(required.at(i).c_str());
		if (!subj->Has(key))
			return -1;
	}

	for (uint32_t i = 0; i < len; i++) {
		Local<Value> property = properties->Get(i);
		Local<String> property_s = property->ToString();

		if (*property_s == NULL)
			continue;

		String::Utf8Value temp(property);
		std::string propertyName = std::string(*temp);

		const FieldDescriptor *field = d->FindFieldByName(propertyName);
		if (field == NULL) continue;

		Local<Value> val = subj->Get(property);

		if (field->is_repeated()) {
			if (!val->IsArray())
				continue;

			Handle<Array> array = val.As<Array>();
			int len = array->Length();

			for (int i = 0; i < len; i++)
				SerializeField(message, r, field, array->Get(i));

		} else {
			SerializeField(message, r, field, val);
		}
	}
	
	return 0;
}