ECode AllAppsList::RemovePackage(
    /* [in] */ const String& packageName,
    /* [in] */ IUserHandle* user)
{
    AutoPtr<IList> data = mData;
    Int32 size;
    data->GetSize(&size);
    for (Int32 i = size - 1; i >= 0; i--) {
        AutoPtr<IInterface> obj;
        data->Get(i, (IInterface**)&obj);
        AutoPtr<ApplicationInfo> info = (ApplicationInfo*)IObject::Probe(obj);

        AutoPtr<IComponentName> component;
        info->mIntent->GetComponent((IComponentName**)&component);

        Boolean res;
        info->mUser->Equals(user, &res);
        if (res) {
            String name;
            component->GetPackageName(&name);
            Boolean tmp;
            packageName.Equals(name, &tmp);
            if (tmp) {
                removed->Add(info);
                data->Remove(i);
            }
        }
    }
    // This is more aggressive than it needs to be.
    return mIconCache->Flush();
}