    // Symbol.for as described in ES 2015
    Var JavascriptSymbol::EntryFor(RecyclableObject* function, CallInfo callInfo, ...)
    {
        PROBE_STACK(function->GetScriptContext(), Js::Constants::MinStackDefault);

        ARGUMENTS(args, callInfo);
        AssertMsg(args.Info.Count, "Should always have implicit 'this'.");
        ScriptContext* scriptContext = function->GetScriptContext();
        JavascriptLibrary* library = scriptContext->GetLibrary();

        Assert(!(callInfo.Flags & CallFlags_New));

        JavascriptString* key;

        if (args.Info.Count > 1)
        {
            key = JavascriptConversion::ToString(args[1], scriptContext);
        }
        else
        {
            key = library->GetUndefinedDisplayString();
        }

        // Search the global symbol registration map for a symbol with description equal to the string key.
        // The map can only have one symbol with that description so if we found a symbol, that is the registered
        // symbol for the string key.
        const Js::PropertyRecord* propertyRecord = scriptContext->GetThreadContext()->GetSymbolFromRegistrationMap(key->GetString(), key->GetLength());

        // If we didn't find a PropertyRecord in the map, we'll create a new symbol with description equal to the key string.
        // This is the only place we add new PropertyRecords to the map, so we should never have multiple PropertyRecords in the
        // map with the same string key value (since we would return the one we found above instead of creating a new one).
        if (propertyRecord == nullptr)
        {
            propertyRecord = scriptContext->GetThreadContext()->AddSymbolToRegistrationMap(key->GetString(), key->GetLength());
        }

        Assert(propertyRecord != nullptr);

        return library->CreateSymbol(propertyRecord);
    }