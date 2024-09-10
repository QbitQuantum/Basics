ECode LocalViewOnLongClickListener::OnLongClick(
    /* [in] */ IView* v,
    /* [out] */ Boolean* result)
{
//    try {
    AutoPtr<IIntent> intent;
    CIntent::New(IIntent::ACTION_MAIN, (IIntent**)&intent);
    intent->SetFlags(IIntent::FLAG_ACTIVITY_NEW_TASK
            | IIntent::FLAG_ACTIVITY_CLEAR_TASK
            | IIntent::FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS);
    intent->AddCategory(String("com.android.internal.category.PLATLOGO"));
    mHost->StartActivity(intent);
        //.setClassName("com.android.systemui","com.android.systemui.BeanBag"));
//    } catch (ActivityNotFoundException ex) {
//        android.util.Log.e("PlatLogoActivity", "Couldn't find a bag of beans.");
//    }
    mHost->Finish();
    *result = TRUE;
    return NOERROR;
}