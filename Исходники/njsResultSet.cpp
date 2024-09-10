/*
   DESCRIPTION
     Callback function of close

   PARAMETERS:
     req - UV queue work block
*/
void ResultSet::Async_AfterClose(uv_work_t *req)
{
  Nan::HandleScope scope;
  rsBaton *closeBaton = (rsBaton*)req->data;

  Nan::TryCatch tc;

  Local<Value> argv[1];

  if(!(closeBaton->error).empty())
  {
    argv[0] = v8::Exception::Error(
                   Nan::New<v8::String>(closeBaton->error).ToLocalChecked());
    if(!closeBaton->errOnActiveOrInvalid)
    {
      closeBaton->njsRS->state_ = NJS_INACTIVE;
    }
  }
  else
  {
    argv[0] = Nan::Undefined();
    // resultset is not valid after close succeeds.
    closeBaton-> njsRS-> state_ = NJS_INVALID;
  }

  /*
   * When we close the resultSet, we have to clear the reference of
   * its parent.
   */
  closeBaton->njsRS->jsParent_.Reset ();

  Local<Function> callback = Nan::New(closeBaton->ebaton->cb);
  delete closeBaton;

  Nan::MakeCallback( Nan::GetCurrentContext()->Global(), callback, 1, argv );
  if(tc.HasCaught())
  {
    Nan::FatalException(tc);
  }
}