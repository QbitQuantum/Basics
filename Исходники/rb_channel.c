/* Clones Channel instances.

   Gives Channel a consistent implementation of Ruby's object copy/dup
   protocol. */
static VALUE grpc_rb_channel_init_copy(VALUE copy, VALUE orig) {
  grpc_rb_channel *orig_ch = NULL;
  grpc_rb_channel *copy_ch = NULL;

  if (copy == orig) {
    return copy;
  }

  /* Raise an error if orig is not a channel object or a subclass. */
  if (TYPE(orig) != T_DATA ||
      RDATA(orig)->dfree != (RUBY_DATA_FUNC)grpc_rb_channel_free) {
    rb_raise(rb_eTypeError, "not a %s", rb_obj_classname(grpc_rb_cChannel));
    return Qnil;
  }

  TypedData_Get_Struct(orig, grpc_rb_channel, &grpc_channel_data_type, orig_ch);
  TypedData_Get_Struct(copy, grpc_rb_channel, &grpc_channel_data_type, copy_ch);

  /* use ruby's MEMCPY to make a byte-for-byte copy of the channel wrapper
   * object. */
  MEMCPY(copy_ch, orig_ch, grpc_rb_channel, 1);
  return copy;
}