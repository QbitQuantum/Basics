	bool OnProcess(void)
	{
		CStageMap& map = avej_lite::singleton<CStageMap>::get();

		if (GetSysDesc().stage.has_cleared)
		{
			SetSysDesc().stage.has_cleared = false;
			SetSysDesc().stage.current_stage = GetSysDesc().stage.current_stage + 1;

			if (GetSysDesc().stage.current_stage > 5)
			{
				g_ChangeState(STATE_ENDING_HAPPY);
				return false;
			}

			map.SetCurrentMap(GetSysDesc().stage.current_stage);

			SetSysDesc().stage.message.remained_ticks = SCROLL_DELAY_CALC(100);

			tchar stage_message[256];
			util::ComposeString(stage_message, TCHAR("STAGE @"), GetSysDesc().stage.current_stage);
			// -> sprintf(stage_message, "STAGE %d", GetSysDesc().stage.current_stage);

			SetSysDesc().stage.message.Set(stage_message);
		}

		CInputDevice& input_device = avej_lite::singleton<CInputDevice>::get();
		input_device.UpdateInputState();

		{
			bool has_pressed_exit_key;
			
			has_pressed_exit_key = input_device.WasKeyPressed(avej_lite::INPUT_KEY_SYS1);

			if (has_pressed_exit_key)
			{
				if ((assigned_(objects[MIN_FRIEND]) && objects[MIN_FRIEND]->IsValid()) ||
					(assigned_(objects[MAX_FRIEND]) && objects[MAX_FRIEND]->IsValid()))
					g_ChangeState(STATE_EXIT);
				else
					g_ChangeState(STATE_ENDING_BAD);

				return false;
			}
		}

		// process objects
		map.Move(SCROLL_SPEED, 0);

		{
			IGfxDevice::TDeviceDesc screenDesc;

			g_p_gfx_device->GetDesc(screenDesc);

			g_p_gfx_device->BeginDraw();

			// clear the screen
			g_p_back_buffer->StretchBlt(0, 0, 800, 480, g_p_res_sprite, 0, 512, 640, 216*2);

			// display background
			for (int j = 0; j < 8; j++)
			for (int i = 0; i < 18; i++)
			{
				int x_offset = map.GetXOffset();
				int y_offset = map.GetYOffset();

				if (map.GetTile(i*TILE_X_SIZE-x_offset, j*TILE_Y_SIZE-y_offset) > 0)
				{
					gfx::DrawImage(i*TILE_X_SIZE-x_offset, j*TILE_Y_SIZE-y_offset+Y_DOWN+1,tile_data[TILENAME_TILE_GROUND]->m_p_sprite);
				}
			}

			for (int i = MAX_ENEMY; i >= MIN_OBJECTS; i--)
			{
				if (assigned_(objects[i]))
				{
					if (objects[i]->ProcessByAI())
					{
						if (objects[i]->IsValid())
						{
							objects[i]->ProcessByGravity();
							objects[i]->Display();
						}
						else
						{
							delete objects[i];
							objects[i] = NULL;
						}
					}
					else
					{
						delete objects[i];
						objects[i] = NULL;
					}
				}
			}

			{
				gui::CFloatMessage& message = avej_lite::singleton<gui::CFloatMessage>::get();
				message.Show();
			}

			g_p_back_buffer->StretchBlt
			(
				0, 0, 800, 31,
				g_p_res_sprite,
				g_sprite_rect[TILENAME_TILE_STATUS_BAR].x,
				g_sprite_rect[TILENAME_TILE_STATUS_BAR].y,
				g_sprite_rect[TILENAME_TILE_STATUS_BAR].w,
				g_sprite_rect[TILENAME_TILE_STATUS_BAR].h
			);

			{
				int   i = 0;
				int   j = 0;
				tchar s1[64] = {0, };
				tchar s2[64] = {0, };
				int   number1 = 0;
				int   number2 = 0;

				if (assigned_(objects[MIN_FRIEND]))
				{
					TFriend* p_friend = (TFriend*)objects[MIN_FRIEND];
					i = p_friend->m_hit_point;
					number1 = p_friend->m_special_weapon;
					util::ComposeString(s1, TCHAR("@"), p_friend->GetLevel());
					// -> sprintf(s1, "%d", p_friend->GetLevel());
				}
				if (assigned_(objects[MAX_FRIEND]))
				{
					TFriend* p_friend = (TFriend*)objects[MAX_FRIEND];
					j = p_friend->m_hit_point;
					number2 = p_friend->m_special_weapon;
					util::ComposeString(s2, TCHAR("@"), p_friend->GetLevel());
					// -> sprintf(s2, "%d", p_friend->GetLevel());
				}

				switch (GetSysDesc().GetPlayerMode())
				{
					case PLAYERMODE_PLAYER1_ONLY:
						i = 104 + i;
						j = 424;
						break;
					case PLAYERMODE_PLAYER2_ONLY:
						j = 424 + i;
						i = 104;
						STRCPY(s2, s1);
						STRCPY(s1, TCHAR(""));
						number2 = number1;
						number1 = 0;
						break;
					case PLAYERMODE_DOUBLE_MODE1:
						i = 104 + i;
						j = 424 + j;
						break;
					case PLAYERMODE_DOUBLE_MODE2:
						{
							int k;

							k = i;
							i = 104 + j;
							j = 424 + k;

							k = number1;
							number1 = number2;
							number2 = k;

							tchar s3[64];
							STRCPY(s3, s2);
							STRCPY(s2, s1);
							STRCPY(s1, s3);
						}
						break;
				}

				if (i < 208)
				{
					// i: 104~208
					// (x:129,y:12)-(w:132,h:5)
					int percentage = (i-104) * 100 / (208-104);

					int x1 = 129;
					int y1 = 12;
					int x2 = 129 + 132;
					int y2 = y1 + 5;

					x1 = x1 + 132 * percentage / 100;

					gfx::FillRect(0xFF000000, x1, y1, x2-x1, y2-y1);
				}

				if (j < 528)
				{
					// j: 424~528
					// (x:530,y:12)-(w:131,h:5)
					int percentage = (j-424) * 100 / (528-424);

					int x1 = 530;
					int y1 = 12;
					int x2 = 530 + 131;
					int y2 = y1 + 5;

					x1 = x1 + 131 * percentage / 100;

					gfx::FillRect(0xFF000000, x1, y1, x2-x1, y2-y1);
				}

				if (s1[0])
				{
					gfx_ix::DrawText(341,4,s1,TIndexColor(3));
					gfx_ix::DrawText(340,3,s1,TIndexColor(4));
				}
				if (s2[0])
				{
					gfx_ix::DrawText(741,4,s2,TIndexColor(3));
					gfx_ix::DrawText(740,3,s2,TIndexColor(4));
				}
				if (number1 > 0)
				{
					if (number1 > 10) number1 = 10;
					for (int i = 0; i < number1; i++)
					{
						gfx::DrawSprite(i*24+TILE_X_SIZE,30,tile_data[TILENAME_SMGAL_SP]->m_p_sprite,true);
					}
				}
				if (number2 > 0)
				{
					if (number2 > 10) number2 = 10;
					for (int i = 0; i < number2; i++)
					{
						gfx::DrawSprite(i*24+TILE_X_SIZE+330,36,tile_data[TILENAME_NETO_SP]->m_p_sprite,true);
					}
				}
			}

			if (GetSysDesc().stage.message.remained_ticks > 0)
			{
				SetSysDesc().stage.message.remained_ticks = GetSysDesc().stage.message.remained_ticks - 1;
				int i = (640/24 - STRLEN(GetSysDesc().stage.message.Get())) / 2;
				gfx_ix::DrawText_x2(i*12, 85, GetSysDesc().stage.message.Get(), TIndexColor(11));
			}

			gui::CButtonGroupFull::Show();

			// flip the screen
			g_p_gfx_device->EndDraw();
			g_p_gfx_device->Flip();
		}

		if (map.IsEndOfMap())
		{
			int k = 0;
			for (int i = MIN_ENEMY; i <= MAX_ENEMY; i++)
			{
				if (assigned_(objects[i]))
					k++;
			}
			if (k == 0)
			{
				SetSysDesc().stage.has_cleared = true;
//				ascii_code  = ascii_code + [_ESC_KEY];
			}
		}

		return true;
	}