void TwoStatePreference::SendAccessibilityEvent(
    /* [in] */ IView* view)
{
    // Since the view is still not attached we create, populate,
    // and send the event directly since we do not know when it
    // will be attached and posting commands is not as clean.
    AutoPtr<IContext> ctx;
    GetContext((IContext**)&ctx);
    AutoPtr<IAccessibilityManagerHelper> managerHelper;
    CAccessibilityManagerHelper::AcquireSingleton((IAccessibilityManagerHelper**)&managerHelper);
    AutoPtr<IAccessibilityManager> accessibilityManager;
    managerHelper->GetInstance(ctx, (IAccessibilityManager**)&accessibilityManager);
    Boolean enabled;
    if (mSendClickAccessibilityEvent && (accessibilityManager->IsEnabled(&enabled), enabled)) {
        AutoPtr<IAccessibilityEventHelper> helper;
        CAccessibilityEventHelper::AcquireSingleton((IAccessibilityEventHelper**)&helper);
        AutoPtr<IAccessibilityEvent> event;
        helper->Obtain((IAccessibilityEvent**)&event);
        event->SetEventType(IAccessibilityEvent::TYPE_VIEW_CLICKED);
        view->OnInitializeAccessibilityEvent(event);
        Boolean isConsumed;
        view->DispatchPopulateAccessibilityEvent(event, &isConsumed);
        accessibilityManager->SendAccessibilityEvent(event);
    }

    mSendClickAccessibilityEvent = FALSE;
}