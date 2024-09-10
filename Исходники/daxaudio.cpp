tUInt32 DAXAudio::WriteSound(string host,tUInt32 port,tByte* data,tUInt32 size)
{
	if (!_player)
		return 0;

#ifdef SPEEX_CODE
	tByte frame[BLOCK_SIZE]={0};
	int voicesize = *((tUInt32*)(data));
	int timestamp = *((tUInt32*)(data+4));

	if (timestamp % FRAME_SIZE != 0)
	{
		LOGWARNING("DAXAudio::WriteSound:Currupted data with timestamp "<<timestamp<<" from "<<host<<"::"<<port<<",abandon the data!");
		return 0;
	}

	if (voicesize!=size-8)
	{
		LOGWARNING("DAXAudio::WriteSound:Currupted data from "<<host<<" for "<<voicesize<<"!="<<size<<"-8,abandon the data!");
		return 0;
	}

#ifdef USING_JITTER
	// find the right jitter and stored the data into
	// check if player can playmore,if yes, get a frame from all jitters and merge them
	// write the merged data into player.
	tByte from[100]={0};
	sprintf_s((char*)from,100,"%s::%u",host.c_str(),port);
	tFromJitterMapIter iter = _from_jitter_map.find(from);

	if (iter==_from_jitter_map.end())
	{
		LOGWARNING("DAXAudio::WriteSound:From "<<from<<" is not registered,abandon the data!");
		return 0;
	}

	speex_jitter_put(iter->second,(char*)(data+8),size-8,timestamp);

	if (_player->ReadyForPlayMore())
	{
		GetMergedFramFromJitters(frame,BLOCK_SIZE);
		_player->WriteSound(frame,BLOCK_SIZE);
		return size;
	}
	else
	{
		LOGWARNING("DAXAudio::WriteSound:Player is busy,wait a momment...");
		return 0;
	}
#else	
	if (_converter->Decode(data+8,size-8,frame,BLOCK_SIZE))
		if(_player->WriteSound(frame,BLOCK_SIZE))
			return size;
	return 0;
#endif	//USING_JITTER

#else
	// just for test, of course coded and sent.
	//if (_player->ReadyForPlayMore())
		return _player->WriteSound(data,size);
	//else
	//	return 0;
#endif	//SPEEX_CODE
}