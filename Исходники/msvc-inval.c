void
gl_msvc_inval_ensure_handler (void)
{
  if (gl_msvc_inval_initialized == 0)
    {
      _set_invalid_parameter_handler (gl_msvc_invalid_parameter_handler);
      gl_msvc_inval_initialized = 1;
    }
}