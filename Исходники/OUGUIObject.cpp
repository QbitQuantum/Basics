void OUGUIObject::SetMouseLButton(bool bDown)
{
    if(bDown == m_bMouseLButton) return;

    m_bMouseLButton = bDown;

    if(m_bMouseLButton)
    {
        /** 设置控件 */
        if(!IsChild(OUGUIObject::GetFocusControl()))
        {
            OUGUIObject::SetFocusControl(this);
        }

        /** 激活控件 (如拖曳) */
        if(!IsChild(OUGUIObject::GetActiveControl()))
        {
            OUGUIObject::SetActiveControl(this);
        }

        OnMouseLButtonDown();
    }
    else
    {
        if(OUGUIObject::GetActiveControl() == this)
        {
            OUGUIObject::SetActiveControl(NULL);
        }

        OnMouseLButtonUp();
    }
}