CosNaming::Name* 
VOmniORBHelper::nsPathToObjectName(const char* program, const char* object,
				   int telescopenumber)
  throw(CORBA::SystemException)
{
  std::ostringstream program_stream;
  if(telescopenumber!=-1)
    program_stream << program << telescopenumber;
  else 
    program_stream << program;
  
  CosNaming::Name* name = new CosNaming::Name;
  name->length(3);
  
  (*name)[0].id   = CORBA::string_dup(m_project.c_str());
  (*name)[0].kind = CORBA::string_dup("");

  (*name)[1].id   = CORBA::string_dup(program_stream.str().c_str());
  (*name)[1].kind = CORBA::string_dup("Program");

  (*name)[2].id   = CORBA::string_dup(object);
  (*name)[2].kind = CORBA::string_dup("Object");

  return name;
}