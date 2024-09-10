void UIWidget::insertChild(int index, const UIWidgetPtr& child)
{
    if(!child) {
        g_logger.traceWarning("attempt to insert a null child into a UIWidget");
        return;
    }

    if(hasChild(child)) {
        g_logger.traceWarning("attempt to insert a child again into a UIWidget");
        return;
    }

    index = index <= 0 ? (m_children.size() + index) : index-1;

    if(!(index >= 0 && (uint)index <= m_children.size())) {
        //g_logger.traceWarning("attempt to insert a child UIWidget into an invalid index, using nearest index...");
        index = std::min(std::max(index, 0),  (int)m_children.size());
    }

    // retrieve child by index
    auto it = m_children.begin() + index;
    m_children.insert(it, child);
    child->setParent(static_self_cast<UIWidget>());

    // create default layout if needed
    if(!m_layout)
        m_layout = UIAnchorLayoutPtr(new UIAnchorLayout(static_self_cast<UIWidget>()));

    // add to layout and updates it
    m_layout->addWidget(child);

    // update new child states
    child->updateStates();
    updateChildrenIndexStates();

    g_ui.onWidgetAppear(child);
}