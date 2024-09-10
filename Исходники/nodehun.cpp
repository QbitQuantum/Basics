Handle<Value> Nodehun::SpellDictionary::New(const Arguments& args) {
  HandleScope scope;
  int argl = args.Length();
  if (!args.IsConstructCall())
    return ThrowException(Exception::Error(String::New("Use the new operator to create an instance of this object.")));
  if(argl < 2)
    return ThrowException(Exception::Error(String::New("Constructor requires two arguments.")));
  if(!Buffer::HasInstance(args[0]))
    return ThrowException(Exception::TypeError(String::New("First argument must be a buffer")));
  if(!Buffer::HasInstance(args[1]))
    return ThrowException(Exception::TypeError(String::New("Second argument must be a buffer")));

  Nodehun::SpellDictionary *obj = new Nodehun::SpellDictionary(Buffer::Data(args[0].As<Object>()), Buffer::Data(args[1].As<Object>()));
  obj->Wrap(args.This());  
  return args.This();
}