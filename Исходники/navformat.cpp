Handle<Value> DecoderNotifier::Done(const Arguments& args) {
  HandleScope scope;

  DecoderNotifier* obj = ObjectWrap::Unwrap<DecoderNotifier>(args.This());
  
 if(args.Length() == 0){
    // Process next frame
    uv_queue_work(uv_default_loop(),
                  &(obj->pBaton->request),
                  AsyncWork,
                  (uv_after_work_cb)AsyncAfter);
  }
  
  return Undefined();
}