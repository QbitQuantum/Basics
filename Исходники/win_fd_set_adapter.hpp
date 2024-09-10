 bool is_set(socket_type descriptor) const
 {
   return !!__WSAFDIsSet(descriptor,
       const_cast<fd_set*>(reinterpret_cast<const fd_set*>(&fd_set_)));
 }