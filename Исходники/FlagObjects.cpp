DDWORD FlagObject::ObjectMessageFn(HOBJECT hSender, DDWORD messageID, HMESSAGEREAD hRead)
{
	switch (messageID)
	{
		case MID_TRIGGER:
		{
			// Get the trigger name...

			HSTRING hMsg = g_pServerDE->ReadFromMessageHString(hRead);
			if (hMsg)
			{
				char* sMsg = g_pServerDE->GetStringData(hMsg);
				if (sMsg)
				{
					// Check if we should return to the flag stand...

					if (_mbsicmp((const unsigned char*)sMsg, (const unsigned char*)"return") == 0)
					{
						ReturnToFlagStand();
					}
				}

				g_pServerDE->FreeString(hMsg);
			}

			break;
		}

		default: break;
	}

	return B2BaseClass::ObjectMessageFn(hSender, messageID, hRead);
}