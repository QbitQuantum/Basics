 void ActiveThread::initializeActiveObject(ActiveObject *ao)
 {
     auto msg = safeNew<LambdaMessage>();
     msg->lambda = [ao]
     {
         ao->initialize();
     };
     sendTo(ao->at(), msg);
 }