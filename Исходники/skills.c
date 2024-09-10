/**
 * Op throws any object toss_item.
 * @param op Living thing throwing something.
 * @param toss_item Item thrown.
 * @param dir Direction to throw. */
void do_throw(object *op, object *toss_item, int dir)
{
	object *left_cont, *throw_ob = toss_item, *left = NULL, *tmp_op;
	tag_t left_tag;
	rv_vector range_vector;

	if (!throw_ob)
	{
		if (op->type == PLAYER)
		{
			new_draw_info(NDI_UNIQUE, op, "You have nothing to throw.");
		}

		return;
	}

	if (QUERY_FLAG(throw_ob, FLAG_STARTEQUIP))
	{
		if (op->type == PLAYER)
		{
			new_draw_info(NDI_UNIQUE, op, "The gods won't let you throw that.");
		}

		return;
	}

	if (throw_ob->weight <= 0)
	{
		new_draw_info_format(NDI_UNIQUE, op, "You can't throw %s.\n", query_base_name(throw_ob, NULL));
		return;
	}

	/* These are throwing objects left to the player */
	left = throw_ob;
	left_cont = left->env;
	left_tag = left->count;

	/* Sometimes get_split_ob can't split an object (because op->nrof==0?)
	 * and returns NULL. We must use 'left' then */
	if ((throw_ob = get_split_ob(throw_ob, 1, NULL, 0)) == NULL)
	{
		throw_ob = left;
		remove_ob(left);
		check_walk_off(left, NULL, MOVE_APPLY_VANISHED);

		if (op->type == PLAYER)
		{
			esrv_del_item(CONTR(op), left->count, left->env);
		}
	}
	else if (op->type == PLAYER)
	{
		if (was_destroyed(left, left_tag))
		{
			esrv_del_item(CONTR(op), left_tag, left_cont);
		}
		else
		{
			esrv_update_item(UPD_NROF, op, left);
		}
	}

	/* Special case: throwing powdery substances like dust, dirt */
	if (QUERY_FLAG(throw_ob, FLAG_DUST))
	{
		cast_dust(op, throw_ob, dir);

		/* update the shooting speed for the player action timer.
		 * We init the used skill with it - its not calculated here.
		 * cast_dust() can change the used skill... */
		if (op->type == PLAYER)
		{
			op->chosen_skill->stats.maxsp = throw_ob->last_grace;
		}

		return;
	}

	/* Targetting throwing */
	if (!dir && op->type == PLAYER && OBJECT_VALID(CONTR(op)->target_object, CONTR(op)->target_object_count))
	{
		dir = get_dir_to_target(op, CONTR(op)->target_object, &range_vector);
	}

	/* Three things here prevent a throw, you aimed at your feet, you
	 * have no effective throwing strength, or you threw at a wall */
	if (!dir || wall(op->map, op->x + freearr_x[dir], op->y + freearr_y[dir]))
	{
		/* Bounces off 'wall', and drops to feet */
		if (!QUERY_FLAG(throw_ob, FLAG_REMOVED))
		{
			remove_ob(throw_ob);

			if (check_walk_off(throw_ob, NULL, MOVE_APPLY_MOVE) != CHECK_WALK_OK)
			{
				return;
			}
		}

		throw_ob->x = op->x;
		throw_ob->y = op->y;

		if (!insert_ob_in_map(throw_ob, op->map, op, 0))
		{
			return;
		}

		if (op->type == PLAYER)
		{
			if (!dir)
			{
				new_draw_info_format(NDI_UNIQUE, op, "You drop %s at the ground.", query_name(throw_ob, NULL));
			}
			else
			{
				new_draw_info(NDI_UNIQUE, op, "Something is in the way.");
			}
		}

		return;
	}

	set_owner(throw_ob, op);
	set_owner(throw_ob->inv, op);
	throw_ob->direction = dir;
	throw_ob->x = op->x;
	throw_ob->y = op->y;

	/* Save original wc and dam */
	throw_ob->last_heal = throw_ob->stats.wc;
	throw_ob->stats.hp = throw_ob->stats.dam;

	/* Speed */
	throw_ob->speed = MIN(1.0f, (speed_bonus[op->stats.Str] + 1.0f) / 1.5f);

	/* Now we get the wc from the used skill. */
	if ((tmp_op = SK_skill(op)))
	{
		throw_ob->stats.wc += tmp_op->last_heal;
	}
	/* Monsters */
	else
	{
		throw_ob->stats.wc += 10;
	}

	throw_ob->stats.wc_range = op->stats.wc_range;

	if (QUERY_FLAG(throw_ob, FLAG_IS_THROWN))
	{
		throw_ob->stats.dam += throw_ob->magic;
		throw_ob->stats.wc += throw_ob->magic;

		/* Adjust for players */
		if (op->type == PLAYER)
		{
			op->chosen_skill->stats.maxsp = throw_ob->last_grace;
			throw_ob->stats.dam = FABS((int) ((float) (throw_ob->stats.dam + dam_bonus[op->stats.Str] / 2) * LEVEL_DAMAGE(SK_level(op))));
			throw_ob->stats.wc += thaco_bonus[op->stats.Dex] + SK_level(op);
		}
		else
		{
			throw_ob->stats.dam = FABS((int) ((float) (throw_ob->stats.dam) * LEVEL_DAMAGE(op->level)));
			throw_ob->stats.wc += 10 + op->level;
		}

		throw_ob->stats.grace = throw_ob->last_sp;
		throw_ob->stats.maxgrace = 60 + (RANDOM() % 12);

		/* Only throw objects get directional faces */
		if (GET_ANIM_ID(throw_ob) && NUM_ANIMATIONS(throw_ob))
		{
			SET_ANIMATION(throw_ob, (NUM_ANIMATIONS(throw_ob) / NUM_FACINGS(throw_ob)) * dir);
		}

		/* Adjust damage with item condition */
		throw_ob->stats.dam = (sint16) (((float) throw_ob->stats.dam / 100.0f) * (float) throw_ob->item_condition);
	}

	if (throw_ob->stats.dam < 0)
	{
		throw_ob->stats.dam = 0;
	}

	update_ob_speed(throw_ob);
	throw_ob->speed_left = 0;

	SET_MULTI_FLAG(throw_ob, FLAG_FLYING);
	SET_FLAG(throw_ob, FLAG_FLY_ON);
	SET_FLAG(throw_ob, FLAG_WALK_ON);

	play_sound_map(op->map, CMD_SOUND_EFFECT, "throw.ogg", op->x, op->y, 0, 0);

	/* Trigger the THROW event */
	trigger_event(EVENT_THROW, op, throw_ob, NULL, NULL, 0, 0, 0, SCRIPT_FIX_ACTIVATOR);

	if (insert_ob_in_map(throw_ob, op->map, op, 0))
	{
		move_arrow(throw_ob);
	}
}