AutoPtr<IArrayMap> EnterTransitionCoordinator::MapNamedElements( //ArrayMap<String, View>
    /* [in] */ IArrayList* accepted,    //<String>
    /* [in] */ IArrayList* localNames)  //<String>
{
    AutoPtr<IArrayMap> sharedElements;
    CArrayMap::New((IArrayMap**)&sharedElements);
    AutoPtr<IViewGroup> vg;
    GetDecor((IViewGroup**)&vg);
    IView* decorView = IView::Probe(vg);
    if (decorView != NULL) {
        decorView->FindNamedViews(IMap::Probe(sharedElements));
    }
    if (accepted != NULL) {
        Int32 size;
        localNames->GetSize(&size);
        for (Int32 i = 0; i < size; i++) {
            AutoPtr<IInterface> localNameObj, acceptedObj;
            localNames->Get(i, (IInterface**)&localNameObj);
            accepted->Get(i, (IInterface**)&acceptedObj);

            if (localNameObj != NULL && !Object::Equals(localNameObj, acceptedObj)) {
                AutoPtr<IInterface> viewObj;
                sharedElements->Remove(localNameObj, (IInterface**)&viewObj);
                if (viewObj != NULL) {
                    sharedElements->Put(acceptedObj, viewObj);
                }
            }
        }
    }
    return sharedElements;
}