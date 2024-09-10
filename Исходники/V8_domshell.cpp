// The callback that is invoked by v8 whenever the JavaScript 'read'
// function is called.  This function loads the content of the file named in
// the argument into a JavaScript string.
v8::Handle<v8::Value> Read(const v8::Arguments& args)
{
    if (args.Length() != 1) {
        return v8::ThrowException(v8::String::New("Bad parameters"));
    }
    v8::String::Utf8Value file(args[0]);
    if (*file == NULL) {
        return v8::ThrowException(v8::String::New("Error loading file"));
    }
    v8::Handle<v8::String> source = ReadFile(*file);
    if (source.IsEmpty()) {
        return v8::ThrowException(v8::String::New("Error loading file"));
    }
    return source;
}