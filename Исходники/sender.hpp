 void send_messages(
     connection_ptr connection
 )
 {
     // Check if sending has been completed....
     if (connection->send())
     {
         error_code ec;
         util::unique_function_nonser<
             void(
                 error_code const&
               , parcelset::locality const&
               , connection_ptr
             )
         > postprocess_handler;
         std::swap(postprocess_handler, connection->postprocess_handler_);
         postprocess_handler(
             ec, connection->destination(), connection);
     }
     else
     {
         std::unique_lock<mutex_type> l(connections_mtx_);
         connections_.push_back(std::move(connection));
     }
 }