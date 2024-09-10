void 
IceInternal::LocatorInfo::getEndpointsException(const ReferencePtr& ref, const Ice::Exception& exc)
{
    assert(ref->isIndirect());

    try
    {
        exc.ice_throw();
    }
    catch(const AdapterNotFoundException&)
    {
        if(ref->getInstance()->traceLevels()->location >= 1)
        {
            Trace out(ref->getInstance()->initializationData().logger,
                      ref->getInstance()->traceLevels()->locationCat);
            out << "adapter not found" << "\n";
            out << "adapter = " << ref->getAdapterId();
        }

        NotRegisteredException ex(__FILE__, __LINE__);
        ex.kindOfObject = "object adapter";
        ex.id = ref->getAdapterId();
        throw ex;
    }
    catch(const ObjectNotFoundException&)
    {
        if(ref->getInstance()->traceLevels()->location >= 1)
        {
            Trace out(ref->getInstance()->initializationData().logger,
                      ref->getInstance()->traceLevels()->locationCat);
            out << "object not found" << "\n";
            out << "object = " << ref->getInstance()->identityToString(ref->getIdentity());
        }

        NotRegisteredException ex(__FILE__, __LINE__);
        ex.kindOfObject = "object";
        ex.id = ref->getInstance()->identityToString(ref->getIdentity());
        throw ex;
    }
    catch(const NotRegisteredException&)
    {
        throw;
    }
    catch(const LocalException& ex)
    {
        if(ref->getInstance()->traceLevels()->location >= 1)
        {
            Trace out(ref->getInstance()->initializationData().logger, ref->getInstance()->traceLevels()->locationCat);
            out << "couldn't contact the locator to retrieve adapter endpoints\n";
            if(ref->getAdapterId().empty())
            {
                out << "object = " << ref->getInstance()->identityToString(ref->getIdentity()) << "\n";
            }
            else
            {
                out << "adapter = " << ref->getAdapterId() << "\n";
            }
            out << "reason = " << ex;
        }
        throw;
    }
}