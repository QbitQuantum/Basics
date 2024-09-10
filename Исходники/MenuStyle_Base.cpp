void BaseMenuStyle::ClientPressedKey(int client, unsigned int key_press)
{
#if defined MENU_DEBUG
	g_Logger.LogMessage("[SM_MENU] ClientPressedKey() (client %d) (key_press %d)", client, key_press);
#endif
	CBaseMenuPlayer *player = GetMenuPlayer(client);

	/* First question: Are we in a menu? */
	if (!player->bInMenu)
	{
		return;
	}

	bool cancel = false;
	unsigned int item = 0;
	MenuCancelReason reason = MenuCancel_Exit;
	MenuEndReason end_reason = MenuEnd_Selected;
	menu_states_t &states = player->states;

	/* Save variables */
	IMenuHandler *mh = states.mh;
	IBaseMenu *menu = states.menu;

	unsigned int item_on_page = states.item_on_page;

	assert(mh != NULL);

	if (menu == NULL)
	{
		item = key_press;
	} else if (key_press < 1 || key_press > GetMaxPageItems()) {
		cancel = true;
	} else {
		ItemSelection type = states.slots[key_press].type;

		/* Check if we should play a sound about the type */
		if (g_Menus.MenuSoundsEnabled() && 
			(!menu || (menu->GetMenuOptionFlags() & MENUFLAG_NO_SOUND) != MENUFLAG_NO_SOUND))
		{
			CellRecipientFilter filter;
			cell_t clients[1];

			clients[0] = client;
			filter.Initialize(clients, 1);

			const char *sound = g_Menus.GetMenuSound(type);

			if (sound != NULL)
			{
				edict_t *pEdict = PEntityOfEntIndex(client);
				if (pEdict)
				{
					ICollideable *pCollideable = pEdict->GetCollideable();

					if (pCollideable)
					{
						const Vector & pos = pCollideable->GetCollisionOrigin();
						enginesound->EmitSound(filter, 
							client, 
							CHAN_AUTO, 
#if SOURCE_ENGINE >= SE_PORTAL2
							sound, 
							-1, 
#endif
							sound, 
							VOL_NORM, 
							ATTN_NORM, 
#if SOURCE_ENGINE >= SE_PORTAL2
							0, 
#endif
							0, 
							PITCH_NORM, 
#if SOURCE_ENGINE == SE_CSS || SOURCE_ENGINE == SE_HL2DM || SOURCE_ENGINE == SE_DODS \
	|| SOURCE_ENGINE == SE_SDK2013 || SOURCE_ENGINE == SE_BMS || SOURCE_ENGINE == SE_TF2
							0,
#endif
							&pos);
					}
				}
			}
		}

		/* For navigational items, we're going to redisplay */
		if (type == ItemSel_Back)
		{
			if (!RedoClientMenu(client, ItemOrder_Descending))
			{
				cancel = true;
				reason = MenuCancel_NoDisplay;
				end_reason = MenuEnd_Cancelled;
			} else {
				return;
			}
		} else if (type == ItemSel_Next) {
			if (!RedoClientMenu(client, ItemOrder_Ascending))
			{
				cancel = true;						/* I like Saltines. */
				reason = MenuCancel_NoDisplay;
				end_reason = MenuEnd_Cancelled;
			} else {
				return;
			}
		} else if (type == ItemSel_Exit || type == ItemSel_None) {
			cancel = true;
			reason = MenuCancel_Exit;
			end_reason = MenuEnd_Exit;
		} else if (type == ItemSel_ExitBack) {
			cancel = true;
			reason = MenuCancel_ExitBack;
			end_reason = MenuEnd_ExitBack;
		} else {
			item = states.slots[key_press].item;
		}
	}

	/* Clear states */
	player->bInMenu = false;
	if (player->menuHoldTime)
	{
		RemoveClientFromWatch(client);
	}

	Handle_t hndl = menu ? menu->GetHandle() : BAD_HANDLE;
	AutoHandleRooter ahr(hndl);

	if (cancel)
	{
		mh->OnMenuCancel(menu, client, reason);
	} else {
		mh->OnMenuSelect(menu, client, item);
		if (mh->GetMenuAPIVersion2() >= 13)
		{
			mh->OnMenuSelect2(menu, client, item, item_on_page);
		}
	}

	/* Only fire end for valid menus */
	if (menu)
	{
		mh->OnMenuEnd(menu, end_reason);
	}
}