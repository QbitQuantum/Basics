void AXObjectCache::postPlatformNotification(AccessibilityObject* obj, AXNotification notification)
{
    if (!obj)
        return;

    Document* document = obj->document();
    if (!document)
        return;

    Page* page = document->page();
    if (!page || !page->chrome().platformPageClient())
        return;

    DWORD msaaEvent;
    switch (notification) {
        case AXCheckedStateChanged:
            msaaEvent = EVENT_OBJECT_STATECHANGE;
            break;

        case AXFocusedUIElementChanged:
        case AXActiveDescendantChanged:
            msaaEvent = EVENT_OBJECT_FOCUS;
            break;

        case AXScrolledToAnchor:
            msaaEvent = EVENT_SYSTEM_SCROLLINGSTART;
            break;

        case AXLayoutComplete:
            msaaEvent = EVENT_OBJECT_REORDER;
            break;

        case AXLoadComplete:
            msaaEvent = IA2_EVENT_DOCUMENT_LOAD_COMPLETE;
            break;

        case AXValueChanged:
        case AXMenuListValueChanged:
            msaaEvent = EVENT_OBJECT_VALUECHANGE;
            break;

        case AXMenuListItemSelected:
            msaaEvent = EVENT_OBJECT_SELECTION;
            break;

        default:
            return;
    }

    // Windows will end up calling get_accChild() on the root accessible
    // object for the WebView, passing the child ID that we specify below. We
    // negate the AXID so we know that the caller is passing the ID of an
    // element, not the index of a child element.

    ASSERT(obj->axObjectID() >= 1);
    ASSERT(obj->axObjectID() <= numeric_limits<LONG>::max());

    NotifyWinEvent(msaaEvent, page->chrome().platformPageClient(), OBJID_CLIENT, -static_cast<LONG>(obj->axObjectID()));
}