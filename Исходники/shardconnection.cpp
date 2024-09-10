 void sync(){
     scoped_lock lk( _mutex );
     for ( map<string,Status*>::iterator i=_hosts.begin(); i!=_hosts.end(); ++i ){
         string addr = i->first;
         Status* ss = i->second;
         assert( ss );
         std::stack<DBClientBase*>& s = ss->avail;
         while ( ! s.empty() ){
             DBClientBase* conn = s.top();
             conn->getLastError();
             pool.release( addr , conn );
             s.pop();
         }
         delete ss;
     }
     _hosts.clear();
 }