/*! \reimp */
QAccessible::State QAccessibleWidget::state() const
{
    QAccessible::State state;

    QWidget *w = widget();
    if (w->testAttribute(Qt::WA_WState_Visible) == false)
        state.invisible = true;
    if (w->focusPolicy() != Qt::NoFocus)
        state.focusable = true;
    if (w->hasFocus())
        state.focused = true;
    if (!w->isEnabled())
        state.disabled = true;
    if (w->isWindow()) {
        if (w->windowFlags() & Qt::WindowSystemMenuHint)
            state.movable = true;
        if (w->minimumSize() != w->maximumSize())
            state.sizeable = true;
        if (w->isActiveWindow())
            state.active = true;
    }

    return state;
}