OnlineViewer_var getOnlineViewer(CosNaming::NamingContext_var cxt)
{  
    CosNaming::Name ncName;
    ncName.length(1);
    ncName[0].id = CORBA::string_dup("OnlineViewer");
    ncName[0].kind = CORBA::string_dup("");
    OnlineViewer_var onlineViewer = NULL;
    try {
        onlineViewer = OnlineViewer::_narrow(cxt->resolve(ncName));
    } catch(const CosNaming::NamingContext::NotFound &exc) {
        std::cerr << "OnlineViewer not found: ";
        switch(exc.why) {
        case CosNaming::NamingContext::missing_node:
            std::cerr << "Missing Node" << std::endl;
        case CosNaming::NamingContext::not_context:
            std::cerr << "Not Context" << std::endl;
            break;
        case CosNaming::NamingContext::not_object:
            std::cerr << "Not Object" << std::endl;
            break;
        }
        return 0;
    } catch(CosNaming::NamingContext::CannotProceed &exc) {
        std::cerr << "Resolve OnlineViewer CannotProceed" << std::endl;
        return 0;
    } catch(CosNaming::NamingContext::AlreadyBound &exc) {
        std::cerr << "Resolve OnlineViewer InvalidName" << std::endl;
        return 0;
    }
    return onlineViewer;
}