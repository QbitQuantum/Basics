    Handle< Value > V8Scope::loadCallback( const Arguments &args ) {
        Locker l;
        HandleScope handle_scope;
        Handle<External> field = Handle<External>::Cast(args.Data());
        void* ptr = field->Value();
        V8Scope* self = static_cast<V8Scope*>(ptr);

        Context::Scope context_scope(self->_context);
        for (int i = 0; i < args.Length(); ++i) {
            std::string filename(toSTLString(args[i]));
            if (!self->execFile(filename, false , true , false)) {
                return v8::ThrowException(v8::String::New((std::string("error loading file: ") + filename).c_str()));
            }
        }
        return v8::True();
    }