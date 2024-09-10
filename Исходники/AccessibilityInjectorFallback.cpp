/**
 * Sends an {@link AccessibilityEvent}.
 *
 * @param event The event to send.
 */
void AccessibilityInjectorFallback::SendAccessibilityEvent(
    /* [in] */ IAccessibilityEvent* event)
{
//    if (DEBUG) {
//        Log.d(LOG_TAG, "Dispatching: " + event);
//    }
    // accessibility may be disabled while waiting for the selection string
    AutoPtr<IAccessibilityManagerHelper> accessibilityManagerHelper;
    AutoPtr<IAccessibilityManager> accessibilityManager;
    AutoPtr<IContext> context;

    CAccessibilityManagerHelper::AcquireSingleton((IAccessibilityManagerHelper**)&accessibilityManagerHelper);
    context = mWebView->GetContext();
    accessibilityManagerHelper->GetInstance(context, (IAccessibilityManager**)&accessibilityManager);
    Boolean enable = FALSE;
    if (accessibilityManager->IsEnabled(&enable), enable) {
        accessibilityManager->SendAccessibilityEvent(event);
    }
}