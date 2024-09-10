static void
StatsCellCallback(JSRuntime *rt, void *data, void *thing, JSGCTraceKind traceKind,
                  size_t thingSize)
{
    IteratorClosure *closure = static_cast<IteratorClosure *>(data);
    RuntimeStats *rtStats = closure->rtStats;
    CompartmentStats *cStats = rtStats->currCompartmentStats;
    switch (traceKind) {
    case JSTRACE_OBJECT:
    {
        JSObject *obj = static_cast<JSObject *>(thing);
        if (obj->isFunction()) {
            cStats->gcHeapObjectsFunction += thingSize;
        } else if (obj->isDenseArray()) {
            cStats->gcHeapObjectsDenseArray += thingSize;
        } else if (obj->isSlowArray()) {
            cStats->gcHeapObjectsSlowArray += thingSize;
        } else if (obj->isCrossCompartmentWrapper()) {
            cStats->gcHeapObjectsCrossCompartmentWrapper += thingSize;
        } else {
            cStats->gcHeapObjectsOrdinary += thingSize;
        }
        size_t slotsSize, elementsSize, argumentsDataSize, regExpStaticsSize,
               propertyIteratorDataSize;
        obj->sizeOfExcludingThis(rtStats->mallocSizeOf, &slotsSize, &elementsSize,
                                 &argumentsDataSize, &regExpStaticsSize,
                                 &propertyIteratorDataSize);
        cStats->objectsExtraSlots += slotsSize;
        cStats->objectsExtraElements += elementsSize;
        cStats->objectsExtraArgumentsData += argumentsDataSize;
        cStats->objectsExtraRegExpStatics += regExpStaticsSize;
        cStats->objectsExtraPropertyIteratorData += propertyIteratorDataSize;

        if (ObjectPrivateVisitor *opv = closure->opv) {
            js::Class *clazz = js::GetObjectClass(obj);
            if (clazz->flags & JSCLASS_HAS_PRIVATE &&
                clazz->flags & JSCLASS_PRIVATE_IS_NSISUPPORTS)
            {
                cStats->objectsExtraPrivate += opv->sizeOfIncludingThis(GetObjectPrivate(obj));
            }
        }
        break;
    }
    case JSTRACE_STRING:
    {
        JSString *str = static_cast<JSString *>(thing);

        size_t strSize = str->sizeOfExcludingThis(rtStats->mallocSizeOf);

        // If we can't grow hugeStrings, let's just call this string non-huge.
        // We're probably about to OOM anyway.
        if (strSize >= HugeStringInfo::MinSize() && cStats->hugeStrings.growBy(1)) {
            cStats->gcHeapStringsNormal += thingSize;
            HugeStringInfo &info = cStats->hugeStrings.back();
            info.length = str->length();
            info.size = strSize;
            PutEscapedString(info.buffer, sizeof(info.buffer), &str->asLinear(), 0);
        } else if (str->isShort()) {
            MOZ_ASSERT(strSize == 0);
            cStats->gcHeapStringsShort += thingSize;
        } else {
            cStats->gcHeapStringsNormal += thingSize;
            cStats->stringCharsNonHuge += strSize;
        }
        break;
    }
    case JSTRACE_SHAPE:
    {
        Shape *shape = static_cast<Shape*>(thing);
        size_t propTableSize, kidsSize;
        shape->sizeOfExcludingThis(rtStats->mallocSizeOf, &propTableSize, &kidsSize);
        if (shape->inDictionary()) {
            cStats->gcHeapShapesDict += thingSize;
            cStats->shapesExtraDictTables += propTableSize;
            JS_ASSERT(kidsSize == 0);
        } else {
            if (shape->base()->getObjectParent() == shape->compartment()->maybeGlobal()) {
                cStats->gcHeapShapesTreeGlobalParented += thingSize;
            } else {
                cStats->gcHeapShapesTreeNonGlobalParented += thingSize;
            }
            cStats->shapesExtraTreeTables += propTableSize;
            cStats->shapesExtraTreeShapeKids += kidsSize;
        }
        break;
    }
    case JSTRACE_BASE_SHAPE:
    {
        cStats->gcHeapShapesBase += thingSize;
        break;
    }
    case JSTRACE_SCRIPT:
    {
        JSScript *script = static_cast<JSScript *>(thing);
        cStats->gcHeapScripts += thingSize;
        cStats->scriptData += script->sizeOfData(rtStats->mallocSizeOf);
#ifdef JS_METHODJIT
        cStats->jaegerData += script->sizeOfJitScripts(rtStats->mallocSizeOf);
# ifdef JS_ION
        cStats->ionData += ion::MemoryUsed(script, rtStats->mallocSizeOf);
# endif
#endif

        ScriptSource *ss = script->scriptSource();
        SourceSet::AddPtr entry = closure->seenSources.lookupForAdd(ss);
        if (!entry) {
            closure->seenSources.add(entry, ss); // Not much to be done on failure.
            rtStats->runtime.scriptSources += ss->sizeOfIncludingThis(rtStats->mallocSizeOf);
        }
        break;
    }
    case JSTRACE_IONCODE:
    {
#ifdef JS_METHODJIT
# ifdef JS_ION
        cStats->gcHeapIonCodes += thingSize;
        // The code for a script is counted in ExecutableAllocator::sizeOfCode().
# endif
#endif
        break;
    }
    case JSTRACE_TYPE_OBJECT:
    {
        types::TypeObject *obj = static_cast<types::TypeObject *>(thing);
        cStats->gcHeapTypeObjects += thingSize;
        obj->sizeOfExcludingThis(&cStats->typeInferenceSizes, rtStats->mallocSizeOf);
        break;
    }
#if JS_HAS_XML_SUPPORT
    case JSTRACE_XML:
    {
        cStats->gcHeapXML += thingSize;
        break;
    }
#endif
    }
    // Yes, this is a subtraction:  see StatsArenaCallback() for details.
    cStats->gcHeapUnusedGcThings -= thingSize;
}