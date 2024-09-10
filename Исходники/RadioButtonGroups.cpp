void RadioButtonGroup::remove(HTMLInputElement* button)
{
    ASSERT(button->isRadioButton());
    HashSet<HTMLInputElement*>::iterator it = m_members.find(button);
    if (it == m_members.end())
        return;

    bool wasValid = isValid();
    m_members.remove(it);
    if (button->isRequired()) {
        ASSERT(m_requiredCount);
        --m_requiredCount;
    }
    if (m_checkedButton) {
        button->setNeedsStyleRecalc();
        if (m_checkedButton == button) {
            m_checkedButton = nullptr;
            setNeedsStyleRecalcForAllButtons();
        }
    }

    if (m_members.isEmpty()) {
        ASSERT(!m_requiredCount);
        ASSERT(!m_checkedButton);
    } else if (wasValid != isValid())
        updateValidityForAllButtons();
    if (!wasValid) {
        // A radio button not in a group is always valid. We need to make it
        // valid only if the group was invalid.
        button->updateValidity();
    }
}