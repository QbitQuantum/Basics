bool DINOTaskBoundaries::getTaskBoundariesFromCall (CallInst &CI, DINOGlobal::BasicBlockSet &TBs) {

    /*TBs Collects the Task Boundaries for this store instruction*/
    IsTaskBoundaryPredicate collect = IsTaskBoundaryPredicate();
    IsTaskBoundaryOrFunctionEntryPredicate stop = IsTaskBoundaryOrFunctionEntryPredicate();
    BasicBlock *CB = CI.getParent();

    DINOGlobal::BasicBlockList visited = DINOGlobal::BasicBlockList();

    DINOGlobal::CollectBBsPredicated(*CB, visited, TBs,
                         collect, /*Collection Predicate*/
                         stop);/*Traversal Stop Predicate*/

    return !stop.hitTaskBoundary;

}