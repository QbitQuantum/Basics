  static v8::Handle<v8::Value> v8addEventListener(  const v8::Arguments& arguments ){
    if( arguments.Length() > 2 ){
      v8::Local<v8::External> external = v8::Local<v8::External>::Cast( arguments.This()->GetInternalField(0) );
      EventTarget* object = static_cast<EventTarget*>( external->Value() );
      
      v8::Local<v8::String> typeStr = v8::Local<v8::String>::Cast(arguments[0]);
      v8::String::AsciiValue type(typeStr);
      
      v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(arguments[1]);
      v8::Persistent<v8::Function> handler = v8::Persistent<v8::Function>::New(cb);

      object->addEventListener( *type, handler, false );
    }
    return v8::Undefined();
  }