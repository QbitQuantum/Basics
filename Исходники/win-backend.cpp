 wmf_backend::~wmf_backend()
 {
     try {
         MFShutdown();
         CoUninitialize();
     }
     catch(...)
     {
         // TODO: Write to log
     }
 }