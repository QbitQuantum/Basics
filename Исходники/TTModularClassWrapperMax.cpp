TTErr makeInternals_receiver(TTPtr self, TTAddress address, TTSymbol name, t_symbol *callbackMethod, TTObject& returnedReceiver, TTBoolean deferlow, TTBoolean appendNameAsAttribute)
{
	WrappedModularInstancePtr	x = (WrappedModularInstancePtr)self;
	TTValue			v, args, baton;
	TTObject        returnValueCallback, empty;
	TTAddress       adrs;
    
    // check the internals do not exist yet
    if (!x->internals->lookup(name, v)) {
        returnedReceiver = v[0];
        JamomaDebug object_post((t_object*)x, "makeInternals_receiver : \"%s\" internal already exists", name.c_str());
        returnedReceiver.send("Get");
        return kTTErrNone;
    }
	
	// prepare arguments
	
	// we don't want the address back
	args.append(empty);
	
	returnValueCallback = TTObject("callback");
    
	baton = TTValue(TTPtr(x), TTPtr(callbackMethod), deferlow);
    
	returnValueCallback.set(kTTSym_baton, baton);
	returnValueCallback.set(kTTSym_function, TTPtr(&jamoma_callback_return_value));
	args.append(returnValueCallback);
	
	returnedReceiver = TTObject(kTTSym_Receiver, args);
	
	// edit address
	if (appendNameAsAttribute)
        adrs = address.appendAttribute(name);
    else
        adrs = address.appendAddress(TTAddress(name.c_str()));
	
	// default registration case : store object only (see in unregister method)
	x->internals->append(name, returnedReceiver);
    
    // set address attribute (after registration as the value can be updated in the same time)
    returnedReceiver.set(kTTSym_address, adrs);
    
    JamomaDebug object_post((t_object*)x, "makes internal \"%s\" receiver to bind on : %s", name.c_str(), adrs.c_str());
    
	return kTTErrNone;
}