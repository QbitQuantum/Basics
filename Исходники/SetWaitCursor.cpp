SetWaitCursor::~SetWaitCursor()
{
    if (m_guiApp) {

        RG_DEBUG << "SetWaitCursor::SetWaitCursor() : restoring normal cursor\n";
        QWidget* viewport = 0;
        QCursor currentCompositionViewCursor;

        if ((m_guiApp->getView() &&
                m_guiApp->getView()->getTrackEditor() &&
                m_guiApp->getView()->getTrackEditor()->getCompositionView() &&
                m_guiApp->getView()->getTrackEditor()->getCompositionView()->viewport())) {
            viewport = m_guiApp->getView()->getTrackEditor()->getCompositionView()->viewport();
            currentCompositionViewCursor = viewport->cursor();
        }

        m_guiApp->setCursor(m_saveCursor);

        if (viewport) {
            if (currentCompositionViewCursor.shape() == Qt::WaitCursor) {
                viewport->setCursor(m_saveCompositionViewCursor);
            } else {
                viewport->setCursor(currentCompositionViewCursor); // because m_guiApp->setCursor() has replaced it
            }
        }

        // otherwise, it's been modified elsewhere, so leave it as is

    }

}