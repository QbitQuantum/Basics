		// Returns whether the specified key is NOT pressed
		bool KeyboardState::IsKeyUp(Keys_t key)
		{
			if(XInputGetKeystroke(&Stroke) == 0)
			{
				if((Stroke.ucFlags & (byte)key) != 0)
				{
					return true;
				}

				return false;
			}

			// The keyboard was not connected...bail out.
			return -1;
		}