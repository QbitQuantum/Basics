    static Handle<Value> createContext(const Arguments& args)
    {
	HandleScope scope;
	if (!args[0]->IsArray())
	    ThrowException(Exception::Error(String::New("CL_INVALID_VALUE")));
	if (!args[1]->IsArray())
	    ThrowException(Exception::Error(String::New("CL_INVALID_VALUE")));

	Local<Array> propertiesArray = Array::Cast(*args[0]);
	cl_context_properties *properties = new cl_context_properties[propertiesArray->Length()+1];

	for (int i=0; i<propertiesArray->Length(); i+=2) {
	    properties[i] = (cl_context_properties)propertiesArray->Get(i)->NumberValue();
	    Local<Object> obj = propertiesArray->Get(i+1)->ToObject();
	    Platform *p = ObjectWrap::Unwrap<Platform>(obj);
	    properties[i+1] = (cl_context_properties)p->getPlatformWrapper()->getWrapped();
	}
	properties[propertiesArray->Length()] = 0;

	Local<Array> deviceArray = Array::Cast(*args[1]);
	std::vector<DeviceWrapper*> devices;
	for (int i=0; i<deviceArray->Length(); i++) {
	    Local<Object> obj = deviceArray->Get(i)->ToObject();
	    Device *d = ObjectWrap::Unwrap<Device>(obj);
	    devices.push_back(d->getDeviceWrapper());
	}

	ContextWrapper *cw = 0;
	cl_int ret = ContextWrapper::createContext (properties, devices, 0, 0, &cw);

	delete[] properties;

	if (ret != CL_SUCCESS) {
	    WEBCL_COND_RETURN_THROW(CL_INVALID_PLATFORM);
	    WEBCL_COND_RETURN_THROW(CL_INVALID_PROPERTY);
	    WEBCL_COND_RETURN_THROW(CL_INVALID_VALUE);
	    WEBCL_COND_RETURN_THROW(CL_INVALID_DEVICE);
	    WEBCL_COND_RETURN_THROW(CL_DEVICE_NOT_AVAILABLE);
	    WEBCL_COND_RETURN_THROW(CL_OUT_OF_RESOURCES);
	    WEBCL_COND_RETURN_THROW(CL_OUT_OF_HOST_MEMORY);
	    return ThrowException(Exception::Error(String::New("UNKNOWN ERROR")));
	}

	return scope.Close(CLContext::New(cw)->handle_);
    }