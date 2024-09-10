 void handle_get_trxs( const connection_ptr& c, chan_data& cdat, get_trxs_message msg )
 { try {
     trxs_message reply;
     FC_ASSERT( msg.items.size() < TRX_INV_QUERY_LIMIT );
     reply.trxs.reserve( msg.items.size() );
     
     for( auto itr = msg.items.begin(); itr != msg.items.end(); ++itr )
     {
         auto pending_itr = _pending_trx.find( *itr );
         if( pending_itr == _pending_trx.end() )
         {
            // TODO DB queries are far more expensive, and therefore must be rationed and potentialy
            // require a proof of work paying us to fetch them
            auto tx_num = _db->fetch_trx_num( *itr );
            reply.trxs.push_back( _db->fetch_trx(tx_num) );
         }
         else
         {
            reply.trxs.push_back( pending_itr->second );
         }
     }
     c->send( network::message( reply, _chan_id ) );
 } FC_RETHROW_EXCEPTIONS( warn, "", ("msg",msg) ) } // provide stack trace for errors