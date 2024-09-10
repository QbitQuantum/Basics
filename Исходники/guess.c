static VALUE guess4r_f__guess_open(int argc, VALUE *argv) {
  VALUE *args, opt, f, str, enc;
  int i;

  args = ALLOCA_N(VALUE, argc + 1);
  args[0] = argv[0];
  if (TYPE(argv[argc - 1]) != T_HASH) {
    args[1] = args[argc++] = rb_hash_new();
  } else {
    args[1] = argv[argc - 1];
  }

  rb_hash_aset(args[1], ID2SYM(rb_intern("encoding")), rb_const_get(rb_cEncoding, rb_intern("ASCII_8BIT")));
  rb_funcall(args[1], rb_intern("delete"), 1, ID2SYM(rb_intern("external_encoding")));
  rb_funcall(args[1], rb_intern("delete"), 1, ID2SYM(rb_intern("internal_encoding")));
  f = rb_funcall2(rb_mKernel, rb_intern("open"), 2, args);
  str = rb_funcall(f, rb_intern("read"), 0);
  enc = guess4r_str__guess_encoding(str);
  rb_funcall(f, rb_intern("close"), 0);
  rb_hash_aset(args[1], ID2SYM(rb_intern("encoding")), enc);

  MEMCPY(args, argv, VALUE, argc - 1);
  return rb_funcall_passing_block(rb_mKernel, rb_intern("open"), argc, args);
}