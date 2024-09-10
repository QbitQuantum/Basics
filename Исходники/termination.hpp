 static detail::reaction_result react(
   State & stt, const EventBase &, const IdType & )
 {
   return detail::result_utility::get_result( stt.terminate() );
 }