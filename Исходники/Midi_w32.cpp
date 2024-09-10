		bool _reset(uint _deviceID) 
		{
			MMRESULT res;
			if ( ! _midiIn ) return 0;
			res = midiInStop( _midiIn );
			if ( res ) return _error( res );   
			res = midiInReset( _midiIn );
			if ( res ) return _error( res );   
			res = midiInStart( _midiIn );
			return  _error( res );   
		}