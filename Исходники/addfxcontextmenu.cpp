void AddFxContextMenu::onAddFx(QAction *action)
{
	if (action->isCheckable() && action->isChecked())
		action->setChecked(false);

	TFx *fx = createFx(action, m_app->getCurrentXsheet());
	if (fx) {
		QList<TFxP> fxs = m_selection->getFxs();
		// try to add node at cursor position
		if (m_currentCursorScenePos.x() != 0 || m_currentCursorScenePos.y() != 0) {
			fx->getAttributes()->setDagNodePos(TPointD(m_currentCursorScenePos.x(), m_currentCursorScenePos.y()));
			m_currentCursorScenePos.setX(0);
			m_currentCursorScenePos.setY(0);
		}

		TFxCommand::addFx(fx, fxs, m_app,
						  m_app->getCurrentColumn()->getColumnIndex(), m_app->getCurrentFrame()->getFrameIndex());

		m_app->getCurrentXsheet()->notifyXsheetChanged();
		//memorize the latest operation
		m_app->getCurrentFx()->setPreviousActionString(QString("A ") + action->data().toString());
	}
}