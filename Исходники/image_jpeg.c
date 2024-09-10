static void my_error_exit(j_common_ptr cinfo) {
  my_error_ptr myerr = (my_error_ptr) cinfo->err;
  (*cinfo->err->format_message)(cinfo, emsg);
  longjmp(myerr->setjmp_buffer, 1);
}