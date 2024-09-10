void HbAnchorArrowDrawer::changeEvent(QEvent *event)
{
#if defined(HB_DEVELOPER) || defined(CSS_INSPECTOR)
    if (event->type() == HbEvent::ThemeChanged)
        updateColors();
#endif
    HbWidgetBase::changeEvent(event);
}