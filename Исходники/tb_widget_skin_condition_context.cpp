bool TBWidgetSkinConditionContext::GetCondition(TBSkinCondition::TARGET target, const TBSkinCondition::CONDITION_INFO &info)
{
	switch (target)
	{
	case TBSkinCondition::TARGET_THIS:
		return GetCondition(m_widget, info);
	case TBSkinCondition::TARGET_PARENT:
		return m_widget->GetParent() && GetCondition(m_widget->GetParent(), info);
	case TBSkinCondition::TARGET_ANCESTORS:
		{
			TBWidget *widget = m_widget->GetParent();
			while (widget)
			{
				if (GetCondition(widget, info))
					return true;
				widget = widget->GetParent();
			}
		}
	case TBSkinCondition::TARGET_PREV_SIBLING:
		return m_widget->GetPrev() && GetCondition(m_widget->GetPrev(), info);
	case TBSkinCondition::TARGET_NEXT_SIBLING:
		return m_widget->GetNext() && GetCondition(m_widget->GetNext(), info);
	}
	return false;
}