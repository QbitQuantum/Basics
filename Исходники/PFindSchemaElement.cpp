void PFindSchemaElement::start()
{
    /* 1) add actions
       2) start actions
       3) wait signals */

    // Evalutate requires
    QList<PSchemaElement> childRequireSchemas = m_from.schema().requires();
    if (!childRequireSchemas.isEmpty()) {
        // there is at least one require to evaluate
        PActionGroup *evalRequireGroup = new PActionGroup(this);
        evalRequireGroup->setSingleStatusToStop(PAction::StatusFailure, PAction::StatusFailure);
        for (int i=0; i<childRequireSchemas.length(); i++) {
            // add the require evaluator for the current require to the action group
            PWrapperRequire *require = m_from.childRequire(childRequireSchemas.at(i));
            PEvalWrapperRequire *evalRequire = new PEvalWrapperRequire(require);
            evalRequireGroup->addAction(evalRequire);
            // fail if the group fails
            connect(evalRequireGroup, SIGNAL(failure(PAction::StatusType)), this, SLOT(finish(PAction::StatusType)));
        }

    }
}