int CPCSCMngr::CloseSession() {
    int     status = STAT_OK;

    // CLOSE ACTUAL SESION
   if (m_hCard) {
    	SCardDisconnect(m_hCard, SCARD_LEAVE_CARD);
        m_hCard = NULL;
    }
    if (m_cardContext) {
    	SCardReleaseContext(m_cardContext);
        m_cardContext = NULL;
    }
    return status;
}