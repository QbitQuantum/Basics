void AudioStreamer::Update()
{
	// this method must run on separate thread!!!

	XAUDIO2_VOICE_STATE state;

	Sound*		s;
	soundlist	canstream;
	int			stream;
	long		readbytes;
	long		totalread;
	long		toread;
	bool		play;

	// must be called in every thread
	CoInitializeEx(0, COINIT_MULTITHREADED);

	while( running )
	{
		// collect sound that need more data
		canstream.clear();

		soundguard.Lock(); // reading 'sound'

		for( soundlist::iterator it = sound.begin(); it != sound.end(); ++it )
		{
			s = (*it);

			if( s->isstream )
			{
				if( (s->readsize < s->totalsize) && (s->freebuffers > 0) )
					canstream.push_back(s);
			}
		}

		soundguard.Unlock();

		// update collected sound
		if( canstream.size() > 0 )
		{
			for( soundlist::iterator it = canstream.begin(); it != canstream.end(); ++it )
			{
				soundguard.Lock(); // watch out for 'Destroy()'

				// might have exited
				if( !running )
					return;

				s = (*it);

				totalread = 0;
				readbytes = 0;
				toread = min(STREAMING_BUFFER_SIZE, s->totalsize - s->readsize);

				// fill a free buffer with data
				do
				{
					readbytes = ov_read(&s->oggfile, s->data[s->currentbuffer] + totalread, toread - totalread, 0, 2, 1, &stream);
					totalread += readbytes;
				}
				while( readbytes > 0 && totalread < toread );

				s->readsize += totalread;
				SND_DEBUG("buffer " << s->currentbuffer << " loaded");

				// pull buffer to queue if possible
				// otherwise the sound is gonna pull it
				s->voice->GetState(&state);

				if( state.BuffersQueued < MAX_BUFFER_COUNT - 1 )
				{
					s->PullBuffer(s->currentbuffer);
					SND_DEBUG("buffer " << s->currentbuffer << " pulled (instantly)");
					
					// lock it so noone can modify s->playing
					s->playguard.Lock();
					{
						s->canplay = true;
						play = (s->playrequest && !s->playing);
					}
					s->playguard.Unlock();

					if( play )
						s->Play();
				}
				
				s->currentbuffer = (s->currentbuffer + 1) % MAX_BUFFER_COUNT;
				--s->freebuffers;

				soundguard.Unlock();
			}
		}
		else
			Sleep(100);
	}

	CoUninitialize();
}