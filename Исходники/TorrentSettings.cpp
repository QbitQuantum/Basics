void TorrentSettings::cleanup()
{
	int removed = 0;
	
	QDir dir = QDir::home();
	QStringList files, hashes, toremove;
	std::vector<libtorrent::torrent_handle> torrents;
	
	torrents = TorrentDownload::m_session->get_torrents();
	
	for(size_t i=0;i<torrents.size();i++)
	{
		const libtorrent::big_number& bn = torrents[i].info_hash();
		hashes << QByteArray((char*) bn.begin(), 20).toHex();
	}
	
	if(dir.cd(TORRENT_FILE_STORAGE))
		files = dir.entryList(QStringList("*.torrent"));
	
	foreach(QString file, files)
	{
		int pt, pos = file.lastIndexOf(" - ");
		if(pos < 0)
			continue;
		pt = file.lastIndexOf('.');
		if(pt < 0)
			continue; // shouldn't happen
		
		if(!hashes.contains(file.mid(pos+3, pt-pos-3)))
		{
			dir.remove(file);
			removed++;
		}
	}