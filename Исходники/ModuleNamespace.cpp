    void ModuleNamespace::Initialize()
    {
        ScriptContext* scriptContext = moduleRecord->GetRealm()->GetScriptContext();
        Recycler* recycler = scriptContext->GetRecycler();
        SourceTextModuleRecord* sourceTextModuleRecord = static_cast<SourceTextModuleRecord*>(moduleRecord);
        JavascriptLibrary* library = GetLibrary();

        if (scriptContext->GetConfig()->IsES6ToStringTagEnabled())
        {
            DynamicObject::SetPropertyWithAttributes(PropertyIds::_symbolToStringTag, library->GetModuleTypeDisplayString(),
                PropertyConfigurable, nullptr);
        }

        DynamicType* type = library->CreateFunctionWithLengthType(&EntryInfo::SymbolIterator);
        RuntimeFunction* iteratorFunction = RecyclerNewEnumClass(scriptContext->GetRecycler(),
            library->EnumFunctionClass, RuntimeFunction,
            type, &EntryInfo::SymbolIterator);
        DynamicObject::SetPropertyWithAttributes(PropertyIds::_symbolIterator, iteratorFunction, PropertyBuiltInMethodDefaults, nullptr);

        ModuleImportOrExportEntryList* localExportList = sourceTextModuleRecord->GetLocalExportEntryList();
        // We don't have a type handler that can handle ModuleNamespace object. We have properties that could be aliased
        // like {export foo as foo1, foo2, foo3}, and external properties as reexport from current module. The problem with aliasing
        // is that multiple propertyId can be associated with one slotIndex. We need to build from PropertyMap directly here.
        // there is one instance of ModuleNamespace per module file; we can always use the BigPropertyIndex for security.
        propertyMap = RecyclerNew(recycler, SimplePropertyDescriptorMap, recycler, sourceTextModuleRecord->GetLocalExportCount());
        if (localExportList != nullptr)
        {
            localExportList->Map([=](ModuleImportOrExportEntry exportEntry) {
                PropertyId exportNameId = exportEntry.exportName->GetPropertyId();
                PropertyId localNameId = exportEntry.localName->GetPropertyId();
                const Js::PropertyRecord* exportNameRecord = scriptContext->GetThreadContext()->GetPropertyName(exportNameId);
                ModuleNameRecord* importRecord = nullptr;
                AssertMsg(exportNameId != Js::Constants::NoProperty, "should have been initialized already");
                // ignore local exports that are actually indirect exports.
                if (sourceTextModuleRecord->GetImportEntryList() == nullptr ||
                    (sourceTextModuleRecord->ResolveImport(localNameId, &importRecord)
                    && importRecord == nullptr))
                {
                    BigPropertyIndex index = sourceTextModuleRecord->GetLocalExportSlotIndexByExportName(exportNameId);
                    Assert((uint)index < sourceTextModuleRecord->GetLocalExportCount());
                    SimpleDictionaryPropertyDescriptor<BigPropertyIndex> propertyDescriptor = { index, PropertyModuleNamespaceDefault };
                    propertyMap->Add(exportNameRecord, propertyDescriptor);
                }
            });
        }
        // update the local slot to use the storage for local exports.
        SetNSSlotsForModuleNS(sourceTextModuleRecord->GetLocalExportSlots());

        // For items that are not in the local export list, we need to resolve them to get it 
        ExportedNames* exportedNames = sourceTextModuleRecord->GetExportedNames(nullptr);
        ModuleNameRecord* moduleNameRecord = nullptr;
#if DBG
        uint unresolvableExportsCount = 0;
        uint localExportCount = 0;
#endif
        if (exportedNames != nullptr)
        {
            exportedNames->Map([&](PropertyId propertyId) {
                if (!moduleRecord->ResolveExport(propertyId, nullptr, nullptr, &moduleNameRecord))
                {
                    // ignore ambigious resolution.
#if DBG
                    unresolvableExportsCount++;
#endif
                    return;
                }
                // non-ambiguous resolution.
                if (moduleNameRecord == nullptr)
                {
                    JavascriptError::ThrowSyntaxError(scriptContext, JSERR_ResolveExportFailed, scriptContext->GetPropertyName(propertyId)->GetBuffer());
                }
                if (moduleNameRecord->module == moduleRecord)
                {
                    // skip local exports as they are covered in the localExportSlots.
#if DBG
                    localExportCount++;
#endif
                    return;
                }
                Assert(moduleNameRecord->module != moduleRecord);
                this->AddUnambiguousNonLocalExport(propertyId, moduleNameRecord);
            });
        }
#if DBG
        uint totalExportCount = exportedNames != nullptr ? exportedNames->Count() : 0;
        uint unambiguousNonLocalCount = (this->GetUnambiguousNonLocalExports() != nullptr) ? this->GetUnambiguousNonLocalExports()->Count() : 0;
        Assert(totalExportCount == localExportCount + unambiguousNonLocalCount + unresolvableExportsCount);
#endif
        BOOL result = this->PreventExtensions();
        Assert(result);
    }