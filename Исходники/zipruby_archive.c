static VALUE zipruby_archive_read(VALUE self) {
  VALUE retval = Qnil;
  struct zipruby_archive *p_archive;
  FILE *fzip;
  char buf[DATA_BUFSIZE];
  ssize_t n;
  int block_given;

  Data_Get_Struct(self, struct zipruby_archive, p_archive);

  if (NIL_P(p_archive->path)) {
    rb_raise(rb_eRuntimeError, "invalid Zip::Archive");
  }

#ifdef _WIN32
  if (fopen_s(&fzip, RSTRING_PTR(p_archive->path), "rb") != 0) {
    rb_raise(Error, "Read archive failed: Cannot open archive");
  }
#else
  if ((fzip = fopen(RSTRING_PTR(p_archive->path), "rb")) == NULL) {
    rb_raise(Error, "Read archive failed: Cannot open archive");
  }
#endif

  block_given = rb_block_given_p();

  while ((n = fread(buf, 1, sizeof(buf), fzip)) > 0) {
    if (block_given) {
      rb_yield(rb_str_new(buf, n));
    } else {
      if (NIL_P(retval)) {
        retval = rb_str_new(buf, n);
      } else {
        rb_str_buf_cat(retval, buf, n);
      }
    }
  }

#if defined(RUBY_VM) && defined(_WIN32)
  _fclose_nolock(fzip);
#elif defined(RUBY_WIN32_H)
#undef fclose
  fclose(fzip);
#define fclose(f) rb_w32_fclose(f)
#else
  fclose(fzip);
#endif

  if (n == -1) {
    rb_raise(Error, "Read archive failed");
  }

  return retval;
}