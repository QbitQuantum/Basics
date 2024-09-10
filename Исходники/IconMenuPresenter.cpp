ECode IconMenuPresenter::RestoreHierarchyState(
    /* [in] */ IBundle* inState)
{
    AutoPtr<ISparseArray> viewStates;
    inState->GetSparseParcelableArray(VIEWS_TAG, (ISparseArray**)&viewStates);

    if (viewStates != NULL) {
        IView::Probe(mMenuView)->RestoreHierarchyState(viewStates);
    }

    Int32 subMenuId;
    inState->GetInt32(OPEN_SUBMENU_KEY, 0, &subMenuId);
    if (subMenuId > 0 && mMenu != NULL) {
        AutoPtr<IMenuItem> item;
        IMenu::Probe(mMenu)->FindItem(subMenuId, (IMenuItem**)&item);
        if (item != NULL) {
            AutoPtr<ISubMenu> sm;
            item->GetSubMenu((ISubMenu**)&sm);
            Boolean rst;
            OnSubMenuSelected(ISubMenuBuilder::Probe(sm), &rst);
        }
    }
    return NOERROR;
}