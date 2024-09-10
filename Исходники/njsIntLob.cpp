void ILob::Async_AfterRead(uv_work_t *req)
{
  Nan::HandleScope scope;

  LobBaton     *lobBaton = (LobBaton *)req->data;
  ILob         *iLob = lobBaton->iLob;
  Nan::TryCatch  tc;
  Local<Value> argv[2];

  if ( !lobBaton->errOnActiveOrInvalid )
  {
    iLob->state_ = NJS_INACTIVE; // mark Lob as inactive as back in main thread
  }

  if(!(lobBaton->error).empty())
  {
    argv[0] = v8::Exception::Error(
                    Nan::New<v8::String>(lobBaton->error).ToLocalChecked());
    argv[1] = Nan::Undefined();
  }
  else
  {
    argv[0] = Nan::Undefined();

    if (iLob->amountRead_)
    {
      if (iLob->dpiLobType_ == DpiClob)
      {
        Local<Value> str = Nan::New<v8::String>((char *)iLob->buf_,
                                         iLob->amountRead_).ToLocalChecked();
        argv[1] = str;
      }
      else
      {
        // Blobs use buffers rather than strings
        // TODO: We could use NewBuffer to save memory and CPU, but it gets the ownership of buffer to itself (behaviour changed in Nan 2.0)
        Local<Value> buffer = Nan::CopyBuffer((char *)iLob->buf_,
                                             iLob->amountRead_).ToLocalChecked();
        argv[1] = buffer;
      }


    }
    else
      argv[1] = Nan::Null();
  }

  Local<Function> callback = Nan::New<Function>(lobBaton->cb);
  delete lobBaton;

  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, 2, argv);

  if(tc.HasCaught())
  {
    Nan::FatalException(tc);
  }
}