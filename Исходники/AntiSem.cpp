void AntiSem::sub_count(ulen dcount)
 {
  if( UIntSub(count,dcount) ) Abort("Fatal error: CCore::AntiSem counter underflow");
 }