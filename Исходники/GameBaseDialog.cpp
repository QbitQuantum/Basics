void GameBaseDialog::cancel() {
	onExit();
	this->removeFromParentAndCleanup(true);

	if (m_pCancelCallbackTarget && m_selector) {
		(m_pCancelCallbackTarget->*m_selector)(NULL);
	}
}