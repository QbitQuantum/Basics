/* Clones Server instances.

   Gives Server a consistent implementation of Ruby's object copy/dup
   protocol. */
static VALUE grpc_rb_server_init_copy(VALUE copy, VALUE orig) {
    grpc_rb_server *orig_srv = NULL;
    grpc_rb_server *copy_srv = NULL;

    if (copy == orig) {
        return copy;
    }

    /* Raise an error if orig is not a server object or a subclass. */
    if (TYPE(orig) != T_DATA ||
            RDATA(orig)->dfree != (RUBY_DATA_FUNC)grpc_rb_server_free) {
        rb_raise(rb_eTypeError, "not a %s", rb_obj_classname(grpc_rb_cServer));
    }

    TypedData_Get_Struct(orig, grpc_rb_server, &grpc_rb_server_data_type,
                         orig_srv);
    TypedData_Get_Struct(copy, grpc_rb_server, &grpc_rb_server_data_type,
                         copy_srv);

    /* use ruby's MEMCPY to make a byte-for-byte copy of the server wrapper
       object. */
    MEMCPY(copy_srv, orig_srv, grpc_rb_server, 1);
    return copy;
}