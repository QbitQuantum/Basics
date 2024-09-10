// Runs on the handler.
void WifiDisplayAdapter::HandleUpdateNotification()
{
    Boolean isConnected;
    {
        AutoLock lock(GetSyncRoot());

        if (!mPendingNotificationUpdate) {
            return;
        }

        mPendingNotificationUpdate = FALSE;
        isConnected = (mDisplayDevice != NULL);
    }

    AutoPtr<IUserHandle> all;
    AutoPtr<IUserHandleHelper> helper;
    CUserHandleHelper::AcquireSingleton((IUserHandleHelper**)&helper);
    helper->GetALL((IUserHandle**)&all);

    // Cancel the old notification if there is one.
    String nullStr;
    mNotificationManager->CancelAsUser(nullStr,
        R::string::wifi_display_notification_title, all);

    if (isConnected) {
        AutoPtr<IContext> context = GetContext();

        AutoPtr<IPendingIntentHelper> piHelper;
        CPendingIntentHelper::AcquireSingleton((IPendingIntentHelper**)&piHelper);

        AutoPtr<IUserHandle> current;
        helper->GetCURRENT((IUserHandle**)&current);

        // Initialize pending intents for the notification outside of the lock because
        // creating a pending intent requires a call into the activity manager.
        if (mSettingsPendingIntent == NULL) {
            AutoPtr<IIntent> settingsIntent;
            CIntent::New(ISettings::ACTION_WIFI_DISPLAY_SETTINGS, (IIntent**)&settingsIntent);
            settingsIntent->SetFlags(IIntent::FLAG_ACTIVITY_NEW_TASK
               | IIntent::FLAG_ACTIVITY_RESET_TASK_IF_NEEDED
               | IIntent::FLAG_ACTIVITY_CLEAR_TOP);
            piHelper->GetActivityAsUser(
               context, 0, settingsIntent, 0, NULL, current,
               (IPendingIntent**)&mSettingsPendingIntent);
        }

        if (mDisconnectPendingIntent == NULL) {
            AutoPtr<IIntent> disconnectIntent;
            CIntent::New(ACTION_DISCONNECT, (IIntent**)&disconnectIntent);
            piHelper->GetBroadcastAsUser(
                context, 0, disconnectIntent, 0, current,
                (IPendingIntent**)&mDisconnectPendingIntent);
        }

        // Post the notification.
        AutoPtr<IResources> r;
        context->GetResources((IResources**)&r);
        AutoPtr<INotification> notification;
        AutoPtr<INotificationBuilder> builder;
        CNotificationBuilder::New(context, (INotificationBuilder**)&builder);
        String str;
        r->GetString(R::string::wifi_display_notification_title, &str);
        AutoPtr<ICharSequence> seq;
        CStringWrapper::New(str, (ICharSequence**)&seq);
        builder->SetContentTitle(seq);
        r->GetString(R::string::wifi_display_notification_message, &str);
        seq = NULL;
        CStringWrapper::New(str, (ICharSequence**)&seq);
        builder->SetContentText(seq);
        builder->SetContentIntent(mSettingsPendingIntent);
        builder->SetSmallIcon(R::drawable::ic_notify_wifidisplay);
        builder->SetOngoing(TRUE);
        r->GetString(R::string::wifi_display_notification_disconnect, &str);
        seq = NULL;
        CStringWrapper::New(str, (ICharSequence**)&seq);
        builder->AddAction(R::drawable::ic_menu_close_clear_cancel,
            seq, mDisconnectPendingIntent);
        builder->Build((INotification**)&notification);
        mNotificationManager->NotifyAsUser(nullStr,
            R::string::wifi_display_notification_title,
            notification, all);
    }
}