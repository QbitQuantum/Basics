ECode MenuBuilder::SaveActionViewStates(
    /* [in] */ IBundle* outStates)
{
    assert(outStates != NULL);
    AutoPtr<ISparseArray> viewStates;

    Int32 itemCount;
    GetSize(&itemCount);
    for (Int32 i = 0; i < itemCount; i++) {
        AutoPtr<IMenuItem> item;
        GetItem(i, (IMenuItem**)&item);
        AutoPtr<IView> v;
        item->GetActionView((IView**)&v);

        Int32 id = 0;
        if (v != NULL && (v->GetId(&id), id) != IView::NO_ID) {
            if (viewStates == NULL) {
                CSparseArray::New((ISparseArray**)&viewStates);
            }

            v->SaveHierarchyState(viewStates);

            Boolean expanded = FALSE;
            if (item->IsActionViewExpanded(&expanded), expanded) {
                item->GetItemId(&id);
                outStates->PutInt32(EXPANDED_ACTION_VIEW_ID, id);
            }
        }

        Boolean has = FALSE;
        if (item->HasSubMenu(&has), has) {
            AutoPtr<ISubMenu> submenu;
            item->GetSubMenu((ISubMenu**)&submenu);
            IMenuBuilder::Probe(submenu)->SaveActionViewStates(outStates);
        }
    }

    if (viewStates != NULL) {
        String key;
        GetActionViewStatesKey(&key);
        outStates->PutSparseParcelableArray(key, viewStates);
    }

    return NOERROR;
}