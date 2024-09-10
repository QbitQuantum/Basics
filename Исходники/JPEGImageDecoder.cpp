// Override the standard error method in the IJG JPEG decoder code.
void error_exit(j_common_ptr cinfo)
{
    // Return control to the setjmp point.
    decoder_error_mgr *err = (decoder_error_mgr *) cinfo->err;
    longjmp(err->setjmp_buffer, -1);
}