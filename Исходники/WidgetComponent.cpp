void WidgetComponent::cleanup(Window& parent) const
{
    if (!parent.isChild(getWidgetName()))
        return;

    Window* widget = parent.getChild(getWidgetName());
    // clean up up the event actions
    for (EventActionList::const_iterator i = d_eventActions.begin();
            i != d_eventActions.end();
            ++i)
    {
        (*i).cleanupWidget(*widget);
    }

    parent.destroyChild(widget);
}