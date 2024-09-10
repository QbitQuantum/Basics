// Update: draw background
update_status ModulePlayer::Update()
{
	float speed = 1.6f;


	switch (status){
	case NORMAL:
	{
		if (god == false){
			player->type = COLLIDER_PLAYER;
		}
		else if (god == true){
			player->type = COLLIDER_NONE;
		}
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x >= 200){
				speed = 0;
			}
			position.x += speed;
			if (current_animation != &right && App->input->keyboard[SDL_SCANCODE_LALT] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_REPEAT)
			{
				right.Reset();
				current_animation = &right;
			}

			else if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN)
			{
				jump_right.loops = 0;
				jump_right.Reset();
				current_animation = &jump_right;
				status = ROLL;
			}

			else if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT)
			{
				position.x -= speed;
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &shotidle;
				}
				else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
					current_animation = &shotopright;

				}
				else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
					current_animation = &shotrighttop;

				}
				else if ((App->scope->position.x - position.x) > 77.3f){
					current_animation = &shotright;

				}
			}
		}

		else if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
		{

			if (position.x <= 0){
				speed = 0;
			}
			position.x -= speed;
			if (current_animation != &left && App->input->keyboard[SDL_SCANCODE_LALT] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_LCTRL] != KEY_STATE::KEY_REPEAT)
			{
				left.Reset();
				current_animation = &left;
			}
			else if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
				jump_left.loops = 0;
				jump_left.Reset();
				current_animation = &jump_left;
				status = ROLL;
			}

			else if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT)
			{
				position.x += speed;
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &shotidle;
				}
				else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
					current_animation = &shotopleft;
				}
				else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
					current_animation = &shotleftop;
				}
				else if ((position.x - App->scope->position.x) > 77.3f){
					current_animation = &shotleft;

				}



			}
		}

		else if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT || (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_RIGHT] != KEY_STATE::KEY_REPEAT  && App->input->keyboard[SDL_SCANCODE_LEFT] != KEY_STATE::KEY_REPEAT)){
			if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
				current_animation = &shotidle;
			}

			else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
				current_animation = &shotopleft;
			}
			else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
				current_animation = &shotleftop;
			}
			else if ((position.x - App->scope->position.x) > 77.3f){
				current_animation = &shotleft;

			}

			else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
				current_animation = &shotopright;
			}

			else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
				current_animation = &shotrighttop;
			}

			else if ((App->scope->position.x - position.x) > 77.3f){
				current_animation = &shotright;

			}

		}


		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_IDLE){
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &idle;
				}
				else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
					current_animation = &lookingleft;
				}
				else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
					current_animation = &lookingfarleft;
				}
				else if ((position.x - App->scope->position.x) > 77.3f){
					current_animation = &lookingveryfarleft;

				}

				else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
					current_animation = &lookingright;//
				}

				else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
					current_animation = &lookingfarright;
				}

				else if ((App->scope->position.x - position.x) > 77.3f){
					current_animation = &lookingveryfarright;
				}
				else{
					current_animation = &idle;
				}
		}
		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN){
			current_animation = &crouch;
			status = CROUCH;
		}
		player->rect.x = position.x + 14;
		player->rect.y = position.y + 20;
		player->rect.h = 16;
		player->rect.w = 12;
	} break;

	case ROLL:
	{
		player->type = COLLIDER_NONE;
		if (current_animation == &jump_right){
			if (position.x >= 180){
				speed = 0;
			}
			else
			{
				position.x += speed;
			}
			if (current_animation->Finished() == true){
				if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
					current_animation = &crouch;
					status = CROUCH;
				}
				else{
					status = NORMAL;
				}
				break;
			}
		}
		if (current_animation == &jump_left){
			if (position.x <= 0){
				speed = 0;
			}
			else
			{
				position.x -= speed;
			}
			if (current_animation->Finished() == true){
				if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
					current_animation = &crouch;
					status = CROUCH;
				}
				else{
					status = NORMAL;
				}
				break;
			}
		}
	} break;
	case CROUCHROLL:
	{
		player->type = COLLIDER_NONE;
		if (current_animation == &crouchjumpright){
			if (position.x >= 180){
				speed = 0;
			}
			else
			{
				position.x += (speed*2)/3;
			}
			if (current_animation->Finished() == true){
				if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
					current_animation = &crouch;
					status = CROUCH;
				}
				else{
					status = NORMAL;
				}
				break;
			}
		}
		if (current_animation == &crouchjumpleft){
			if (position.x <= 0){
				speed = 0;
			}
			else
			{
				position.x -= (speed * 2) / 3;
			}
			if (current_animation->Finished() == true){
				if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
					current_animation = &crouch;
					status = CROUCH;
				}
				else{
					status = NORMAL;
				}
				break;
			}
		}
	} break;
	case DEAD:
	{
		player->type = COLLIDER_NONE;
		if (current_animation->Finished() == true){
			status = NORMAL;
			break;
		}

	} break;

	case WIN:
	{
		position.y -= 0.3;
		position.x = 100;
		player->type = COLLIDER_NONE;
		if (current_animation->Finished() == true){
			current_animation->Reset();
			current_animation->loops = 0;
			App->fade->FadeToBlack(App->level2, App->victoryscreen, 2);
			status = NORMAL;
			break;
		}
	}break;

	case CROUCH:
	{
		player->rect.x = position.x + 10;
		player->rect.y = position.y + 40;
		player->rect.h = 8;
		player->rect.w = 12;
		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT){
			if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT){
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &crouchshotidle;
				}

				else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
					current_animation = &crouchshotleft;
				}
				else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
					current_animation = &crouchshottopleft;
				}
				else if ((position.x - App->scope->position.x) > 77.3f){
					current_animation = &crouchshotlefttop;

				}

				else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
					current_animation = &crouchshotright;//
				}

				else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
					current_animation = &crouchshotopright;
				}

				else if ((App->scope->position.x - position.x) > 77.3f){
					current_animation = &crouchshotrighttop;

				}

			}
			else{
				if (((position.x - App->scope->position.x) > 0 && (position.x - App->scope->position.x) <= 10.0f) || ((App->scope->position.x - position.x) > 0 && (App->scope->position.x - position.x) <= 10.0f)){
					current_animation = &crouch;
				}
				else if ((position.x - App->scope->position.x) > 10 && (position.x - App->scope->position.x) <= 38.6f){
					current_animation = &crouchlookingleft;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpleft.loops = 0;
						crouchjumpleft.Reset();
						current_animation = &crouchjumpleft;
						status = CROUCHROLL;
					}
				}
				else if ((position.x - App->scope->position.x) > 38.6f && (position.x - App->scope->position.x) <= 77.3f){
					current_animation = &crouchlookingfarleft;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpleft.loops = 0;
						crouchjumpleft.Reset();
						current_animation = &crouchjumpleft;
						status = CROUCHROLL;
					}
				}
				else if ((position.x - App->scope->position.x) > 77.3f){
					current_animation = &crouchlookingveryfarleft;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpleft.loops = 0;
						crouchjumpleft.Reset();
						current_animation = &crouchjumpleft;
						status = CROUCHROLL;
					}

				}

				else if ((App->scope->position.x - position.x) > 10 && (App->scope->position.x - position.x) <= 38.6f){
					current_animation = &crouchlookingright;//
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpright.loops = 0;
						crouchjumpright.Reset();
						current_animation = &crouchjumpright;
						status = CROUCHROLL;
					}
				}

				else if ((App->scope->position.x - position.x) > 38.6f && (App->scope->position.x - position.x) <= 77.3f){
					current_animation = &crouchlookingfarright;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpright.loops = 0;
						crouchjumpright.Reset();
						current_animation = &crouchjumpright;
						status = CROUCHROLL;
					}
				}

				else if ((App->scope->position.x - position.x) > 77.3f){
					current_animation = &crouchlookingveryfarright;
					if (App->input->keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_DOWN){
						crouchjumpright.loops = 0;
						crouchjumpright.Reset();
						current_animation = &crouchjumpright;
						status = CROUCHROLL;
					}
				}
			}
			
		}
		else{
			status = NORMAL;
		}
	}break;
	}
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN){
		if (god == false){
			player->type = COLLIDER_NONE;
			App->textures->Unload(graphics);
			graphics = App->textures->Load("Images/Main_character_CowBoy_GodMode.png");
			god = true;

		}
		else if (god == true){
			App->textures->Unload(graphics);
			graphics = App->textures->Load("Images/Main_character_CowBoy.png");
			god = false;
			player->type = COLLIDER_PLAYER;
		}
	}
	/*player->rect.x = position.x + 10;
	player->rect.y = position.y + 20;
	player->rect.h = 8;
	player->rect.w = 12;*/
	hit = true;

	

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	sprintf_s(score_text, 10, "%7d", score);
	sprintf_s(tnt_text, 10, "%7d", tntammo);
	App->font->Blit(18, 1, font_score, score_text);
	App->font->Blit(0, 201, font_score, tnt_text);

	return UPDATE_CONTINUE;
}