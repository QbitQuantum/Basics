void WebcamTask::parseData( QByteArray &data, KStreamSocket *socket )
{
	int headerLength = 0;
	int read = 0;
	YahooWebcamInformation *info = &socketMap[socket];
	if( !info->headerRead )
	{
		headerLength = data[0];	
		kDebug(YAHOO_RAW_DEBUG) << "headerLength " << headerLength;
		if( data.size() < headerLength )
			return;			
		if( headerLength >= 8 )
		{
			kDebug() << data[0] << data[1] << data[2] << data[3] << data[4] << data[5] << data[6] << data[7];
			info->reason = data[1];
			info->dataLength = yahoo_get32(data.data() + 4);
		}
		if( headerLength == 13 )
		{
			kDebug() << data[8] << data[9] << data[10] << data[11] << data[12];
			info->timestamp = yahoo_get32(data.data() + 9);
			kDebug(YAHOO_RAW_DEBUG) << "PacketType: " << data[8] << " reason: " << info->reason << " timestamp: " << info->timestamp;
			QStringList::iterator it;
			switch( data[8] )
			{
				case 0x00:
					if( info->direction == Incoming )
					{
						if( info->timestamp == 0 )
						{
							emit webcamClosed( info->sender, 3 );
							cleanUpConnection( socket );
						}
					}
					else
					{
						info->type = UserRequest;
						info->headerRead = true;
					}
				break;
				case 0x02: 
					info->type = Image;
					info->headerRead = true;
				break;
				case 0x04:
					if( info->timestamp == 1 )
					{
						emit webcamPaused( info->sender );
					}
				break;
				case 0x05:
					kDebug(YAHOO_RAW_DEBUG) << "Ready for Transmission";
					if( info->timestamp == 1 )
					{
						info->status = Sending;
						emit readyForTransmission();
					}
					else if( info->timestamp == 0 )
					{
						info->status = SendingEmpty;
						emit stopTransmission();
						sendEmptyWebcamImage();
					
					}
					// Send  very first Invitation packets
					for(it = pendingInvitations.begin(); it != pendingInvitations.end(); it++)
					{
						kDebug(YAHOO_RAW_DEBUG) << "send primary invitation";
						SendNotifyTask *snt = new SendNotifyTask( parent() );
						snt->setTarget( *it );
						snt->setType( SendNotifyTask::NotifyWebcamInvite );
						snt->go( true );
						it = pendingInvitations.erase( it );
						it--;
						info->status = SendingEmpty;
						emit stopTransmission();
						sendEmptyWebcamImage();
					}
					
					break;
				case 0x07: 
					
					info->type = ConnectionClosed;
					emit webcamClosed( info->sender, info->reason );
					cleanUpConnection( socket );
				case 0x0c:
					info->type = NewWatcher;
					info->headerRead = true;
				break;
				case 0x0d:
					info->type = WatcherLeft;
					info->headerRead = true;
				break;
			}
		}
		if( headerLength > 13 || headerLength <= 0)		//Parse error
			return;
		if( !info->headerRead && data.size() > headerLength )
		{
			// More headers to read
			kDebug(YAHOO_RAW_DEBUG) << "More data to read...";
			QByteArray newData;
			newData.reserve( data.size() - headerLength );
			QDataStream stream( &newData, QIODevice::WriteOnly );
			stream.writeRawData( data.data() + headerLength, data.size() - headerLength );
			parseData( newData, socket );
			return;
		}
		kDebug(YAHOO_RAW_DEBUG) << "Parsed Packet: HeaderLen: " << headerLength << " DataLen: " << info->dataLength;
	}
	
	if( info->dataLength <= 0 )
	{
		kDebug(YAHOO_RAW_DEBUG) << "No data to read. (info->dataLength <= 0)";
		if( info->headerRead )
			info->headerRead = false;
		return;
	}
	if( headerLength >= data.size() )
	{
		kDebug(YAHOO_RAW_DEBUG) << "No data to read. (headerLength >= data.size())";
		return;		//Nothing to read here...
	}
	if( !info->buffer )
	{
		kDebug(YAHOO_RAW_DEBUG) << "Buffer created";
		info->buffer = new QBuffer();
		info->buffer->open( QIODevice::WriteOnly );
	}
	kDebug(YAHOO_RAW_DEBUG) << "data.size() " << data.size() << " headerLength " << headerLength << " buffersize " << info->buffer->size();
	read = headerLength + info->dataLength - info->buffer->size();
	info->buffer->write( data.data() + headerLength, data.size() - headerLength );//info->dataLength - info->buffer->size() );
	kDebug(YAHOO_RAW_DEBUG) << "read " << data.size() - headerLength << " Bytes, Buffer is now " << info->buffer->size();
	if( info->buffer->size() >= static_cast<uint>(info->dataLength) )
	{	
		info->buffer->close();
		QString who;
		switch( info->type )
		{
		case UserRequest:
			{
			who.append( info->buffer->buffer() );
			who = who.mid( 2, who.indexOf('\n') - 3);
			kDebug(YAHOO_RAW_DEBUG) << "User wants to view webcam: " << who << " len: " << who.length() << " Index: " << accessGranted.indexOf( who );
			if( accessGranted.indexOf( who ) >= 0 )
			{
				grantAccess( who );
			}
			else
				emit viewerRequest( who );
			}
		break;
		case NewWatcher:
			who.append( info->buffer->buffer() );
			who = who.left( who.length() - 1 );
			kDebug(YAHOO_RAW_DEBUG) << "New Watcher of webcam: " << who;
			emit viewerJoined( who );
		break;
		case WatcherLeft:
			who.append( info->buffer->buffer() );
			who = who.left( who.length() - 1 );
			kDebug(YAHOO_RAW_DEBUG) << "A Watcher left: " << who << " len: " << who.length();
			accessGranted.removeAll( who );
			emit viewerLeft( who );
		break;
		case Image:
			{
			QPixmap webcamImage;
			//webcamImage.loadFromData( info->buffer->buffer() );
			if (WebcamImgFormat::instance())
			{
				if (WebcamImgFormat::instance()->fromYahoo(webcamImage, info->buffer->buffer().constData(), info->buffer->buffer().size()))
				{
					kDebug(YAHOO_RAW_DEBUG) << "Image Received and converted. Size: " << webcamImage.size();
					emit webcamImageReceived( info->sender, webcamImage );
				} else
					kDebug(YAHOO_RAW_DEBUG) << "Failed to convert incoming Yahoo webcam image";
			} else
				kDebug(YAHOO_RAW_DEBUG) << "Failed to initialize WebcamImgFormat helper";
			}
		break;
		default:
		break;
		}
		
		info->headerRead = false;
		delete info->buffer;
		info->buffer = 0L;
	}
	if( data.size() > read )
	{
		// More headers to read
		kDebug(YAHOO_RAW_DEBUG) << "More data to read..." << data.size() - read;
		QByteArray newData;
		newData.reserve( data.size() - read );
		QDataStream stream( &newData, QIODevice::WriteOnly );
		stream.writeRawData( data.data() + read, data.size() - read );
		parseData( newData, socket );
	}
}