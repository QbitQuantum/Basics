void* worker_routine(void *vdbc) {

    struct dbcontext * dbc = (struct dbcontext *) vdbc;
    
    //allocate array for objects that will be automatically removed after 
    th_alloc_array(1000);
    
    //  Socket to talk to dispatcher
    void *receiver = zmq_socket (dbc->context, ZMQ_REP);
    zmq_connect (receiver, "inproc://workers");

    //Initialize our Isoloate
    Isolate *isolate = Isolate::New();
    if(!isolate)
    {
        cout << "Failed to initialize Isolate, we can't work";
        return 0;
    }
    
    Locker lock(isolate);
    Isolate::Scope isolateScope(isolate);
    HandleScope scope;
    
    Local<ObjectTemplate> globals = ObjectTemplate::New();
    
#define SETGLOB(name) globals->Set(String::New(""#name), FunctionTemplate::New(name));

    globals->Set(String::New("addnum"), FunctionTemplate::New(addnum));
    SETGLOB(print)
    
    globals->Set(String::New("put"), FunctionTemplate::New(put));
    globals->Set(String::New("get"), FunctionTemplate::New(get));
    globals->Set(String::New("del"), FunctionTemplate::New(del));
    
    //iterator
    globals->Set(String::New("it_del"), FunctionTemplate::New(it_del));
    globals->Set(String::New("it_new"), FunctionTemplate::New(it_new));
    globals->Set(String::New("it_first"), FunctionTemplate::New(it_first));
    globals->Set(String::New("it_last"), FunctionTemplate::New(it_last));
    globals->Set(String::New("it_seek"), FunctionTemplate::New(it_seek));
    globals->Set(String::New("it_next"), FunctionTemplate::New(it_next));
    globals->Set(String::New("it_prev"), FunctionTemplate::New(it_prev));
    globals->Set(String::New("it_valid"), FunctionTemplate::New(it_valid));
    globals->Set(String::New("it_key"), FunctionTemplate::New(it_key));
    globals->Set(String::New("it_val"), FunctionTemplate::New(it_val));

    //BITSET
    SETGLOB(bs_new)
    SETGLOB(bs_reset)
    SETGLOB(bs_set)
    SETGLOB(bs_logicalor)
    SETGLOB(bs_logicalnot)
    SETGLOB(bs_inplace_logicalnot)
    SETGLOB(bs_logicaland)
    SETGLOB(bs_sparselogicaland)
    SETGLOB(bs_tostring)
    SETGLOB(bs_makeSameSize)
    SETGLOB(bs_eq)
    SETGLOB(putbs)
    SETGLOB(getbs)
    SETGLOB(bs_it_new)
    SETGLOB(bs_it_end)
    SETGLOB(bs_it_isend)
    SETGLOB(bs_it_next)
    SETGLOB(bs_it_val)
    SETGLOB(bs_it_end)
    SETGLOB(bs_it_eq)
    
    
    Handle<Context> context = Context::New(NULL, globals);
    context->Enter();
    
    //Running init script with library functions
 
    if (dbc->init_code != NULL) {
        TryCatch try_catch;
        
        Local<String> source = String::New(dbc->init_code);
        Local<Script> script = Script::Compile(source);
        
        if(script.IsEmpty())
        {
            ReportException(&try_catch);
        } else {        
            // Run the function once and catch the error to generate machine code
            Local<Value> result = script->Run();
        }
        
    }
        
    while (1) {
        
        zmq_msg_t req;
        int rc = zmq_msg_init (&req);
        assert (rc == 0);
        rc = zmq_recv (receiver, &req, 0);
        assert (rc == 0);
        
        zmq_msg_t reply;
        //rc = zmq_msg_init_size (&reply, 200);
        //assert (rc == 0);

//test mq speed only
#if 0
        
        rc = zmq_msg_init_size (&reply, 200);
        assert (rc == 0);
        rc = zmq_msg_copy (&reply, &req);
        assert (rc == 0);
        rc = zmq_send (receiver, &reply, 0); 
        assert (rc == 0);
        
        //s_sleep(1);
        
        zmq_msg_close (&req);
        zmq_msg_close (&reply);
        continue;
#endif

        //std::cout << "thread: " << pthread_self() << " Received script: " << (char*) zmq_msg_data(&req) << std::endl;

        //leveldb::Status s;
 
 #if 1
        Context::Scope contextScope(context);
        
        // Compile a function which will keep using the stack until v8 cuts it off
        
        //Local<Script> script = Local<Script>::New(Script::Compile(String::New( (char*) zmq_msg_data(&req) )));
        
        TryCatch try_catch;
        
        Local<String> source = String::New((char*) zmq_msg_data(&req));
        Local<Script> script = Script::Compile(source);
        
        if(script.IsEmpty())
        {
            ReportException(&try_catch);
            
            String::Utf8Value error(try_catch.Exception());
            v8::Handle<v8::Message> message = try_catch.Message();
            int line_num = 0;
            int col_num = 0;
            
            if (message.IsEmpty()) {
                
            }else {
                line_num = message->GetLineNumber();
                col_num = message->GetStartColumn();
            }
            
            int mess_size = error.length()+100;
            rc = zmq_msg_init_size (&reply, mess_size);
            assert (rc == 0);

            //cerr << "compile error line: " << " message: " << *error << endl;
            snprintf ((char*) zmq_msg_data (&reply), mess_size, "2; {res: 'COMPILE ERROR', line: %d, col: %d, message: '%s'}", line_num, col_num, *error);
        }
        else {        

            // Run the function once and catch the error to generate machine code
            Local<Value> result = script->Run();
                    
            if (try_catch.HasCaught()) {
                //TODO: escape string
                String::Utf8Value message(try_catch.Exception());
                int mess_size = message.length()+100;
                rc = zmq_msg_init_size (&reply, mess_size);
                assert (rc == 0);

                std::cout <<"exception->" <<*message <<"\n";
                snprintf ((char*) zmq_msg_data (&reply), mess_size, "1; {res: 'ERROR', message: '%s'}", *message);
            }
            else {
                //TODO: escape string
                String::Utf8Value message(result->ToString());
                int mess_size = message.length()+2;
                rc = zmq_msg_init_size (&reply, mess_size);
                assert (rc == 0);

                snprintf ((char*) zmq_msg_data (&reply), mess_size, " %s", *message);
            }
        }        

#endif
                
        
        /* Send the message to the socket */
        rc = zmq_send (receiver, &reply, 0); 
        assert (rc == 0);
        
        //s_sleep(1);
        
        zmq_msg_close (&req);
        zmq_msg_close (&reply);
        
        free_objects();
    }
    
    context->Exit();    
    //printf("Iter: %d , Result: %ld ; from thread: %ld \n", i, res, tid);
        
    //context.Dispose();
    
    //script.Dispose();
    
    Unlocker unlock(isolate);
    
    //isolate->Exit();
    //isolate->Dispose();

    zmq_close (receiver);
    return NULL;
}