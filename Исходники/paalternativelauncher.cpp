void PAAlternativeLauncher::manifestReadyRead()
{
	QNetworkReply *reply = dynamic_cast<QNetworkReply *>(sender());
	if(reply)
	{
		if(reply->error() == QNetworkReply::NoError)
		{
			qint64 bytes_available = reply->bytesAvailable();
			QByteArray input = reply->read(bytes_available);
			Q_ASSERT(input.size() == bytes_available);
			mZstream.next_in = (Bytef *)input.constData();
			mZstream.avail_in = bytes_available;

			uInt old_avail_out = mZstream.avail_out;
			int res = inflate(&mZstream, Z_SYNC_FLUSH);
			if(res != Z_OK && res != Z_STREAM_END)
			{
				reply->abort();
				info.warning("ZLib", mZstream.msg, false);
				return;
			}

			mManifestJson.write((const char *)mBuffer, old_avail_out - mZstream.avail_out);
			mZstream.avail_out = mBufferSize;
			mZstream.next_out = mBuffer;
			Q_ASSERT(mZstream.avail_in == 0);
		}
		else
		{
			reply->abort();
			info.critical(tr("Manifest"), tr("Error while getting manifest (1).\n%1").arg(reply->errorString()));
		}
	}
}