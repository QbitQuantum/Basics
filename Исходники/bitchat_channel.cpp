 /**
  *  Send all inventory items that are not known to c and are dated 'after'
  */
 void handle_get_inv( const connection_ptr& c, bitchat_chan_data& cd, const get_inv_message& msg )
 {
    inv_message reply;
    for( auto itr = msg_time_index.lower_bound( fc::time_point(msg.after) ); itr != msg_time_index.end(); ++itr )
    {
       if( cd.known_inv.insert( itr->second ).second )
       {
          reply.items.push_back( itr->second );
          cd.known_inv.insert( itr->second );
       }
    }
    c->send( network::message( reply, chan_id ) );
 }