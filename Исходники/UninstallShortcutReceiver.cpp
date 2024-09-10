void UninstallShortcutReceiver::RemoveShortcut(
    /* [in] */ IContext* context,
    /* [in] */ IIntent* data,
    /* [in] */ ISharedPreferences* sharedPrefs)
{
    AutoPtr<IParcelable> parcelable;
    data->GetParcelableExtra(IIntent::EXTRA_SHORTCUT_INTENT, (IParcelable**)&parcelable);
    AutoPtr<IIntent> intent = IIntent::Probe(parcelable);
    String name;
    data->GetStringExtra(IIntent::EXTRA_SHORTCUT_NAME, &name);
    Boolean duplicate;
    data->GetBooleanExtra(ILauncher::EXTRA_SHORTCUT_DUPLICATE, TRUE, &duplicate);

    if (intent != NULL && name != NULL) {
        AutoPtr<IContentResolver> cr;
        context->GetContentResolver((IContentResolver**)&cr);
        AutoPtr<ArrayOf<String> > array = ArrayOf<String>::Alloc(2);
        (*array)[0] = IBaseColumns::ID;
        (*array)[1] = LauncherSettings::Favorites::INTENT;
        StringBuilder sb;
        sb += LauncherSettings::Favorites::TITLE;
        sb += "=?";
        AutoPtr<ArrayOf<String> > names = ArrayOf<String>::Alloc(1);
        (*names)[0] = name;
        AutoPtr<ICursor> c;
        cr->Query(LauncherSettings::Favorites::CONTENT_URI,
            array, sb.ToString(), names, String(NULL), (ICursor**)&c);

        Int32 intentIndex;
        c->GetColumnIndexOrThrow(LauncherSettings::Favorites::INTENT, &intentIndex);
        Int32 idIndex;
        c->GetColumnIndexOrThrow(IBaseColumns::ID, &idIndex);

        Boolean changed = FALSE;

        //try {
        Boolean res;
        while (c->MoveToNext(&res), res) {
            //try {
            String index;
            c->GetString(intentIndex, &index);
            AutoPtr<IIntentHelper> helper;
            CIntentHelper::AcquireSingleton((IIntentHelper**)&helper);
            AutoPtr<IIntent> tmp;
            helper->ParseUri(index, 0, (IIntent**)&tmp);

            Boolean res;
            intent->FilterEquals(tmp, &res);
            if (res) {
                Int64 id;
                c->GetInt64(idIndex, &id);
                AutoPtr<IUri> uri;
                LauncherSettings::Favorites::GetContentUri(id, FALSE, (IUri**)&uri);
                Int32 num;
                cr->Delete(uri, String(NULL), NULL, &num);
                changed = TRUE;
                if (!duplicate) {
                    break;
                }
            }
            //} catch (URISyntaxException e) {
            // if (ec == (ECode)E_URI_SYNTAX_EXCEPTION) {
            //     // Ignore
            // }
            //}
        }
        //} finally {
            ICloseable::Probe(c)->Close();
        //}

        if (changed) {
            cr->NotifyChange(LauncherSettings::Favorites::CONTENT_URI, NULL);

            AutoPtr<ICharSequence> cchar = CoreUtils::Convert(name);
            AutoPtr<ArrayOf<IInterface*> > array = ArrayOf<IInterface*>::Alloc(1);
            array->Set(0, TO_IINTERFACE(cchar));
            String str;
            context->GetString(
                    Elastos::Droid::Launcher2::R::string::shortcut_uninstalled, array, &str);

            AutoPtr<IToastHelper> helper;
            CToastHelper::AcquireSingleton((IToastHelper**)&helper);
            AutoPtr<IToast> toast;
            AutoPtr<ICharSequence> cs = CoreUtils::Convert(str);
            helper->MakeText(context, cs, IToast::LENGTH_SHORT, (IToast**)&toast);
        }

        // Remove any items due to be animated
        Boolean appRemoved;
        AutoPtr<ISet> newApps;
        CHashSet::New((ISet**)&newApps);
        sharedPrefs->GetStringSet(IInstallShortcutReceiver::NEW_APPS_LIST_KEY, newApps, (ISet**)&newApps);
        synchronized(newApps) {
            do {
                String str;
                intent->ToUri(0, &str);
                AutoPtr<ICharSequence> cchar = CoreUtils::Convert(str);
                newApps->Remove(TO_IINTERFACE(cchar), &appRemoved);
            } while (appRemoved);
        }
        if (appRemoved) {
            AutoPtr<ISet> savedNewApps = newApps;
            AutoPtr<MyThread> thread = new MyThread(savedNewApps, sharedPrefs);
            thread->Start();
        }
    }