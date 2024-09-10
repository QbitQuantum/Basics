Boolean HelpUtils::PrepareHelpMenuItem(
    /* [in] */ IContext* context,
    /* [in] */ IMenuItem* helpMenuItem,
    /* [in] */ const String& helpUrlString)
{
    if (TextUtils::IsEmpty(helpUrlString)) {
        // The help url string is empty or NULL, so set the help menu item to be invisible.
        helpMenuItem->SetVisible(FALSE);

        // return that the help menu item is not visible (i.e. FALSE)
        return FALSE;
    }
    else {
        // The help url string exists, so first add in some extra query parameters.
        AutoPtr<IUriHelper> helper;
        CUriHelper::AcquireSingleton((IUriHelper**)&helper);
        AutoPtr<IUri> baseUri;
        helper->Parse(helpUrlString, (IUri**)&baseUri);
        AutoPtr<IUri> fullUri = UriWithAddedParameters(context, baseUri);

        // Then, create an intent that will be fired when the user
        // selects this help menu item.
        AutoPtr<IIntent> intent;
        CIntent::New(IIntent::ACTION_VIEW, fullUri, (IIntent**)&intent);
        intent->SetFlags(IIntent::FLAG_ACTIVITY_NEW_TASK
                | IIntent::FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS);

        // Set the intent to the help menu item, show the help menu item in the overflow
        // menu, and make it visible.
        AutoPtr<IPackageManager> manager;
        context->GetPackageManager((IPackageManager**)&manager);
        AutoPtr<IComponentName> component;
        intent->ResolveActivity(manager, (IComponentName**)&component);
        if (component != NULL) {
            helpMenuItem->SetIntent(intent);
            helpMenuItem->SetShowAsAction(IMenuItem::SHOW_AS_ACTION_NEVER);
            helpMenuItem->SetVisible(TRUE);
        }
        else {
            helpMenuItem->SetVisible(FALSE);
            return FALSE;
        }

        // return that the help menu item is visible (i.e., TRUE)
        return TRUE;
    }
}