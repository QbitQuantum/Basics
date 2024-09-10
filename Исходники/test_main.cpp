 void _STLP_CALL unexpected() {
   unexpected_handler hdl;
   set_unexpected(hdl = set_unexpected((unexpected_handler)0));
   hdl();
 }