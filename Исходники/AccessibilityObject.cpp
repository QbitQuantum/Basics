AccessibilityObject* AccessibilityObject::elementAccessibilityHitTest(const IntPoint& point) const
{ 
    // Send the hit test back into the sub-frame if necessary.
    if (isAttachment()) {
        Widget* widget = widgetForAttachmentView();
        // Normalize the point for the widget's bounds.
        if (widget && widget->isFrameView())
            return axObjectCache()->getOrCreate(widget)->accessibilityHitTest(IntPoint(point - widget->frameRect().location()));
    }

    return const_cast<AccessibilityObject*>(this); 
}