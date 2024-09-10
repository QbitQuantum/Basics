const string& UniqueID()
{
   static AtomicCounter cnt; // a GLOBAL counter
   

   NTL_TLS_LOCAL(string, ID);

   NTL_TLS_LOCAL_INIT(bool, initialized, (false));
   NTL_TLS_LOCAL_INIT(unsigned long, local_cnt, (cnt.inc()));
   NTL_TLS_LOCAL_INIT(unsigned long, local_time, (time(0)));
   NTL_TLS_LOCAL_INIT(unsigned long, local_clock, (clock()));

   if (!initialized) {
      stringstream ss;
      ss << local_cnt << "-" << local_time << "-" 
         << local_clock << "-" << GetPID()  << "-" << CurrentThreadID();  
      ID = ss.str();
      initialized = true;
   }

   return ID;
}