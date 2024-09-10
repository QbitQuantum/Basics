CompilerWrapperOption::CompilerWrapperOption(CompilerWrapperOptionPool &pool,const char *field_name) : _pool(pool)
{
  _description=NULL;
  _field_name=STRDUP(field_name);
  _pool.add(this);
}