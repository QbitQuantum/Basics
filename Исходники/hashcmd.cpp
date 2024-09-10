Handle_ptr hashremoveCommand( CBuiltinAdapter *adapter, Context &ctx,
		   Environment *env, std::vector<Handle_ptr> args)
{
  if (2 != args.size()) {
     throw ArgumentCountException( 2, __FILE__, __LINE__);
  }

  Hashtable *hashtable = asHashtable( args[0]);
  std::string key = args[1]->stringValue();
  hashtable->remove( key);

  return args[0];
}