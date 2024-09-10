// static
nsresult
nsXPCWrappedJS::GetNewOrUsed(JS::HandleObject jsObj,
                             REFNSIID aIID,
                             nsISupports* aOuter,
                             nsXPCWrappedJS** wrapperResult)
{
    // Do a release-mode assert against accessing nsXPCWrappedJS off-main-thread.
    if (!MOZ_LIKELY(NS_IsMainThread() || NS_IsCycleCollectorThread()))
        MOZ_CRASH();

    AutoJSContext cx;
    JSObject2WrappedJSMap* map;
    nsXPCWrappedJS* root = nullptr;
    nsXPCWrappedJS* wrapper = nullptr;
    nsXPCWrappedJSClass* clazz = nullptr;
    XPCJSRuntime* rt = nsXPConnect::GetRuntimeInstance();
    bool release_root = false;

    map = rt->GetWrappedJSMap();
    if (!map) {
        NS_ASSERTION(map,"bad map");
        return NS_ERROR_FAILURE;
    }

    nsXPCWrappedJSClass::GetNewOrUsed(cx, aIID, &clazz);
    if (!clazz)
        return NS_ERROR_FAILURE;
    // from here on we need to return through 'return_wrapper'

    // always find the root JSObject
    JS::RootedObject rootJSObj(cx, clazz->GetRootJSObject(cx, jsObj));
    if (!rootJSObj)
        goto return_wrapper;

    // look for the root wrapper, and if found, hold the map lock until
    // we've added our ref to prevent another thread from destroying it
    // under us
    {   // scoped lock
        XPCAutoLock lock(rt->GetMapLock());
        root = map->Find(rootJSObj);
        if (root) {
            if ((nullptr != (wrapper = root->Find(aIID))) ||
                (nullptr != (wrapper = root->FindInherited(aIID)))) {
                NS_ADDREF(wrapper);
                goto return_wrapper;
            }
        }
    }

    if (!root) {
        // build the root wrapper
        if (rootJSObj == jsObj) {
            // the root will do double duty as the interface wrapper
            wrapper = root = new nsXPCWrappedJS(cx, jsObj, clazz, nullptr,
                                                aOuter);
            if (!root)
                goto return_wrapper;

            {   // scoped lock
#if DEBUG_xpc_leaks
                printf("Created nsXPCWrappedJS %p, JSObject is %p\n",
                       (void*)wrapper, (void*)jsObj);
#endif
                XPCAutoLock lock(rt->GetMapLock());
                map->Add(cx, root);
            }

            if (!CheckMainThreadOnly(root)) {
                XPCAutoLock lock(rt->GetMapLock());
                map->Remove(root);

                wrapper = NULL;
            }

            goto return_wrapper;
        } else {
            // just a root wrapper
            nsXPCWrappedJSClass* rootClazz = nullptr;
            nsXPCWrappedJSClass::GetNewOrUsed(cx, NS_GET_IID(nsISupports),
                                              &rootClazz);
            if (!rootClazz)
                goto return_wrapper;

            root = new nsXPCWrappedJS(cx, rootJSObj, rootClazz, nullptr, aOuter);
            NS_RELEASE(rootClazz);

            if (!root)
                goto return_wrapper;

            release_root = true;

            {   // scoped lock
#if DEBUG_xpc_leaks
                printf("Created nsXPCWrappedJS %p, JSObject is %p\n",
                       (void*)root, (void*)rootJSObj);
#endif
                XPCAutoLock lock(rt->GetMapLock());
                map->Add(cx, root);
            }

            if (!CheckMainThreadOnly(root)) {
                XPCAutoLock lock(rt->GetMapLock());
                map->Remove(root);

                goto return_wrapper;
            }
        }
    }

    // at this point we have a root and may need to build the specific wrapper
    NS_ASSERTION(root,"bad root");
    NS_ASSERTION(clazz,"bad clazz");

    if (!wrapper) {
        wrapper = new nsXPCWrappedJS(cx, jsObj, clazz, root, aOuter);
        if (!wrapper)
            goto return_wrapper;
#if DEBUG_xpc_leaks
        printf("Created nsXPCWrappedJS %p, JSObject is %p\n",
               (void*)wrapper, (void*)jsObj);
#endif
    }

    wrapper->mNext = root->mNext;
    root->mNext = wrapper;

return_wrapper:
    if (clazz)
        NS_RELEASE(clazz);

    if (release_root)
        NS_RELEASE(root);

    if (!wrapper)
        return NS_ERROR_FAILURE;

    *wrapperResult = wrapper;
    return NS_OK;
}