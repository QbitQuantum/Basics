bool genexe(compile_t* c, ast_t* program)
{
  // The first package is the main package. It has to have a Main actor.
  const char* main_actor = stringtab("Main");
  const char* env_class = stringtab("Env");

  ast_t* package = ast_child(program);
  ast_t* main_def = ast_get(package, main_actor, NULL);

  if(main_def == NULL)
  {
    errorf(NULL, "no Main actor found in package '%s'", c->filename);
    return false;
  }

  // Generate the Main actor and the Env class.
  ast_t* main_ast = type_builtin(c->opt, main_def, main_actor);
  ast_t* env_ast = type_builtin(c->opt, main_def, env_class);

  genprim_reachable_init(c, program);
  reach(c->reachable, main_ast, stringtab("create"), NULL);
  reach(c->reachable, env_ast, stringtab("_create"), NULL);
  paint(c->reachable);

  gentype_t main_g;
  gentype_t env_g;

  bool ok = gentype(c, main_ast, &main_g) && gentype(c, env_ast, &env_g);

  if(ok)
    gen_main(c, &main_g, &env_g);

  ast_free_unattached(main_ast);
  ast_free_unattached(env_ast);

  if(!ok)
    return false;

  if(!genopt(c))
    return false;

  const char* file_o = genobj(c);

  if(file_o == NULL)
    return false;

  if(c->opt->limit < PASS_ALL)
    return true;

  if(!link_exe(c, program, file_o))
    return false;

#ifdef PLATFORM_IS_WINDOWS
  _unlink(file_o);
#else
  unlink(file_o);
#endif

  return true;
}