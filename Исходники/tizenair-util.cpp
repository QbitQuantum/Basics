v8::Handle<v8::Value> Util::getFilenameFrom( const v8::Arguments& args ) {
	if ( args.Length() < 1 ) {
		return v8::Undefined();
	}

	v8::String::Utf8Value path( args[0] );
	std::string p = *path;

	size_t index = p.rfind( "/" );
	if ( index == std::string::npos ) {
		return args[0];
	}
	return v8::String::NewSymbol( p.substr( index + 1, p.size() - index - 1 ).c_str() );

}