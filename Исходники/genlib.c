bool genlib(compile_t* c, ast_t* program)
{
  if(!reachable_actors(c, program) ||
    !generate_actors(c, program) ||
    !genheader(c)
    )
    return false;

  const char* file_o = genobj(c);

  if(file_o == NULL)
    return false;

  if(c->opt->limit < PASS_ALL)
    return true;

  if(!link_lib(c, file_o))
    return false;

#ifdef PLATFORM_IS_WINDOWS
  _unlink(file_o);
#else
  unlink(file_o);
#endif

  return true;
}