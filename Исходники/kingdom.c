/////////////// DO FUNCTIONS ///////////////////
void do_kingdom(CHAR_DATA * ch, char *argument)
{
	KINGDOM_DATA *kingdom;
	CHAR_DATA *vch = 0;
	DESCRIPTOR_DATA *d = 0;
	char buf[MAX_STRING_LENGTH];
	char arg1[MAX_STRING_LENGTH];
	char arg2[MAX_STRING_LENGTH];
	char arg3[MAX_STRING_LENGTH];
	long id = 0;
	long i = 0;

	if(IS_NPC(ch))
		return;

	smash_tilde(argument);
	argument = one_argument_case(argument, arg1);
	argument = one_argument_case(argument, arg2);
	strcpy(arg3, argument);

	if(IS_IMMORTAL(ch) && ch->level == MAX_LEVEL)
	{
		if(!str_cmp(arg1, "save"))
		{
			write_kingdoms();
			sprintf(buf,"cp %s %s.bak",KINGDOM_FILE,KINGDOM_FILE);
			system(buf);
			send_to_char("Done, and made backup.\n\r", ch);
			return;
		}

		if(arg1[0] == '\0')
		{
			send_to_char("Syntax: kingdom create\n\r", ch);
			return;
		}

		if(!str_cmp(arg1, "create"))
		{
			create_kingdom();
			write_kingdoms();
			send_to_char("Done.\n\r", ch);
			return;
		}

		if((!is_number(arg1) || !str_cmp(arg1, "help")))
		{
			send_to_char("Syntax: kingdom <id #> <attribute> <value>\n\r", ch);
			send_to_char("        kingdom <id #> delete\n\r", ch);
			send_to_char("\n\r", ch);
			send_to_char("Attributes:\n\r", ch);
			send_to_char("  leader name points pks pds realpoints\n\r", ch);
			send_to_char("  noansiname\n\r", ch);
			send_to_char("\n\r", ch);
		}
		else
		{
			id = atoi(arg1);

			if((kingdom = get_kingdom(id)) == &kingdom_default)
			{
				send_to_char("There is no such kingdom with that ID.\n\r", ch);
				return;
			}

			if(!str_cmp(arg2, "leader"))
			{
				if((vch = get_char_world(ch, arg3)) == 0)
				{
					send_to_char("The leader must be logged on.\n\r", ch);
					return;
				}

				free_string(kingdom->leader);
				kingdom->leader = str_dup(arg3);
				vch->pcdata->kingdom = id;
				send_to_char("Done.\n\r", ch);
				return;
			}

			if(!str_cmp(arg2, "name"))
			{
				free_string(kingdom->name);
				kingdom->name = str_dup(arg3);
				send_to_char("Done.\n\r", ch);
				return;
			}

			if(!str_cmp(arg2, "noansiname"))
			{
				free_string(kingdom->noansiname);
				kingdom->noansiname = str_dup(arg3);
				send_to_char("Done.\n\r", ch);
				return;
			}

			if(!str_cmp(arg2, "delete") && !str_cmp(arg3, "yes"))
			{
				delete_kingdom(kingdom->id);
				return;
			}

			i = atoi(arg3);

			if(!str_cmp(arg2, "points"))
			{
				kingdom->points = i;
				send_to_char("Done.\n\r", ch);
				return;
			}
			if(!str_cmp(arg2, "realpoints"))
			{
				kingdom->realpoints = i;
				send_to_char("Done.\n\r", ch);
				return;
			}
			if(!str_cmp(arg2, "pds"))
			{
				kingdom->pds = i;
				send_to_char("Done.\n\r", ch);
				return;
			}
			if(!str_cmp(arg2, "pks"))
			{
				kingdom->pks = i;
				send_to_char("Done.\n\r", ch);
				return;
			}
			if(!str_cmp(arg2, "assists"))
			{
				kingdom->assists = i;
				send_to_char("Done.\n\r", ch);
				return;
			}
		}
	}

	if(ch->pcdata->kingdom == 0)	// player not in a kingdom
	{
		if(!str_cmp(arg1, "create"))
		{
			if(ch->pcdata->quest < 1000)
			{
				send_to_char("You need 1000 quest points to create a new kingdom.\n\r", ch);
				return;
			}

			if(!arg2 || arg2[0] == '\0' || !arg3 || arg3[0] == '\0')
			{
				send_to_char
					("Syntax (DO NOT MESS THIS UP!): kingdom create \"name WITH ansi\" \"name WITHOUT ansi\"\n\r",
					 ch);
				send_to_char("I suggest you SAY the name a few times to make SURE THE ANSI IS CORRECT.\n\r",
					     ch);
				send_to_char("And if you dont put a final {{x your kingdom will be DELETED.\n\r", ch);
				send_to_char("If your kingdom name has more than one word surround it in QUOTES!\n\r", ch);
				return;
			}

			if(ansistrlen(arg2) > 20 || strlen(arg3) > 20)
			{
				send_to_char("String length is limited to 20 characters!\n\r", ch);
				return;
			}

			kingdom = create_kingdom();
			ch->pcdata->kingdom = kingdom->id;
			ch->pcdata->quest -= 1000;
			free_string(kingdom->leader);
			kingdom->leader = str_dup(ch->name);
			free_string(kingdom->name);
			kingdom->name = str_dup(arg2);
			free_string(kingdom->noansiname);
			kingdom->noansiname = str_dup(arg3);

			kingdom_message(0, "%s has {WCREATED{X The %s Kingdom!", ch->name, kingdom->name);
			write_kingdoms();
			return;
		}

		if(ch->pcdata->kingdom_invite == 0)
		{
			send_to_char("You don't belong to a kingdom.\n\r", ch);
			return;
		}

		// make sure kingdom still exists
		if(get_kingdom(ch->pcdata->kingdom_invite) == &kingdom_default)
		{
			send_to_char("That kingdom was destroyed.\n\r", ch);
			return;
		}

		if(!str_cmp(arg1, "accept"))
		{
			add_member(ch->pcdata->kingdom_invite, ch);
			return;
		}

		if(!str_cmp(arg1, "decline"))
		{
			send_to_char("You decline the kingdom's invitation.\n\r", ch);

			if((vch = get_char_world(ch, get_kingdom(ch->pcdata->kingdom_invite)->leader)) != 0)
			{
				sprintf(buf, "%s has declined your invitation.\n\r", ch->name);
				send_to_char(buf, vch);
			}
			ch->pcdata->kingdom_invite = 0;
			return;
		}

		send_to_char("Type either kingdom accept or kingdom decline.\n\r", ch);
		return;
	}

	kingdom = get_kingdom(ch->pcdata->kingdom);

	if(!str_cmp(arg1, "leave") && !str_cmp(arg2, "for") && !str_cmp(arg3, "good"))
	{
		send_to_char("You leave the kingdom!\n\r", ch);
		remove_member(kingdom->id, ch->name);
		remove_trustee(kingdom->id, ch->name);
		return;
	}

	if(!str_prefix(arg1, "report"))
	{
		long percent;
		char *color;

		buf[0] = '\0';
		sprintf(buf, "%-4s %-12s{X %5s :: %s\n\r",
			"CMBT", "Name", "Hits", "Room" );

		for(d = descriptor_list; d; d = d->next)
		{
			if(d->connected != CON_PLAYING || !(vch = d->character) || vch->pcdata->kingdom != kingdom->id)
				continue;

			percent = (long) ((float) UMAX(1, vch->hit) / (float) UMAX(1, vch->max_hit) * 100);

			if(percent < 10)
				color = "{R";
			else if(percent < 40)
				color = "{B";
			else if(percent < 70)
				color = "{Y";
			else
				color = "{C";

			sprintf(buf + strlen(buf), "%-4s %s%-12s{X %5li :: %s\n\r",
				vch->fighting ? !IS_NPC(vch->fighting) ? "{R(PK){X" : "{r(F){X" : "",
				 color, vch->name, vch->hit, !vch->in_room ? "somewhere" : vch->in_room->name);
		}
		send_to_char(buf, ch);
		return;
	}

	if(!is_trustee(ch, kingdom->id))
	{
		send_to_char("Only leaders and trustees have power to modify their kingdom.\n\r", ch);
		return;
	}

	if(arg1[0] == '\0' || arg2[0] == '\0')
	{
		if(is_leader(ch, kingdom->id) || IS_IMMORTAL(ch))
		{
			send_to_char("Syntax:\n\r", ch);
			send_to_char("        kingdom report\n\r", ch);
			send_to_char("        kingdom invite <player>\n\r", ch);
			send_to_char("        kingdom outcast <member>\n\r", ch);
			send_to_char("        kingdom war <kingdom ID>\n\r", ch);
			send_to_char("        kingdom treaty <kingdom ID>\n\r", ch);
			send_to_char("        kingdom rank <member> <rank>\n\r", ch);
			send_to_char("        kingdom trust <member>\n\r", ch);
			send_to_char("        kingdom recall\n\r", ch);
			send_to_char("\n\r", ch);
		}
		send_to_char("Syntax: kingdom scry <person>\n\r", ch);
		return;
	}

	if(is_leader(ch, kingdom->id))
	{
		if(!str_cmp(arg1, "recall"))
		{
			if(kingdom->points < KINGDOM_RECALL_COST)
			{
				sprintf(buf, "It costs %d kingdom points to set a recall point.\n\r", KINGDOM_RECALL_COST);
				send_to_char(buf, ch);
				return;
			}

			if(ch->in_room == 0)
			{
				send_to_char("You are in a 0 room, eek.\n\r", ch);
				return;
			}

			kingdom->points -= KINGDOM_RECALL_COST;
			kingdom->recall = ch->in_room->vnum;

			kingdom_message(kingdom->id, "{MThe Kingdom Recall has been set to -> [%s]", ch->in_room->name);
			return;
		}

		if(!str_cmp(arg1, "trust"))
		{
			if((vch = get_char_world(ch, arg2)) == 0 || IS_NPC(vch))
			{
				send_to_char("They need to be logged on.\n\r", ch);
				return;
			}

			if(vch->pcdata->kingdom != ch->pcdata->kingdom)
			{
				send_to_char("They aren't in your kingdom!\n\r", ch);
				return;
			}

			arg2[0] = UPPER(arg2[0]);
			if( strstr(kingdom->trustees, arg2) == 0 )
				add_trustee(kingdom->id, vch);
			else
				remove_trustee(kingdom->id, arg2);
			return;
		}

		if(!str_cmp(arg1, "invite"))
		{
			if((vch = get_char_world(ch, arg2)) == 0)
			{
				send_to_char("They aren't logged on.\n\r", ch);
				return;
			}

			if(IS_NPC(vch))
			{
				send_to_char("That's an NPC.\n\r", ch);
				return;
			}

			if(vch->pcdata->kingdom)
			{
				send_to_char("They are already a part of another kingdom!\n\r", ch);
				return;
			}

			vch->pcdata->kingdom_invite = ch->pcdata->kingdom;
			sprintf(buf, "You are invited to join the %s Kingdom by %s.\n\r"
				"Type kingdom accept or kingdom decline.\n\r", kingdom->name, ch->name);
			send_to_char(buf, vch);
			sprintf(buf, "You invite %s to join your glorious kingdom.\n\r", vch->name);
			send_to_char(buf, ch);
			return;
		}

		if(!str_cmp(arg1, "outcast"))
		{
			arg2[0] = UPPER(arg2[0]);
			if( strstr(kingdom->members, arg2) == 0 )
			{
				send_to_char("That person isn't a member!\n\r",ch);
				return;
			}

			if(remove_member(ch->pcdata->kingdom, arg2))
				kingdom_message(0, "%s has been outcasted from the %s Kingdom!", capitalize(arg2), kingdom->name);
			remove_trustee(kingdom->id, arg2);
			return;
		}

		if(!str_cmp(arg1, "treaty"))
		{

			if(kingdom->treaty_pending)
			{
				if(!get_kingdom(kingdom->treaty_pending))
				{
					kingdom->treaty_pending = 0;
					return;
				}

				if(has_treaty(kingdom->id, kingdom->treaty_pending))
				{
					send_to_char("You already have a treaty with them.\n\r", ch);
					return;
				}

				if(!str_cmp(arg2, "accept"))
				{
					add_treaty(kingdom->id, kingdom->treaty_pending);
					kingdom->treaty_pending = 0;
					return;
				}

				if(!str_cmp(arg2, "decline"))
				{
					kingdom_message(kingdom->id, "Your kingdom declines a treaty with the %s Kingdom.",
						get_kingdom(kingdom->treaty_pending)->name);

					kingdom_message(kingdom->treaty_pending, "%s Kingdom has declined your treaty offer.", kingdom->name);
					kingdom->treaty_pending = 0;
					return;
				}

				sprintf(buf, "You have a treaty offer pending with the %s Kingdom.\n\r"
					"Please type kingdom treaty accept or kingdom treaty decline.\n\r",
					get_kingdom(kingdom->treaty_pending)->name);
				send_to_char(buf, ch);
				return;
			}

			if(!is_number(arg2) || get_kingdom(atoi(arg2)) == &kingdom_default)
			{
				send_to_char("There is no such kingdom to make a treaty with.\n\r", ch);
				return;
			}
			i = atoi(arg2);

			if(kingdom->id == i)
			{
				send_to_char("You already have a treaty with yourself, smart one.\n\r", ch);
				return;
			}

			if(is_at_war(kingdom->id, i))
			{
				send_to_char("You are at {RWAR{N with that kingdom!\n\r", ch);
				return;
			}

			if(has_treaty(kingdom->id, i))
			{
				remove_treaty(kingdom->id, i);
				return;
			}

			if(get_kingdom(i)->treaty_pending)
			{
				send_to_char("They are already pending a treaty confirmation.\n\r", ch);
				return;
			}

			get_kingdom(i)->treaty_pending = kingdom->id;
			kingdom_message(i, "The %s Kingdom is asking for a treaty with your kingdom.", kingdom->name);
			kingdom_message(kingdom->id, "You ask the %s Kingdom for a treaty.", get_kingdom(i)->name);
			return;
		}

		if(!str_cmp(arg1, "war"))
		{

			if(!is_number(arg2) || get_kingdom(atoi(arg2)) == &kingdom_default)
			{
				send_to_char("There is no such kingdom to make war with.\n\r", ch);
				return;
			}

			i = atoi(arg2);

			if(i == kingdom->id)
			{
				send_to_char("That wouldn't be a very smart political move.\n\r", ch);
				return;
			}

			if(get_kingdom(i) == &kingdom_default)
			{
				send_to_char("That kingdom doesn't exist.\n\r", ch);
				return;
			}

			if(has_treaty(kingdom->id, i))
			{
				send_to_char("But you have a treaty with them!\n\r", ch);
				return;
			}

			if(is_at_war(kingdom->id, i))
			{
				remove_war(kingdom->id, i);
				return;
			}

			add_war(kingdom->id, i);
			return;
		}

		if(!str_cmp(arg1, "rank"))
		{
			if(!arg3 || arg3[0] == '\0')
			{
				send_to_char("Rank who as what?\n\r", ch);
				return;
			}

			if((vch = get_char_world(ch, arg2)) == 0 || IS_NPC(vch))
			{
				send_to_char("They aren't on at the moment.\n\r", ch);
				return;
			}

			if(vch->pcdata->kingdom != ch->pcdata->kingdom)
			{
				send_to_char("They aren't apart of your kingdom!\n\r", ch);
				return;
			}

			if(ansistrlen(arg3) > 15)
			{
				send_to_char("String length is limited to 20 characters.\n\r", ch);
				return;
			}

			free_string(vch->pcdata->krank);

			if(!str_cmp(arg3, "clear"))
			{
				vch->pcdata->krank = str_dup("");
				return;
			}

			arg3[0] = UPPER(arg3[0]);
			vch->pcdata->krank = str_dup(arg3);
			send_to_char("Done.\n\r", ch);
			return;
		}
	}

	if(!str_cmp(arg1, "scry"))
	{
		if(arg2[0] == '\0')
		{
			send_to_char("You must supply the name of the person.\n\r", ch);
			return;
		}

		if((vch = get_char_world(ch, arg2)) == 0 || IS_NPC(vch))
		{
			send_to_char("They are not online.\n\r", ch);
			return;
		}

		if(kingdom->points < KINGDOM_SCRY_COST)
		{
			sprintf(buf, "It costs %d Kingdom Points to do this.\n\r", KINGDOM_SCRY_COST);
			send_to_char(buf, ch);
			return;
		}

		kingdom_message(kingdom->id, "%s has {cscryed{N %s {C. o O{N ({C%s{N)",
			ch->name, vch->name, vch->in_room == 0 ? "Nowhere" : vch->in_room->name);
		kingdom->points -= KINGDOM_SCRY_COST;
		return;
	}

	// default message
	do_kingdom(ch, "blah");
}