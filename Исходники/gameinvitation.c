struct Box_s *GameInvitation_Create(struct Box_s *roster, char *fromjid, struct gamesearchinfo_s *info, int replace, int cascade)
{
	struct gameinvitationdata_s *data = malloc(sizeof(*data));
	struct Box_s *dialog, *pbox, *vertsize;
	char titlebartxt[512];

	memset(data, 0, sizeof(*data));

	dialog = Box_Create(0, 0, 440, 270, BOX_VISIBLE);
	dialog->boxtypeid = BOXTYPE_GAMEINVITATION;
	dialog->bgcol = DefaultBG;

	dialog->boxdata = data;

	data->jid = strdup(fromjid);
	data->info = Info_DupeGameSearchInfo(info);

	if (replace)
	{
		i18n_stringsub(titlebartxt, 512, _("Game Renegotiation From %1"), Model_GetFriendNick(fromjid));
	}
	else
	{
		i18n_stringsub(titlebartxt, 512, _("Game Invitation From %1"), Model_GetFriendNick(fromjid));
	}
	dialog->titlebar = TitleBarOnly_Add(dialog, titlebartxt);
	dialog->OnActive = TitleBarRoot_OnActive;
	dialog->OnInactive = TitleBarRoot_OnInactive;

	vertsize = AutoSize_Create(10, 43, 0, 0, 0, 0, AUTOSIZE_VERT);
	Box_AddChild(dialog, vertsize);
	data->sizeablecontent = vertsize;
	{
		struct Box_s *horizsize;
		struct Box_s *vertsize2;

		pbox = Text_Create(10, 2, 280, 60, BOX_TRANSPARENT, TX_WRAP);
		/*pbox->OnSizeWidth = Text_OnSizeWidth_Stretch;
		pbox->OnSizeHeight = Box_OnSizeHeight_Stretch;
		*/
		pbox->fgcol = RGB(222, 222, 222);
		Box_AddChild(vertsize, pbox);
		data->messagebox = pbox;

		vertsize2 = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_VERT);
		vertsize2->OnSizeWidth = Box_OnSizeWidth_Stretch;
		data->infobox = vertsize2;
		Box_AddChild(vertsize, vertsize2);
		{
			struct Box_s *vertsize = AutoSize_Create(10, 0, 0, 0, 0, 0, AUTOSIZE_VERT);
			Box_AddChild(vertsize2, vertsize);
			{
				struct Box_s *horizsize = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ | AUTOSIZE_EVENSPACING);
				Box_AddChild(vertsize, horizsize);
				{
					struct Box_s *horizsize2 = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ);
					Box_AddChild(horizsize, horizsize2);
					{
						pbox = Text_Create(0, 0, 95, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ | TX_RIGHT);
						pbox->fgcol = UserInfoFG2;
						Text_SetText(pbox, _("Side"));
						Box_AddChild(horizsize2, pbox);

						AutoSize_AddSpacer(horizsize2, 10);

						pbox = Text_Create(10 /*115*/, 0, 90, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ);
						pbox->fgcol = RGB(222, 222, 222);

						if (info->colorpreference == 1)
						{
							Text_SetText(pbox, _("Black"));
						}
						else if (info->colorpreference == 2)
						{
							Text_SetText(pbox, _("White"));
						}
						else
						{
							Text_SetText(pbox, _("No Preference"));
						}

						Box_AddChild(horizsize2, pbox);
					}

					horizsize2 = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ);
					Box_AddChild(horizsize, horizsize2);
					{
						pbox = Text_Create(10 /*215*/, 0, 60, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ | TX_RIGHT);
						pbox->fgcol = UserInfoFG2;
						Text_SetText(pbox, _("Rated Game"));
						Box_AddChild(horizsize2, pbox);

						AutoSize_AddSpacer(horizsize2, 10);

						pbox = Text_Create(10, /*280*/ 0, 90, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ);
						pbox->fgcol =  RGB(222, 222, 222);
						Text_SetText(pbox, info->rated ? _("Yes") : _("No"));
						Box_AddChild(horizsize2, pbox);
					}
				}

				AutoSize_AddSpacer(vertsize, 2);

				horizsize = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ | AUTOSIZE_EVENSPACING);
				Box_AddChild(vertsize, horizsize);
				{
					struct Box_s *horizsize2 = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ);
					Box_AddChild(horizsize, horizsize2);
					{
						pbox = Text_Create(0, 0, 95, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ | TX_RIGHT);
						pbox->fgcol = UserInfoFG2;
						Text_SetText(pbox, _("Game Variant"));
						Box_AddChild(horizsize2, pbox);

						AutoSize_AddSpacer(horizsize2, 10);

						pbox = Text_Create(10 /*115*/, 0, 90, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ);
						pbox->fgcol = RGB(222, 222, 222);
						Text_SetText(pbox, Util_Capitalize(info->variant));
						Box_AddChild(horizsize2, pbox);
					}

					if (info->takebacks)
					{
						horizsize2 = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ);
						Box_AddChild(horizsize, horizsize2);
						{
							pbox = Text_Create(10 /*215*/, 0, 60, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ | TX_RIGHT);
							pbox->fgcol = UserInfoFG2;
							Text_SetText(pbox, _("Takebacks"));
							Box_AddChild(horizsize2, pbox);

							AutoSize_AddSpacer(horizsize2, 10);

							pbox = Text_Create(10, /*280*/ 0, 90, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ);
							pbox->fgcol =  RGB(222, 222, 222);
							Text_SetText(pbox, Util_Capitalize(info->takebacks));
							Box_AddChild(horizsize2, pbox);
						}
					}
				}

				AutoSize_AddSpacer(vertsize, 2);

				horizsize = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ);
				Box_AddChild(vertsize, horizsize);
				{
					char buffer[1024];

					pbox = Text_Create(10, 0, 95, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ | TX_RIGHT);
					pbox->fgcol = UserInfoFG2;
					Text_SetText(pbox, _("Time Settings"));
					Box_AddChild(horizsize, pbox);

					AutoSize_AddSpacer(horizsize, 10);

					pbox = Text_Create(10, 0, 265, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHVERT);
					pbox->fgcol =  RGB(222, 222, 222);
					Text_SetLinkColor(pbox, CR_LtOrange);
					Text_SetText(pbox, Info_TimeControlsToMultilineText(info->timecontrol, info->blacktimecontrol, buffer, 1024));
					Box_AddChild(horizsize, pbox);
				}

				AutoSize_AddSpacer(vertsize, 2);

				horizsize = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ);
				Box_AddChild(vertsize, horizsize);
				{
					pbox = Text_Create(10, 0, 95, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ | TX_RIGHT);
					pbox->fgcol = UserInfoFG2;
					Text_SetText(pbox, _("Comment"));
					Box_AddChild(horizsize, pbox);

					AutoSize_AddSpacer(horizsize, 10);

					pbox = Text_Create(5, 0, 255, 40, BOX_VISIBLE | BOX_TRANSPARENT, TX_WRAP | TX_STRETCHVERT);
					pbox->fgcol =  RGB(222, 222, 222);
					Text_SetText(pbox, info->comment);
					Box_AddChild(horizsize, pbox);
				}
				
			}

			AutoSize_AddSpacer(vertsize2, 2);

			pbox = Box_Create(0, 0, vertsize2->w, 1, BOX_VISIBLE);
			pbox->bgcol = RGB(77, 77, 77);
			pbox->OnSizeWidth = Box_OnSizeWidth_Stretch;
			Box_AddChild(vertsize2, pbox);

			pbox = Box_Create(0, 0, vertsize2->w, 1, BOX_VISIBLE);
			pbox->bgcol = RGB(102, 102, 102);
			pbox->OnSizeWidth = Box_OnSizeWidth_Stretch;
			Box_AddChild(vertsize2, pbox);

			AutoSize_AddSpacer(vertsize2, 13);

			horizsize = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ);
			horizsize->OnSizeWidth = Box_OnSizeWidth_Stretch;
			Box_AddChild(vertsize2, horizsize);
			{
				AutoSize_AddSpacer(horizsize, 40);

				pbox = Text_Create(0, 5, 50, 20, BOX_VISIBLE | BOX_TRANSPARENT, TX_STRETCHHORIZ | TX_RIGHT);
				pbox->fgcol = UserInfoFG2;
				Text_SetText(pbox, _("Opponent"));
				Box_AddChild(horizsize, pbox);

				AutoSize_AddSpacer(horizsize, 20);

				pbox = MiniProfile_Create(0, 0, 225, 50, fromjid);
				pbox->OnSizeWidth = Box_OnSizeWidth_Stretch;
				data->opponentbox = pbox;
				Box_AddChild(horizsize, pbox);

				AutoSize_AddSpacer(horizsize, 40);
			}
			
		}

		AutoSize_AddSpacer(vertsize, 37);

		horizsize = AutoSize_Create(0, 0, 0, 0, 0, 0, AUTOSIZE_HORIZ);
		horizsize->OnSizeWidth = Box_OnSizeWidth_Stretch;
		Box_AddChild(vertsize, horizsize);
		{
			struct Box_s *horizsize2 = AutoSizeSpace_Create(0, 0, 0, 0, 0, 0, 10, AUTOSIZE_HORIZ);
			Box_AddChild(horizsize, horizsize2);
			{
				pbox = StdButton_Create(0, 0, 90, _("Change Game Terms"), 0);
				Button2_SetOnButtonHit(pbox, GameInvitation_OnChange);
				Box_AddChild(horizsize2, pbox);
				data->changebutton = pbox;

				pbox = StdButton_Create(0, 0, 90, _("Open Chat"), 0);
				Button2_SetOnButtonHit(pbox, GameInvitation_OnChat);
				Box_AddChild(horizsize2, pbox);
				data->openchatbutton = pbox;

				AutoSize_AddSpacer(horizsize2, 0);
			}

			horizsize2 = AutoSizeSpace_Create(0, 0, 0, 0, 0, 0, 10, AUTOSIZE_HORIZ);
			horizsize2->OnSizeWidth = Box_OnSizeWidth_StickRight;
			Box_AddChild(horizsize, horizsize2);
			{	
				pbox = StdButton_Create(0, 0, 90, _("Accept Game"), 0);
				Button2_SetOnButtonHit(pbox, GameInvitation_OnAccept);
				Box_AddChild(horizsize2, pbox);
				data->acceptbutton = pbox;

				pbox = StdButton_Create(0, 0, 90, _("Decline Game"), 0);
				Button2_SetOnButtonHit(pbox, GameInvitation_OnDecline);
				Box_AddChild(horizsize2, pbox);
				data->cancelbutton = pbox;
			}
		}
	}

	AutoSize_Fit(data->sizeablecontent);
	AutoSize_Fill(data->sizeablecontent);

	Box_OnSizeWidth_Stretch(dialog, data->sizeablecontent->w + 20 - dialog->w);
	Box_OnSizeHeight_Stretch(dialog, data->sizeablecontent->h + 50 - dialog->h);

	{
		RECT windowrect;
		HMONITOR hm;
		MONITORINFO mi;
		int remainw, remainh;

		windowrect.left = roster->x;
		windowrect.right = windowrect.left + roster->w - 1;
		windowrect.top = roster->y;
		windowrect.bottom = windowrect.top + roster->h - 1;

		hm = MonitorFromRect(&windowrect, MONITOR_DEFAULTTONEAREST);

		mi.cbSize = sizeof(mi);
		GetMonitorInfo(hm, &mi);

		remainw = mi.rcWork.right - mi.rcWork.left - dialog->w;
		remainh = mi.rcWork.bottom - mi.rcWork.top - dialog->h;

		dialog->x = remainw / 2;
		dialog->y = remainh / 2;

		dialog->x += 20 * cascade;
		dialog->x %= remainw;
		dialog->y += 20 * cascade;
		dialog->y %= remainh;

		dialog->x += mi.rcWork.left;
		dialog->y += mi.rcWork.top;
	}

