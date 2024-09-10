		void Stop()
		{
			if (handle)
			{
				// stop midi input
				stopping = true;
				midiInStop(handle);
			}
		}