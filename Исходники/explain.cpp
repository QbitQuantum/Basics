    // TODO: This is temporary and should get deleted. There are a few small ways in which
    // this differs from 2.6 explain, but I'm not too worried because this entire format is
    // going away soon:
    //  1) 'indexBounds' field excluded from idhack explain.
    //  2) 'filterSet' field (for index filters) excluded.
    Status Explain::legacyExplain(PlanExecutor* exec, TypeExplain** explain) {
        invariant(exec);
        invariant(explain);

        scoped_ptr<PlanStageStats> stats(exec->getStats());
        if (NULL == stats.get()) {
            return Status(ErrorCodes::InternalError, "no stats available to explain plan");
        }

        // Special explain format for EOF.
        if (STAGE_EOF == stats->stageType) {
            *explain = new TypeExplain();

            // Fill in mandatory fields.
            (*explain)->setN(0);
            (*explain)->setNScannedObjects(0);
            (*explain)->setNScanned(0);

            // Fill in all the main fields that don't have a default in the explain data structure.
            (*explain)->setCursor("BasicCursor");
            (*explain)->setScanAndOrder(false);
            (*explain)->setIsMultiKey(false);
            (*explain)->setIndexOnly(false);
            (*explain)->setNYields(0);
            (*explain)->setNChunkSkips(0);

            TypeExplain* allPlans = new TypeExplain;
            allPlans->setCursor("BasicCursor");
            (*explain)->addToAllPlans(allPlans); // ownership xfer

            (*explain)->setNScannedObjectsAllPlans(0);
            (*explain)->setNScannedAllPlans(0);

            return Status::OK();
        }

        // Special explain format for idhack.
        vector<PlanStageStats*> statNodes;
        flattenStatsTree(stats.get(), &statNodes);
        PlanStageStats* idhack = NULL;
        for (size_t i = 0; i < statNodes.size(); i++) {
            if (STAGE_IDHACK == statNodes[i]->stageType) {
                idhack = statNodes[i];
                break;
            }
        }

        if (NULL != idhack) {
            // Explain format does not match 2.4 and is intended
            // to indicate clearly that the ID hack has been applied.
            *explain = new TypeExplain();

            IDHackStats* idhackStats = static_cast<IDHackStats*>(idhack->specific.get());

            (*explain)->setCursor("IDCursor");
            (*explain)->setIDHack(true);
            (*explain)->setN(stats->common.advanced);
            (*explain)->setNScanned(idhackStats->keysExamined);
            (*explain)->setNScannedObjects(idhackStats->docsExamined);

            return Status::OK();
        }

        Status status = explainPlan(*stats, explain, true /* full details */);
        if (!status.isOK()) {
            return status;
        }

        // Fill in explain fields that are accounted by on the runner level.
        TypeExplain* chosenPlan = NULL;
        explainPlan(*stats, &chosenPlan, false /* no full details */);
        if (chosenPlan) {
            (*explain)->addToAllPlans(chosenPlan);
        }
        (*explain)->setNScannedObjectsAllPlans((*explain)->getNScannedObjects());
        (*explain)->setNScannedAllPlans((*explain)->getNScanned());

        return Status::OK();
    }