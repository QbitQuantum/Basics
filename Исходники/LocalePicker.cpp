ECode LocalePicker::GetAllAssetLocales(
    /* [in] */ IContext* context,
    /* [in] */ Boolean isInDeveloperMode,
    /* [out] */ IList** list)
{
    VALIDATE_NOT_NULL(list);

    AutoPtr<IResources> resources;
    context->GetResources((IResources**)&resources);
    AutoPtr<IAssetManager> assetMgr;
    CResources::GetSystem()->GetAssets((IAssetManager**)&assetMgr);
    AutoPtr<ArrayOf<String> > locales;
    assetMgr->GetLocales((ArrayOf<String>**)&locales);

    AutoPtr<IList> localeList;
    CArrayList::New(locales->GetLength(), (IList**)&localeList);
    for (Int32 i = 0; i < locales->GetLength(); i++) {
        Boolean b;
        localeList->Add(CoreUtils::Convert((*locales)[i]), &b);
    }

    // Don't show the pseudolocales unless we're in developer mode. http://b/17190407.
    if (!isInDeveloperMode) {
        localeList->Remove(CoreUtils::Convert(String("ar-XB")));
        localeList->Remove(CoreUtils::Convert(String("en-XA")));
    }

    AutoPtr<ICollections> collections;
    CCollections::AcquireSingleton((ICollections**)&collections);
    collections->Sort(localeList);
    AutoPtr<ArrayOf<String> > specialLocaleCodes;
    resources->GetStringArray(R::array::special_locale_codes, (ArrayOf<String>**)&specialLocaleCodes);
    AutoPtr<ArrayOf<String> > specialLocaleNames;
    resources->GetStringArray(R::array::special_locale_names, (ArrayOf<String>**)&specialLocaleNames);

    Int32 size;
    localeList->GetSize(&size);
    AutoPtr<IList> localeInfos;
    CArrayList::New(size, (IList**)&localeInfos);
    for (Int32 i = 0; i < size; i++) {
        AutoPtr<IInterface> item;
        localeList->Get(i, (IInterface**)&item);
        String locale;
        ICharSequence::Probe(item)->ToString(&locale);
        AutoPtr<ILocaleHelper> lHelper;
        CLocaleHelper::AcquireSingleton((ILocaleHelper**)&lHelper);
        AutoPtr<ILocale> l;
        lHelper->ForLanguageTag(locale.Replace('_', '-'), (ILocale**)&l);
        String language, country ;
        if (l == NULL || (l->GetLanguage(&language), language.Equals("und"))
            || language.IsEmpty() || (l->GetCountry(&country), country.IsEmpty())) {
            continue;
        }

        Boolean isEmpty;
        localeInfos->IsEmpty(&isEmpty);
        String dl;
        l->GetDisplayLanguage(l, &dl);
        if (isEmpty) {
            if (DEBUG) {
                Logger::V(TAG, "adding initial %s", ToTitleCase(dl).string());
            }
            AutoPtr<ILocaleInfo> info = new LocaleInfo(ToTitleCase(dl), l);
            localeInfos->Add(info);
        }
        else {
            // check previous entry:
            //  same lang and a country -> upgrade to full name and
            //    insert ours with full name
            //  diff lang -> insert ours with lang-only name
            Int32 count;
            localeInfos->GetSize(&count);
            AutoPtr<IInterface> item;
            localeInfos->Get(count - 1, (IInterface**)&item);
            LocaleInfo* previous = (LocaleInfo*)ILocaleInfo::Probe(item);
            String prevLang;
            previous->mLocale->GetLanguage(&prevLang);
            if (prevLang.Equals(language) && !prevLang.Equals("zz")) {
                if (DEBUG) {
                    Logger::V(TAG, "backing up and fixing %s to %s", previous->mLabel.string(),
                        GetDisplayName(previous->mLocale, specialLocaleCodes, specialLocaleNames).string());
                }
                previous->mLabel = ToTitleCase(GetDisplayName(
                        previous->mLocale, specialLocaleCodes, specialLocaleNames));
                if (DEBUG) {
                    Logger::V(TAG, "  and adding %s", ToTitleCase(
                        GetDisplayName(l, specialLocaleCodes, specialLocaleNames)).string());
                }
                AutoPtr<ILocaleInfo> info = new LocaleInfo(ToTitleCase(
                    GetDisplayName(l, specialLocaleCodes, specialLocaleNames)), l);
                localeInfos->Add(info);
            }
            else {
                String displayName = ToTitleCase(dl);
                if (DEBUG) {
                    Logger::V(TAG, "Adding %s", displayName.string());
                }
                AutoPtr<ILocaleInfo> info = new LocaleInfo(displayName, l);
                localeInfos->Add(info);
            }
        }
    }

    collections->Sort(localeInfos);
    *list = localeInfos;
    REFCOUNT_ADD(*list);
    return NOERROR;
}