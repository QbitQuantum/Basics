void
OutgoingAsync::prepare(const string& operation, OperationMode mode, const Context& context)
{
    checkSupportedProtocol(getCompatibleProtocol(_proxy->__reference()->getProtocol()));

    _mode = mode;
    _observer.attach(_proxy, operation, context);

    switch(_proxy->__reference()->getMode())
    {
        case Reference::ModeTwoway:
        case Reference::ModeOneway:
        case Reference::ModeDatagram:
        {
            _os.writeBlob(requestHdr, sizeof(requestHdr));
            break;
        }

        case Reference::ModeBatchOneway:
        case Reference::ModeBatchDatagram:
        {
            _proxy->__getBatchRequestQueue()->prepareBatchRequest(&_os);
            break;
        }
    }

    Reference* ref = _proxy->__reference().get();

    _os.write(ref->getIdentity());

    //
    // For compatibility with the old FacetPath.
    //
    if(ref->getFacet().empty())
    {
        _os.write(static_cast<string*>(0), static_cast<string*>(0));
    }
    else
    {
        string facet = ref->getFacet();
        _os.write(&facet, &facet + 1);
    }

    _os.write(operation, false);

    _os.write(static_cast<Byte>(_mode));

    if(&context != &Ice::noExplicitContext)
    {
        //
        // Explicit context
        //
        _os.write(context);
    }
    else
    {
        //
        // Implicit context
        //
        const ImplicitContextIPtr& implicitContext = ref->getInstance()->getImplicitContext();
        const Context& prxContext = ref->getContext()->getValue();
        if(implicitContext == 0)
        {
            _os.write(prxContext);
        }
        else
        {
            implicitContext->write(prxContext, &_os);
        }
    }
}