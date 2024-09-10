void NotifyCaretPositionChanged(_In_ HWND hwnd, _In_ AnnotatedTextControl *control)
{
    TextAreaProvider *eventControl = new TextAreaProvider(hwnd, control);
    if (eventControl == NULL)
    {
        // This is an error, but there's not good place to report it in this sample,
        // so just proceed
    }
    else
    {
        UiaRaiseAutomationEvent(eventControl, UIA_Text_TextSelectionChangedEventId);
        eventControl->Release();
    }
}