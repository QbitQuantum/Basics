/*
   DESCRIPTION
     Callback function of Get Connection method

   PARAMETERS:
     UV queue work block
     status - expected to be non-zero.

   NOTES:
     Connection handle is formed and handed over to JS.
*/
void Pool::Async_AfterGetConnection(uv_work_t *req)
{
  Nan::HandleScope scope;
  poolBaton *connBaton = (poolBaton*)req->data;

  Nan::TryCatch tc;
  Local<Value> argv[2];

  if(!(connBaton->error).empty())
  {
    argv[0] = v8::Exception::Error(Nan::New<v8::String>((connBaton->error).c_str()).ToLocalChecked());
    argv[1] = Nan::Undefined();
  } 
  else
  {
    argv[0] = Nan::Undefined();
    Local<FunctionTemplate> lft = Nan::New(Connection::connectionTemplate_s);
    Local<Object> connection = lft->GetFunction()-> NewInstance();
    (Nan::ObjectWrap::Unwrap<Connection> (connection))->
                                 setConnection( connBaton->dpiconn,
                                                connBaton->njspool->oracledb_ );
    argv[1] = connection;
  }

  Local<Function> callback = Nan::New<Function>(connBaton->cb);
  delete connBaton;
  Nan::MakeCallback( Nan::GetCurrentContext()->Global(),
                      callback, 2, argv );

  if(tc.HasCaught())
  {
    Nan::FatalException(tc);
  }
}