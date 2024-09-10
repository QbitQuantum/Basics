	void Plugin::UploadTo (LIBMTP_mtpdevice_t *device, const QByteArray& storageId,
			const QString& localPath, const QString& origPath)
	{
		if (!device->storage)
			LIBMTP_Get_Storage (device, 0);

		auto storage = device->storage;

		while (storage)
		{
			qDebug () << "st" << storage->id;
			if (QByteArray::number (storage->id) == storageId)
				break;
			storage = storage->next;
		}

		if (!storage)
		{
			qWarning () << Q_FUNC_INFO
					<< "could not find storage"
					<< storageId;
			emit uploadFinished (localPath,
					QFile::ResourceError,
					tr ("Unable to find the requested storage."));
			return;
		}

		const auto id = storage->id;
		const auto& info = OrigInfos_.take (origPath);

		qDebug () << "uploading" << localPath << "of type" << GetFileType (info.FileFormat_) << "to" << storage->id;

		auto track = LIBMTP_new_track_t ();
		track->storage_id = id;

		auto getStr = [] (const QString& str) { return strdup (str.toUtf8 ().constData ()); };

		track->filename = getStr (QFileInfo (localPath).fileName ());
		track->album = getStr (info.Album_);
		track->title = getStr (info.TrackTitle_);
		track->genre = getStr (info.Genres_.join ("; "));
		track->artist = getStr (info.Artist_);
		track->tracknumber = info.TrackNumber_;
		track->filetype = GetFileType (info.FileFormat_);
		track->filesize = QFileInfo (localPath).size ();
		track->date = getStr (QString::number (info.AlbumYear_) + "0101T0000.0");

		auto watcher = new QFutureWatcher<UploadInfo> ();
		connect (watcher,
				SIGNAL (finished ()),
				this,
				SLOT (handleUploadFinished ()));
		const auto future = QtConcurrent::run ([=] () -> UploadInfo
			{
				const auto cbData = new CallbackData { this, 0 };
				const auto res = LIBMTP_Send_Track_From_File (device,
						localPath.toUtf8 ().constData (), track,
						TransferCallback, cbData);
				delete cbData;
				return { res, device, localPath, track, info };
			});
		watcher->setFuture (future);
	}