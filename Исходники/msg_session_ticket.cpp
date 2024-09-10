New_Session_Ticket::New_Session_Ticket(Handshake_IO& io,
                                       Handshake_Hash& hash)
   {
   hash.update(io.send(*this));
   }