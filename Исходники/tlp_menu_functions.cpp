volatile char btConnect(char key, char first)
{
	static uint8_t sfirst = 1;
	uint8_t i;
	static uint8_t menuSize;
	static uint8_t menuSelected;
	uint8_t c;
	uint8_t update, menuScroll;
	update = 0;

	if(sfirst)
	{
		menuScroll = 0;
		menuSelected = 0;
		sfirst = 0;

		update = 1;
		if(bt.state != BT_ST_CONNECTED)
		{
			bt.advertise();
			bt.scan();
		}
	}

	switch(key)
	{
		case LEFT_KEY:
		case FL_KEY:
			sfirst = 1;
			if(bt.state != BT_ST_CONNECTED) bt.sleep();
			return FN_CANCEL;

		case FR_KEY:
			if(bt.state == BT_ST_CONNECTED)
			{
				bt.disconnect();
			}
			else
			{
				bt.connect(bt.device[menuSelected].addr);
			}
			break;
	}

	update = 1;
	switch(bt.event)
	{
		case BT_EVENT_DISCOVERY:
			debug(STR("dicovery!\r\n"));
			break;
		case BT_EVENT_SCAN_COMPLETE:
			debug(STR("done!\r\n"));
			if(bt.state != BT_ST_CONNECTED) bt.scan();
			break;
		case BT_EVENT_DISCONNECT:		
			bt.scan();
			break;
		default:
			update = 0;
	}

	bt.event = BT_EVENT_NULL; // clear event so we don't process it twice

	if(first)
	{
		update = 1;
	}

	if(key == UP_KEY && menuSelected > 0)
	{
		menuSelected--;
		update = 1;
	}
	else if(key == DOWN_KEY && menuSelected < menuSize - 1)
	{
		menuSelected++;
		update = 1;
	}

	if(update)
	{
		lcd.cls();

		if(bt.state == BT_ST_CONNECTED)
		{
			menu.setTitle(TEXT("Connect"));
			lcd.writeStringTiny(18, 20, TEXT("Connected!"));
			menu.setBar(TEXT("RETURN"), TEXT("DISCONNECT"));
		}
		else
		{
			if(menuSelected > 2)
				menuScroll = menuSelected - 2;

			menuSize = 0;

			for(i = 0; i < bt.devices; i++)
			{
				if(i >= menuScroll && i <= menuScroll + 4)
				{
					for(c = 0; c < MENU_NAME_LEN - 1; c++) // Write settings item text //
					{
							if(bt.device[i].name[c])
								lcd.writeChar(3 + c * 6, 8 + 9 * (menuSize - menuScroll), bt.device[i].name[c]);
					}
				}
				menuSize++;
			}

			if(bt.devices)
			{
				lcd.drawHighlight(2, 7 + 9 * (menuSelected - menuScroll), 81, 7 + 9 * (menuSelected - menuScroll) + 8);
				menu.setBar(TEXT("RETURN"), TEXT("CONNECT"));
			}
			else
			{
				lcd.writeStringTiny(6, 20, TEXT("No Devices Found"));
				menu.setBar(TEXT("RETURN"), BLANK_STR);
			}

			menu.setTitle(TEXT("Connect"));

			lcd.drawLine(0, 3, 0, 40);
			lcd.drawLine(83, 3, 83, 40);
		}

		lcd.update();
	}

	return FN_CONTINUE;
}