#if 0
	pbox = Text_Create(20, 40, dialog->w - 40, dialog->h - 80, BOX_TRANSPARENT, TX_WRAP);
	pbox->fgcol = RGB(222, 222, 222);
	Box_AddChild(dialog, pbox);
	data->messagebox = pbox;

	pbox = Box_Create(0, 0, dialog->w, dialog->h, BOX_VISIBLE | BOX_TRANSPARENT);
	data->infobox = pbox;
	Box_AddChild(dialog, pbox);

	pbox = Box_Create(20, 45, 95, 20, BOX_VISIBLE | BOX_TRANSPARENT | BOX_RIGHTTEXT);
	pbox->fgcol = UserInfoFG2;
	Box_SetText(pbox, _("Side"));
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(125, 45, 90, 20, BOX_VISIBLE | BOX_TRANSPARENT);
	pbox->fgcol = RGB(222, 222, 222);
	/* Reversed here since it is the opponent's color preference */
	if (info->colorpreference == 1)
	{
		Box_SetText(pbox, _("Black"));
	}
	else if (info->colorpreference == 2)
	{
		Box_SetText(pbox, _("White"));
	}
	else
	{
		Box_SetText(pbox, _("No Preference"));
	}
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(265, 45, 95, 20, BOX_VISIBLE | BOX_TRANSPARENT);
	pbox->fgcol = UserInfoFG2;
	Box_SetText(pbox, _("Rated Game"));
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(330, 45, 90, 20, BOX_VISIBLE | BOX_TRANSPARENT);
	pbox->fgcol = RGB(222, 222, 222);
	if (info->rated)
	{
		Box_SetText(pbox, _("Yes"));
	}
	else
	{
		Box_SetText(pbox, _("No"));
	}
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(20, 65, 95, 20, BOX_VISIBLE | BOX_TRANSPARENT | BOX_RIGHTTEXT);
	pbox->fgcol = UserInfoFG2;
	Box_SetText(pbox, _("Game Variant"));
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(125, 65, 90, 20, BOX_VISIBLE | BOX_TRANSPARENT);
	pbox->fgcol = RGB(222, 222, 222);
	Box_SetText(pbox, Util_Capitalize(info->variant));
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(20, 85, 95, 20, BOX_VISIBLE | BOX_TRANSPARENT | BOX_RIGHTTEXT);
	pbox->fgcol = UserInfoFG2;
	Box_SetText(pbox, _("Time Settings"));
	Box_AddChild(data->infobox, pbox);

	pbox = Text_Create(125, 85, 315, 20, BOX_VISIBLE | BOX_TRANSPARENT, 0);
	pbox->fgcol = RGB(222, 222, 222);
	Text_SetText(pbox, Info_TimeControlToLongText(info->timecontrol));
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(20, 105, 95, 20, BOX_VISIBLE | BOX_TRANSPARENT | BOX_RIGHTTEXT);
	pbox->fgcol = UserInfoFG2;
	Box_SetText(pbox, _("Comment"));
	Box_AddChild(data->infobox, pbox);

	pbox = Text_Create(125, 105, 290, 40, BOX_VISIBLE | BOX_TRANSPARENT, TX_WRAP);
	pbox->fgcol = RGB(222, 222, 222);
	Text_SetText(pbox, info->comment);
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(10, 139, 420, 1, BOX_VISIBLE);
	pbox->bgcol = RGB(77, 77, 77);
	pbox->OnSizeWidth = Box_OnSizeWidth_Stretch;
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(10, 140, 420, 1, BOX_VISIBLE);
	pbox->bgcol = RGB(102, 102, 102);
	pbox->OnSizeWidth = Box_OnSizeWidth_Stretch;
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(65, 165, 90, 20, BOX_VISIBLE | BOX_TRANSPARENT);
	pbox->fgcol = UserInfoFG2;
	Box_SetText(pbox, _("Opponent"));
	Box_AddChild(data->infobox, pbox);

	pbox = Box_Create(120, 155, 265, 50, BOX_VISIBLE | BOX_BORDER);
	pbox->brcol = RGB(90, 97, 108);
	pbox->bgcol = DrawerBG;
	data->opponentbox = pbox;
	Box_AddChild(data->infobox, pbox);

	pbox = StdButton_Create(10, 270 - 30, 130, _("Change Game Terms"), 0);
	Button2_SetOnButtonHit(pbox, GameInvitation_OnChange);
	Box_AddChild(dialog, pbox);
	data->changebutton = pbox;

	pbox = StdButton_Create(10 + 135, 270 - 30, 80, _("Open Chat"), 0);
	Button2_SetOnButtonHit(pbox, GameInvitation_OnChat);
	Box_AddChild(dialog, pbox);

	pbox = StdButton_Create(440 - 100 - 95, 270 - 30, 90, _("Accept Game"), 0);
	Button2_SetOnButtonHit(pbox, GameInvitation_OnAccept);
	Box_AddChild(dialog, pbox);
	data->acceptbutton = pbox;
	
	pbox = StdButton_Create(440 - 100, 270 - 30, 90, _("Decline Game"), 0);
	Button2_SetOnButtonHit(pbox, GameInvitation_OnDecline);
	Box_AddChild(dialog, pbox);
	data->cancelbutton = pbox;
#endif
	Box_CreateWndCustom(dialog, titlebartxt, roster->hwnd);

	MiniProfile_SetProfile(data->opponentbox, data->jid, NULL);

	Model_SubscribeProfile(data->jid, GameInvitation_SetProfile, dialog);
	dialog->OnDestroy = GameInvitation_OnDestroy;

	if (!Model_GetOption(OPTION_NOGAMENOTIFY))
	{
		FlashWindow(dialog->hwnd, 1);
	}

	return dialog;
}