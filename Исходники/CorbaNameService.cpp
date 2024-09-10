RTT::TaskContext* CorbaNameService::getTaskContext(const std::string& taskName)
{
    if(CORBA::is_nil(orb))
    {
        throw std::runtime_error("CorbaNameService::Error, called getTaskContext() without connection " );
    }

    CosNaming::Name serverName;
    serverName.length(2);
    serverName[0].id = CORBA::string_dup("TaskContexts");
    serverName[1].id = CORBA::string_dup( taskName.c_str() );

    // Get object reference
    CORBA::Object_var task_object = rootContext->resolve(serverName);
    CORBA::String_var s = orb->object_to_string(task_object);

    RTT::TaskContext *ret = nullptr;
        
    try
    {
        ret = RTT::corba::TaskContextProxy::Create(s.in(), true);;
    }
    catch (...)
    {
        std::cout << "Ghost " << taskName << std::endl;
    }
    
    return ret;
}