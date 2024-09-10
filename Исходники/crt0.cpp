void __cdecl
mainCRTStartup(
  void
  )
{
  //
  // Call C initializers.
  //
  _initterm_e(__xi_a, __xi_z);

  //
  // Call C++ initializers.
  //
  _initterm(__xc_a, __xc_z);

  //
  // Exit with whatever main will return.
  //
  create_argc_and_argv();
  int exit_code = main(__argc, __argv);
  destroy_argc_and_argv();

  exit(exit_code);
}