 /* ===================================================== */   
 void handle_get_block( const connection_ptr& con,  chan_data& cdat, const get_block_message& msg )
 { try {
     // TODO: charge POW for this...
     auto block = _name_db.fetch_block( msg.block_id );
     con->send( network::message( block_message( std::move(block) ), _chan_id ) );
 } FC_RETHROW_EXCEPTIONS( warn, "", ("msg",msg) ) }