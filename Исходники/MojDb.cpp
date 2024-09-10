MojDb::MojDb()
: m_purgeWindow(PurgeNumDaysDefault),
  m_loadStepSize(LoadStepSizeDefault),
  m_isOpen(false)
{
	MojLogTrace(s_log);

    UErrorCode error;
    uloc_setDefault("en_US", &error);
}