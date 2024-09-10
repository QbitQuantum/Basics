    Status EOFRunner::getInfo(TypeExplain** explain,
                              PlanInfo** planInfo) const {
        if (NULL != explain) {
            *explain = new TypeExplain;

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
        }
        else if (NULL != planInfo) {
            *planInfo = new PlanInfo();
            (*planInfo)->planSummary = "EOF";
        }

        return Status::OK();
    }