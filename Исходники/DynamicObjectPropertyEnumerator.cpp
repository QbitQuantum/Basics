    void DynamicObjectPropertyEnumerator::Reset()
    {
        if (this->object)
        {
            enumeratedCount = 0;
            initialType = object->GetDynamicType();
            objectIndex = Constants::NoBigSlot;
            initialPropertyCount = GetSnapShotSemantics() ? this->object->GetPropertyCount() : Constants::NoBigSlot;
            // Create the appropriate enumerator object.
            if (GetSnapShotSemantics() && this->initialType->PrepareForTypeSnapshotEnumeration())
            {
                ScriptContext* scriptContext = this->object->GetScriptContext();
                ThreadContext * threadContext = scriptContext->GetThreadContext();
                CachedData * data = (CachedData *)threadContext->GetDynamicObjectEnumeratorCache(this->initialType);

                if (data == nullptr || data->scriptContext != this->requestContext || data->enumNonEnumerable != GetEnumNonEnumerable() || data->enumSymbols != GetEnumSymbols())
                {
                    data = RecyclerNewStructPlus(scriptContext->GetRecycler(),
                        this->initialPropertyCount * sizeof(PropertyString *) + this->initialPropertyCount * sizeof(BigPropertyIndex) + this->initialPropertyCount * sizeof(PropertyAttributes), CachedData);
                    data->scriptContext = requestContext;
                    data->cachedCount = 0;
                    data->strings = (PropertyString **)(data + 1);
                    data->indexes = (BigPropertyIndex *)(data->strings + this->initialPropertyCount);
                    data->attributes = (PropertyAttributes*)(data->indexes + this->initialPropertyCount);
                    data->completed = false;
                    data->enumNonEnumerable = GetEnumNonEnumerable();
                    data->enumSymbols = GetEnumSymbols();
                    threadContext->AddDynamicObjectEnumeratorCache(this->initialType, data);
                }
                this->cachedData = data;
                this->cachedDataType = this->initialType;
            }
            else
            {
                this->cachedData = nullptr;
                this->cachedDataType = nullptr;
            }
        }
    }