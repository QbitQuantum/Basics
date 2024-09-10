bool DictWidget::handleLeftRightKey(const int checked_id, const int key)
{

    QAbstractButton *button = button_group_.button(checked_id);
    if (button)
    {
        int target_focus_id = getNextFocusButtonId(checked_id);
        if (Qt::Key_Left == key)
        {
            target_focus_id = getPreviousFocusButtonId(checked_id);
        }
        QAbstractButton *next = button_group_.button(target_focus_id);
        if (next)
        {
            next->setFocus();
            changeDescription(target_focus_id);
        }
        return true;
    }
    else
    {
        return false;
    }
}