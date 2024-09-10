bool QHangulPlatformInputContext::filterEvent(const QEvent *event) {
    if (event->type() != QEvent::KeyPress)
	return false;

    const QKeyEvent *keyevent = static_cast<const QKeyEvent*>(event);
    if (m_candidateList != NULL && m_candidateList->isVisible()) {
	if (m_candidateList->filterEvent(keyevent)) {
	    if (m_candidateList->isSelected()) {
		hangul_ic_reset(m_hic);
		QString candidate(m_candidateList->getCandidate());
		commitText(candidate);
	    }
	    m_candidateList->close();
	}
	return true;
    }

    if (keyevent->key() == Qt::Key_Shift)
	return false;

    if (keyevent->key() == Qt::Key_Backspace)
	return backspace();

    if (isTriggerKey(keyevent)) {
	if (m_mode == MODE_DIRECT) {
	    m_mode = MODE_HANGUL;
	} else {
	    reset();
	    m_mode = MODE_DIRECT;
	}
	setModeInfo(m_mode);

	return true;
    }

    if (isCandidateKey(keyevent)) {
	return popupCandidateList();
    }

    if (keyevent->modifiers() & Qt::ControlModifier ||
	keyevent->modifiers() & Qt::AltModifier ||
	keyevent->modifiers() & Qt::MetaModifier) {
	reset();
	return false;
    }

    if (m_mode == MODE_HANGUL) {
	QString text = keyevent->text();
	if (keyevent->modifiers() & Qt::ShiftModifier)
	    text = text.toUpper();
	else
	    text = text.toLower();

	int ascii = 0;
	if (!text.isEmpty())
	    ascii = text[0].unicode();
	bool ret = hangul_ic_process(m_hic, ascii);

	QString commitString = getCommitString();
	if (!commitString.isEmpty())
	    commitText(commitString);

	QString preeditString = getPreeditString();
	if (!preeditString.isEmpty())
	    updatePreedit(preeditString);

	return ret;
    }

    return false;
}