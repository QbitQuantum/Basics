KeyStrokeSequenceCommandActuator::KeyStrokeSequenceCommandActuator(int32 argc,
	char** argv)
	:
	CommandActuator(argc, argv)
{
	for (int s = 1; s < argc; s++) {
		fSequence.Append(argv[s]);
		if (s < argc - 1)
			fSequence.Append(" ");
	}

	// Find any insert-unicode-here sequences and replace them with spaces...
	int32 nextStart;
	while ((nextStart = fSequence.FindFirst("$$")) >= 0) {
		int32 nextEnd = fSequence.FindFirst("$$", nextStart + 2);
		if (nextEnd >= 0) {
			uint32 customKey= 0;
			int32 unicodeVal= 0;
			uint32 customMods = 0;
			BString sub;
			fSequence.CopyInto(sub, nextStart + 2, nextEnd-(nextStart + 2));
			sub.ToLower();

			if ((sub.FindFirst('-') >= 0) || ((sub.Length() > 0)
				&& ((sub.String()[0] < '0') || (sub.String()[0] > '9')))) {

				const char* s = sub.String();
				while (*s == '-') s++;// go past any initial dashes

				bool lastWasDash = true;
				while (*s) {
					if (lastWasDash) {
						if (strncmp(s, "shift",5) == 0)
							customMods |=B_LEFT_SHIFT_KEY| B_SHIFT_KEY;
						else if (strncmp(s, "leftsh", 6) == 0)
							customMods |=B_LEFT_SHIFT_KEY| B_SHIFT_KEY;
						else if (strncmp(s, "rightsh",7) == 0)
							customMods |=B_RIGHT_SHIFT_KEY | B_SHIFT_KEY;
						else if (strncmp(s, "alt",3) == 0)
							customMods |=B_LEFT_COMMAND_KEY| B_COMMAND_KEY;
						else if (strncmp(s, "leftalt",7) == 0)
							customMods |=B_LEFT_COMMAND_KEY| B_COMMAND_KEY;
						else if (strncmp(s, "rightalt", 8) == 0)
							customMods |=B_RIGHT_COMMAND_KEY | B_COMMAND_KEY;
						else if (strncmp(s, "com",3) == 0)
							customMods |=B_LEFT_COMMAND_KEY| B_COMMAND_KEY;
						else if (strncmp(s, "leftcom",7) == 0)
							customMods |=B_LEFT_COMMAND_KEY| B_COMMAND_KEY;
						else if (strncmp(s, "rightcom", 8) == 0)
							customMods |=B_RIGHT_COMMAND_KEY | B_COMMAND_KEY;
						else if (strncmp(s, "con",3) == 0)
							customMods |=B_LEFT_CONTROL_KEY| B_CONTROL_KEY;
						else if (strncmp(s, "leftcon",7) == 0)
							customMods |=B_LEFT_CONTROL_KEY| B_CONTROL_KEY;
						else if (strncmp(s, "rightcon", 8) == 0)
							customMods |=B_RIGHT_CONTROL_KEY | B_CONTROL_KEY;
						else if (strncmp(s, "win",3) == 0)
							customMods |=B_LEFT_OPTION_KEY | B_OPTION_KEY;
						else if (strncmp(s, "leftwin",7) == 0)
							customMods |=B_LEFT_OPTION_KEY | B_OPTION_KEY;
						else if (strncmp(s, "rightwin", 8) == 0)
							customMods |=B_RIGHT_OPTION_KEY| B_OPTION_KEY;
						else if (strncmp(s, "opt",3) == 0)
							customMods |=B_LEFT_OPTION_KEY | B_OPTION_KEY;
						else if (strncmp(s, "leftopt",7) == 0)
							customMods |=B_LEFT_OPTION_KEY | B_OPTION_KEY;
						else if (strncmp(s, "rightopt", 8) == 0)
							customMods |=B_RIGHT_OPTION_KEY| B_OPTION_KEY;
						else if (strncmp(s, "menu", 4) == 0)
							customMods |=B_MENU_KEY;
						else if (strncmp(s, "caps", 4) == 0)
							customMods |=B_CAPS_LOCK;
						else if (strncmp(s, "scroll", 6) == 0)
							customMods |=B_SCROLL_LOCK;
						else if (strncmp(s, "num",3) == 0)
							customMods |=B_NUM_LOCK;
						else if (customKey == 0) {
							BString arg = s;
							int32 dashIdx = arg.FindFirst('-');

							if (dashIdx >= 0)
								arg.Truncate(dashIdx);

							uint32 key = (uint32)FindKeyCode(arg.String());

							if (key > 0) {
								customKey = key;
								const char* u = GetKeyUTF8(key);

								//Parse the UTF8 back into an int32
								switch(strlen(u)) {
									case 1:
										unicodeVal = ((uint32)(u[0]&0x7F));
										break;
									case 2:
										unicodeVal = ((uint32)(u[1]&0x3F)) |
											(((uint32)(u[0]&0x1F)) << 6);
										break;
									case 3:
										unicodeVal = ((uint32)(u[2]&0x3F)) |
											(((uint32)(u[1]&0x3F)) << 6) |
											(((uint32)(u[0]&0x0F)) << 12);
										break;
									default: unicodeVal = 0;
										break;
								}
							}
						}
						lastWasDash = false;
					} else
						lastWasDash = (*s == '-');

					s++;
				}

				// If we have a letter, try to make it the correct case
				if ((unicodeVal >= 'A') && (unicodeVal <= 'Z')) {
					if ((customMods & B_SHIFT_KEY) == 0)
						unicodeVal += 'a'-'A';
				} else if ((unicodeVal >= 'a') && (unicodeVal <= 'z')) {
					if ((customMods & B_SHIFT_KEY) != 0)
						unicodeVal -= 'a'-'A';
				}
			} else {
				unicodeVal = strtol(&(fSequence.String())[nextStart + 2],
					NULL, 0);
				customMods = (uint32) -1;
			}

			if (unicodeVal == 0)
				unicodeVal = ' ';

			BString newString = fSequence;
			newString.Truncate(nextStart);
			fOverrides.AddItem((void*)(addr_t)unicodeVal);
			fOverrideOffsets.AddItem((void*)(addr_t)newString.Length());
			fOverrideModifiers.AddItem((void*)(addr_t)customMods);
			fOverrideKeyCodes.AddItem((void*)(addr_t)customKey);
			newString.Append((unicodeVal > 0
				&& unicodeVal < 127) ? (char)unicodeVal : ' ', 1);
			newString.Append(&fSequence.String()[nextEnd + 2]);
			fSequence = newString;
		} else
			break;
	}

	_GenerateKeyCodes();
}