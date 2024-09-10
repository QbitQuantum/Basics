static void UpdateController(void)
{
	struct control_cache_t *cache;
	ioport_constructor last_ipt = NULL;
	BOOL flags[CONTROLLER_MAX];
	int nGames = GetNumGames();
	int b = 0;
	int p = 0;
	int i;

	cache = (control_cache_t *)malloc(sizeof (*cache) * nGames);
	if (cache == NULL)
		return;

	for (i = 0; i < nGames; i++)
	{
		cache[i].ipt = driver_list::driver(i).ipt;
		cache[i].num = i;
	}
	qsort(cache, nGames, sizeof (*cache), cmp_ipt);

	for (i = 0; i < nGames; i++)
	{
		struct DriversInfo *gameinfo = &drivers_info[cache[i].num];

		if (!cache[i].ipt)
			continue;

		if (cache[i].ipt != last_ipt)
		{
			const input_port_config *port;
			ioport_list portlist;
			astring errors;

			int w = CONTROLLER_JOY8WAY;
			BOOL lr = FALSE;
			BOOL ud = FALSE;
			BOOL dual = FALSE;

			last_ipt = cache[i].ipt;
			memset(flags, 0, sizeof flags);
			b = 0;
			p = 0;

			machine_config config(driver_list::driver(i), MameUIGlobal());
			device_iterator iter(config.root_device());
			for (device_t *device = iter.first(); device != NULL; device = iter.next())
				if (device->input_ports()!=NULL)
					input_port_list_init(*device, portlist, errors);

			for (port = portlist.first(); port != NULL; port = port->next())
			{
				const input_field_config *field;
				for (field = port->first_field(); field != NULL; field = field->next())
				{
				    int n;

				    if (p < field->player + 1)
					    p = field->player + 1;

				    n = field->type - IPT_BUTTON1 + 1;
				    if (n >= 1 && n <= MAX_NORMAL_BUTTONS && n > b)
				    {
					    b = n;
					    continue;
				    }

				    switch (field->type)
				    {
				    case IPT_JOYSTICKRIGHT_LEFT:
				    case IPT_JOYSTICKRIGHT_RIGHT:
				    case IPT_JOYSTICKLEFT_LEFT:
				    case IPT_JOYSTICKLEFT_RIGHT:
					    dual = TRUE;

				    case IPT_JOYSTICK_LEFT:
				    case IPT_JOYSTICK_RIGHT:
					    lr = TRUE;

					    if (field->way == 4)
						    w = CONTROLLER_JOY4WAY;
					    else if (field->way == 16)
						    w = CONTROLLER_JOY16WAY;
					    break;

				    case IPT_JOYSTICKRIGHT_UP:
				    case IPT_JOYSTICKRIGHT_DOWN:
				    case IPT_JOYSTICKLEFT_UP:
				    case IPT_JOYSTICKLEFT_DOWN:
					    dual = TRUE;

				    case IPT_JOYSTICK_UP:
				    case IPT_JOYSTICK_DOWN:
					    ud = TRUE;

					    if (field->way == 4)
						    w = CONTROLLER_JOY4WAY;
					    else if (field->way == 16)
						    w = CONTROLLER_JOY16WAY;
					    break;

				    case IPT_PADDLE:
					    flags[CONTROLLER_PADDLE] = TRUE;
					    break;

				    case IPT_DIAL:
					    flags[CONTROLLER_DIAL] = TRUE;
					    break;

				    case IPT_TRACKBALL_X:
				    case IPT_TRACKBALL_Y:
					    flags[CONTROLLER_TRACKBALL] = TRUE;
					    break;

				    case IPT_AD_STICK_X:
				    case IPT_AD_STICK_Y:
					    flags[CONTROLLER_ADSTICK] = TRUE;
					    break;

				    case IPT_LIGHTGUN_X:
				    case IPT_LIGHTGUN_Y:
					    flags[CONTROLLER_LIGHTGUN] = TRUE;
					    break;
				    case IPT_PEDAL:
					    flags[CONTROLLER_PEDAL] = TRUE;
					    break;
				    }
				}
			}
			//input_port_list_deinit(&portlist);

			if (lr || ud)
			{
				if (lr && !ud)
					w = CONTROLLER_JOY2WAY;
				else if (!lr && ud)
					w = CONTROLLER_VJOY2WAY;

				if (dual)
					w += CONTROLLER_DOUBLEJOY2WAY - CONTROLLER_JOY2WAY;

				flags[w] = TRUE;
			}
		}

		gameinfo->numPlayers = p;
		gameinfo->numButtons = b;

		memcpy(gameinfo->usesController, flags, sizeof gameinfo->usesController);
	}

	free(cache);
}