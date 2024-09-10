Handle<Value> AppjsSchemeHandler::NodeCallback(const Arguments& args) {
  HandleScope scope;

  AppjsSchemeHandler* me = static_cast<AppjsSchemeHandler *>(UnwrapObject(args.Data()));

  AutoLock lock_scope(me);

  me->status_      = args[0]->NumberValue();
  me->status_text_ = V8StringToChar(args[1]->ToString());
  me->mime_type_   = V8StringToChar(args[2]->ToString());
  me->data_        = node::Buffer::Data(args[4]->ToObject());
  me->data_length_ = node::Buffer::Length(args[4]->ToObject());

  Local<Object> headerSets = args[3]->ToObject();
  Local<Array> names = Local<Array>::Cast(headerSets->Get(String::NewSymbol("names")));
  Local<Array> headers = Local<Array>::Cast(headerSets->Get(String::NewSymbol("headers")));

  for(int i = 0; i < names->Length(); i++) {
    me->headers_.insert(
      std::pair<CefString,CefString>(
        V8StringToChar(names->Get(i)),
        V8StringToChar(headers->Get(i))
      )
    );
  }

  me->callback_->HeadersAvailable();

  return args.This();
}