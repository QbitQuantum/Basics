 CMessageHandler(const char *_name,PARENT *_parent,void (PARENT::*_handler)(CMessageBuffer &_mb), IExceptionHandler *exceptionHandler=NULL, unsigned maxthreads=40, unsigned timeoutOnRelease=INFINITE, unsigned lowThreadsDelay=1000)
 {
     parent = _parent;
     handler = _handler;
     name = strdup(_name);
     pool = createThreadPool(name,this,exceptionHandler,maxthreads,lowThreadsDelay,0,timeoutOnRelease); // this will cause this to be linked
     hasexceptionhandler = exceptionHandler!=NULL;
 }