Int32 Envvar::set()
{
  // Envvars are added by creating a string "envvar_name=envvar_value"
  // and then adding it ("putting" it) to environment.

  delete [] env_str;
  
  env_str = new char[strlen(name) + 1/*for = */ + strlen(value)
		     +1/*for null*/];
  
  strcpy(env_str, name);
  strcat(env_str, "=");
  strcat(env_str, value);
  
  Int32 i = PUTENV(env_str);
  
  if (i) cerr << "*** ERROR " << i << " from putenv." << endl;
   
  invalidateEnvVarDependentCaches(name);
  return i;
}