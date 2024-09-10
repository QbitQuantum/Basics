AAFRESULT STDMETHODCALLTYPE
ImplAAFTypeDefExtEnum::CreateValueFromName (
											/*[in]*/ aafCharacter_constptr  Name,
											/*[out]*/ ImplAAFPropertyValue ** ppPropVal)
{
	if (! ppPropVal )
		return AAFRESULT_NULL_PARAM;
	
	if (! Name )
		return AAFRESULT_NULL_PARAM;
	
	if (!IsRegistered())
		return AAFRESULT_NOT_INITIALIZED;
	
	
	//Now try to do a Name lookup
	aafUID_t the_value = {0};
	AAFRESULT rc;
	rc = LookupValByName(&the_value, Name);
	

	if (rc == AAFRESULT_INVALID_PARAM)
		{
	    // Built-In names changed from v1.0 -> v1.1
	    // to remove kAAF prefix. so we have to deal with both
	    // old and new style names. 
	    // The lookup on the originally provided name failed due to
	    // the name not being found (not some other error).
	    // So here we add kAAF if it isn't there or 
	    // remove kAAF if it is there. Then look up again.
	    aafCharacter *Name_mod;

	    if ( wcsncmp (Name, L"kAAF", 4) == 0 )
	    {
		// Look past kAAF
		Name_mod = new aafCharacter[wcslen(Name) - 3];
		wcscpy(Name_mod, Name + 4);
	    }
	    else
	    {
		// Prepend kAAF
		Name_mod = new aafCharacter[wcslen(Name) + 5];
		if (!Name_mod)
		    return AAFRESULT_NOMEMORY;
		wcscpy(Name_mod, L"kAAF");
		wcscat(Name_mod, Name);
	    }

	    // Look up again - Return checked later.
	    rc = LookupValByName(&the_value, Name_mod);

	    // Cleanup of allocated memory
	    delete[] Name_mod;
	}

	// At this point, we have a successful lookup and the_val is
	// set, the name was not found (even with variation), or
	// some other error occurred. Check the result and return
	// if we are not successful.
	check_hr( rc );
	
	//else FOUND
	
	
	//Now allocate a New PV based on the local INT size ....
	
	ImplAAFTypeDef* ptd;
	ImplAAFTypeDefRecord* ptdAuid;
	
	ptd = NonRefCountedBaseType ();
	ASSERTU (ptd);
	
	ptdAuid = dynamic_cast<ImplAAFTypeDefRecord*> ((ImplAAFTypeDef*) ptd);
	ASSERTU (ptdAuid);
	
	HRESULT hr = ptdAuid->CreateValueFromStruct ((aafMemPtr_t) &the_value, sizeof (aafUID_t),
		ppPropVal);
	
	return hr;
}