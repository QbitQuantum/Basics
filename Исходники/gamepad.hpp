		void update() {
			connected = XInputGetState(index, &raw_state) == ERROR_SUCCESS;
		}