 ticks_type GetTickCount64()
 {
   ::boost::call_once(&init_gettickcount64, initfnonce);
   return gettickcount64 ? gettickcount64() : static_cast<ticks_type> (gettickcount32());
 }