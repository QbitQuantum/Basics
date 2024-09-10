/** 
 \param pWidget - The widget to add.
*/
void LinearLayout::addWidget(std::shared_ptr<Widget> pWidget){
	CAP_THROW_NULL(pWidget, "The widget is null");
	m_widgets.push_back(pWidget);

	pWidget->setParent(this);
	pWidget->setWindowId(this->m_windowId);

	m_updateChildren = true;
}