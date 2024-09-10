void NamingContextHelper::unbind(const std::string& name)
{
    if(isAlive()){
        CosNaming::Name nc;
        nc.length(1);
        nc[0].id   = CORBA::string_dup(name.c_str());
        nc[0].kind = CORBA::string_dup("");
        namingContext->unbind(nc);
    }
}