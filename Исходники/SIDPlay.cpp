bool SIDPlay::open(const QString &_url, bool tracksOnly)
{
	QString prefix, url, param;
	const bool hasPluginPrefix = Functions::splitPrefixAndUrlIfHasPluginPrefix(_url, &prefix, &url, &param);

	if (tracksOnly == hasPluginPrefix)
		return false;

	int track = 0;
	if (!hasPluginPrefix)
	{
		if (url.startsWith(SIDPlayName "://"))
			return false;
		url = _url;
	}
	else
	{
		if (prefix != SIDPlayName)
			return false;
		bool ok;
		track = param.toInt(&ok);
		if (track < 0 || !ok)
			return false;
	}

	if (Reader::create(url, m_reader))
	{
		const QByteArray data = m_reader->read(m_reader->size());
		m_reader.clear();

		m_tune = new SidTune((const quint8 *)data.data(), data.length());
		if (!m_tune->getStatus())
			return false;

		if (!hasPluginPrefix)
		{
			m_aborted = true;
			m_url = url;
			return true;
		}

		const SidTuneInfo *info = m_tune->getInfo();

		if (track >= (int)info->songs())
			return false;

		m_rs.create(m_sidplay.info().maxsids());
		if (!m_rs.getStatus())
			return false;
		m_rs.filter(true);

#if ((LIBSIDPLAYFP_VERSION_MAJ << 16 | LIBSIDPLAYFP_VERSION_MIN << 8 | LIBSIDPLAYFP_VERSION_LEV) > 0x010800)
		const bool isStereo = info->sidChips() > 1 ? true : false;
#else
		const bool isStereo = info->isStereo();
#endif

		SidConfig cfg;
		cfg.frequency = m_srate;
		cfg.sidEmulation = &m_rs;
		if (isStereo)
			cfg.playback = SidConfig::STEREO;
		cfg.samplingMethod = SidConfig::INTERPOLATE;
		if (!m_sidplay.config(cfg))
			return false;

		m_tune->selectSong(track + 1);

		m_title = getTitle(info, track);
		m_chn = isStereo ? 2 : 1;

		const QString title    = info->infoString(0);
		const QString author   = info->infoString(1);
		const QString released = info->infoString(2);
		if (!title.isEmpty())
			m_tags << qMakePair(QString::number(QMPLAY2_TAG_TITLE), title);
		if (!author.isEmpty())
			m_tags << qMakePair(QString::number(QMPLAY2_TAG_ARTIST), author);
		if (!released.isEmpty())
			m_tags << qMakePair(QString::number(QMPLAY2_TAG_DATE), released);
		m_tags << qMakePair(tr("Track"), QString::number(track + 1));

		streams_info += new StreamInfo(m_srate, m_chn);

		return m_sidplay.load(m_tune);
	}

	return false;
}