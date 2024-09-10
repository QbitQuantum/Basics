		bool getKey(Key key)
		{
			return (GetAsyncKeyState(Imp::WinKey[static_cast<i32>(key)])) != 0;
		}