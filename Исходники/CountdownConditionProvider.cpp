ECode CountdownConditionProvider::OnSubscribe(
    /* [in] */ IUri* conditionId)
{
    if (DEBUG) Slogger::D(TAG, "onSubscribe %p", conditionId);
    AutoPtr<IZenModeConfigHelper> helper;
    CZenModeConfigHelper::AcquireSingleton((IZenModeConfigHelper**)&helper);
    helper->TryParseCountdownConditionId(conditionId, &mTime);

    AutoPtr<IInterface> obj;
    mContext->GetSystemService(IContext::ALARM_SERVICE, (IInterface**)&obj);
    AutoPtr<IAlarmManager> alarms = IAlarmManager::Probe(obj);
    String str;
    IObject::Probe(conditionId)->ToString(&str);
    AutoPtr<IIntent> intent;
    CIntent::New(ACTION, (IIntent**)&intent);
    intent->PutExtra(EXTRA_CONDITION_ID, str);
    intent->SetFlags(IIntent::FLAG_RECEIVER_REGISTERED_ONLY);

    AutoPtr<IPendingIntentHelper> pendingIntentHelper;
    CPendingIntentHelper::AcquireSingleton((IPendingIntentHelper**)&pendingIntentHelper);
    AutoPtr<IPendingIntent> pendingIntent;
    pendingIntentHelper->GetBroadcast(mContext, REQUEST_CODE,
            intent, IPendingIntent::FLAG_UPDATE_CURRENT, (IPendingIntent**)&pendingIntent);
    alarms->Cancel(pendingIntent);
    if (mTime > 0) {
        AutoPtr<ISystem> sys;
        CSystem::AcquireSingleton((ISystem**)&sys);
        Int64 now;
        sys->GetCurrentTimeMillis(&now);

        AutoPtr<ICharSequence> span =
                DateUtils::GetRelativeTimeSpanString(mTime, now, IDateUtils::MINUTE_IN_MILLIS);
        if (mTime <= now) {
            // in the past, already false
            NotifyCondition(NewCondition(mTime, ICondition::STATE_FALSE));
        }
        else {
            // in the future, set an alarm
            alarms->SetExact(IAlarmManager::RTC_WAKEUP, mTime, pendingIntent);
        }

        String spanStr;
        span->ToString(&spanStr);

        str = "";
        str.AppendFormat("%s %s for %s, %s in the future (%s), now=%s",
                (mTime <= now ? "Not scheduling" : "Scheduling"),
                ACTION.string(),
                Ts(mTime).string(),
                StringUtils::ToString(mTime - now).string(),
                spanStr.string(),
                Ts(now).string());
        if (DEBUG) Slogger::D(TAG, str);
    }
    return NOERROR;
}