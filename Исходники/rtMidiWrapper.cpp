static VALUE rtMidiIn_connect(VALUE self, VALUE port)
{
	RtMidiIn *device;
	Data_Get_Struct(self, RtMidiIn, device);
	
	try {
		device->openPort(NUM2INT(port));
		device->ignoreTypes( false, false, false );
	}
	catch(RtError &error)
	{
		rb_warn("could not open port");
		return Qfalse;
	}
	
	return Qtrue;
}