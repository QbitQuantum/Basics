ulen Sem::begin_give_many(ulen dcount)
 {
  FastMutex::Lock lock(mutex);
   
  if( take_count<dcount )
    {
     dcount-=take_count;
      
     if( UIntAdd(count,dcount) ) Abort("Fatal error : CCore::Sem counter add overflow");
     
     return Replace_null(take_count);
    }
  else
    {
     take_count-=dcount;
     
     return dcount;
    }  
 }