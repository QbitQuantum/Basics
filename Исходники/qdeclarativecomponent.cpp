QObject * QDeclarativeComponentPrivate::begin(QDeclarativeContextData *parentContext, 
                                              QDeclarativeContextData *componentCreationContext,
                                              QDeclarativeCompiledData *component, int start, int count,
                                              ConstructionState *state, QList<QDeclarativeError> *errors)
{
    QDeclarativeEnginePrivate *enginePriv = QDeclarativeEnginePrivate::get(parentContext->engine);
    bool isRoot = !enginePriv->inBeginCreate;

    Q_ASSERT(!isRoot || state); // Either this isn't a root component, or a state data must be provided
    Q_ASSERT((state != 0) ^ (errors != 0)); // One of state or errors (but not both) must be provided

    QDeclarativeContextData *ctxt = new QDeclarativeContextData;
    ctxt->isInternal = true;
    ctxt->url = component->url;
    ctxt->imports = component->importCache;

    // Nested global imports
    if (componentCreationContext && start != -1) 
        ctxt->importedScripts = componentCreationContext->importedScripts;

    component->importCache->addref();
    ctxt->setParent(parentContext);

    enginePriv->inBeginCreate = true;

    QDeclarativeVME vme;
    QObject *rv = vme.run(ctxt, component, start, count);

    if (vme.isError()) {
       if(errors) *errors = vme.errors();
       else state->errors = vme.errors();
    }

    if (isRoot) {
        enginePriv->inBeginCreate = false;

        state->bindValues = enginePriv->bindValues;
        state->parserStatus = enginePriv->parserStatus;
        state->finalizedParserStatus = enginePriv->finalizedParserStatus;
        state->componentAttached = enginePriv->componentAttached;
        if (state->componentAttached)
            state->componentAttached->prev = &state->componentAttached;

        enginePriv->componentAttached = 0;
        enginePriv->bindValues.clear();
        enginePriv->parserStatus.clear();
        enginePriv->finalizedParserStatus.clear();
        state->completePending = true;
        enginePriv->inProgressCreations++;
    }

    return rv;
}