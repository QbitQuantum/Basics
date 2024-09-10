void CCWidget::setLongClickTouchHandlerWidget(CCNode* pWidget)
{
	for(CCNode* pNode = m_pWidgetNode; pNode != NULL; pNode = pNode->getParent())
	{
		CCWidgetLayout* pWidgetLayoutParent = dynamic_cast<CCWidgetLayout*>(pNode);
		if( pWidgetLayoutParent )
		{
			pWidgetLayoutParent->setLongClickTouchHandlerWidget(pWidget);
			return;
		}
	}
}