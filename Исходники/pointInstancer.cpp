static
bool 
_SetOrMergeOverOp(std::vector<int64_t> const &items, SdfListOpType op,
                  UsdPrim const &prim)
{
    SdfInt64ListOp  proposed, current;
    UsdStagePtr stage = prim.GetStage();
    UsdEditTarget editTarget = stage->GetEditTarget();
    SdfPrimSpecHandle  primSpec = 
        editTarget.GetPrimSpecForScenePath(prim.GetPath());
    
    if (primSpec){
        VtValue  existingOp = primSpec->GetInfo(UsdGeomTokens->inactiveIds);
        if (existingOp.IsHolding<SdfInt64ListOp>()){
            current = existingOp.UncheckedGet<SdfInt64ListOp>();
        }
    }

    proposed.SetItems(items, op);
    if (current.IsExplicit()){
        std::vector<int64_t> explicitItems = current.GetExplicitItems();
        proposed.ApplyOperations(&explicitItems);
        current.SetExplicitItems(explicitItems);
    }
    else {
        // We can't use ApplyOperations on an extant, non-explicit listOp
        // because the result is always flat and explicit.
        current.ComposeOperations(proposed, op);
        // ComposeOperations() is too narrow in functionality - it does not
        // consider that if we "remove over" an existing set of added items,
        // we need to additionally ensure the removed items get removed
        // from the added in current, since when applying ops, we first
        // remove, then add.  Bug #139215 filed to track; when it gets fixed
        // we can remove this code!
        if (op == SdfListOpTypeDeleted){
            std::vector<int64_t> addedItems = current.GetAddedItems();
            if (!addedItems.empty()){
                std::set<int64_t> toRemove(items.begin(), items.end());
                std::vector<int64_t> newAdded;
                newAdded.reserve(addedItems.size());
                for (auto elt : addedItems){
                    if (!toRemove.count(elt))
                        newAdded.push_back(elt);
                }
                if (newAdded.size() != addedItems.size())
                    current.SetAddedItems(newAdded);
            }
        }
        else if (op == SdfListOpTypeAdded){
            std::vector<int64_t> deletedItems = current.GetDeletedItems();
            if (!deletedItems.empty()){
                std::set<int64_t> toAdd(items.begin(), items.end());
                std::vector<int64_t> newDeleted;
                newDeleted.reserve(deletedItems.size());
                for (auto elt : deletedItems){
                    if (!toAdd.count(elt))
                        newDeleted.push_back(elt);
                }
                if (newDeleted.size() != deletedItems.size())
                    current.SetDeletedItems(newDeleted);
            }
        }
    }
    return prim.SetMetadata(UsdGeomTokens->inactiveIds, current);
}