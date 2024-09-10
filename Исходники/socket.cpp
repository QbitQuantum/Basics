static v8::Handle<v8::Value> JS_runAsClient( const v8::Arguments& args )
{
	v8::HandleScope handleScope;

	int argc = args.Length();

	CSocket *sock = jsGetCObject<CSocket>(args.Holder());

	if( !sock )
	{
		return handleScope.Close( v8::Boolean::New(false) );
	}

	return handleScope.Close( v8::Boolean::New( sock->runAsClient() ) );
}