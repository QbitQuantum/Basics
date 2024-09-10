/* Clones ServerCredentials instances.

   Gives ServerCredentials a consistent implementation of Ruby's object copy/dup
   protocol. */
static VALUE grpc_rb_server_credentials_init_copy(VALUE copy, VALUE orig) {
  grpc_rb_server_credentials *orig_ch = NULL;
  grpc_rb_server_credentials *copy_ch = NULL;

  if (copy == orig) {
    return copy;
  }

  /* Raise an error if orig is not a server_credentials object or a subclass. */
  if (TYPE(orig) != T_DATA ||
      RDATA(orig)->dfree != (RUBY_DATA_FUNC)grpc_rb_server_credentials_free) {
    rb_raise(rb_eTypeError, "not a %s",
             rb_obj_classname(rb_cServerCredentials));
  }

  Data_Get_Struct(orig, grpc_rb_server_credentials, orig_ch);
  Data_Get_Struct(copy, grpc_rb_server_credentials, copy_ch);

  /* use ruby's MEMCPY to make a byte-for-byte copy of the server_credentials
     wrapper object. */
  MEMCPY(copy_ch, orig_ch, grpc_rb_server_credentials, 1);
  return copy;
}