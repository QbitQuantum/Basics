/*---------------------------------------------------------------------*/
obj_t
bgl_write_utf8string( obj_t o, obj_t op ) {
   PUTS( op, "#u\"" );
   bgl_display_string( o, op );
   PUTC( op, '"' );

   return op;
}