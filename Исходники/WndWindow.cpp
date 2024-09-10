CWndControl* CWndWindow::GetEditableControl(const QPoint& mousePos)
{
	const QPoint clientMousePos = mousePos - GetClientRect(false).topLeft();
	CWndControl* ctrl = null;
	bool exists = false;
	for (int i = m_controls.GetSize() - 1; i >= 0; i--)
	{
		ctrl = m_controls[i];
		exists = false;
		for (int j = 0; j < m_data->controls.GetSize(); j++)
		{
			if (m_data->controls[j]->ID == ctrl->GetID())
			{
				exists = true;
				break;
			}
		}
		if (!exists)
			continue;

		if (ctrl->GetType() == WTYPE_STATIC && ctrl->HasFlag(BS_GROUPBOX))
		{
			QRect rect = ctrl->GetWindowRect(true);
			if (ctrl->HasFlag(WBS_DOCKING))
			{
				if (rect.contains(mousePos))
				{
					rect.adjust(4, 16, -8, -10);
					if (!rect.contains(mousePos))
						return ctrl;
				}
			}
			else
			{
				if (rect.contains(clientMousePos))
				{
					rect.adjust(4, 16, -8, -10);
					if (!rect.contains(clientMousePos))
						return ctrl;
				}
			}
		}
		else
		{
			if (ctrl->HasFlag(WBS_DOCKING))
			{
				if (ctrl->GetWindowRect(true).contains(mousePos))
					return ctrl;
			}
			else
			{
				if (ctrl->GetWindowRect(true).contains(clientMousePos))
					return ctrl;
			}
		}
	}
	return this;
}