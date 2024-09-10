/*!
 * @brief クエストに関わるモンスターの配置を行う / Place quest monsters
 * @return 成功したならばTRUEを返す
 */
bool place_quest_monsters(void)
{
    int i;

    /* Handle the quest monster placements */
    for (i = 0; i < max_quests; i++)
    {
        monster_race *r_ptr;
        u32b mode;
        int j;

        if (quest[i].status != QUEST_STATUS_TAKEN ||
                (quest[i].type != QUEST_TYPE_KILL_LEVEL &&
                 quest[i].type != QUEST_TYPE_RANDOM) ||
                quest[i].level != dun_level ||
                dungeon_type != quest[i].dungeon ||
                (quest[i].flags & QUEST_FLAG_PRESET))
        {
            /* Ignore it */
            continue;
        }

        r_ptr = &r_info[quest[i].r_idx];

        /* Hack -- "unique" monsters must be "unique" */
        if ((r_ptr->flags1 & RF1_UNIQUE) &&
                (r_ptr->cur_num >= r_ptr->max_num)) continue;

        mode = (PM_NO_KAGE | PM_NO_PET);

        if (!(r_ptr->flags1 & RF1_FRIENDS))
            mode |= PM_ALLOW_GROUP;

        for (j = 0; j < (quest[i].max_num - quest[i].cur_num); j++)
        {
            int k;

            for (k = 0; k < SAFE_MAX_ATTEMPTS; k++)
            {
                int x = 0, y = 0;
                int l;

                /* Find an empty grid */
                for (l = SAFE_MAX_ATTEMPTS; l > 0; l--)
                {
                    cave_type    *c_ptr;
                    feature_type *f_ptr;

                    y = randint0(cur_hgt);
                    x = randint0(cur_wid);

                    c_ptr = &cave[y][x];
                    f_ptr = &f_info[c_ptr->feat];

                    if (!have_flag(f_ptr->flags, FF_MOVE) && !have_flag(f_ptr->flags, FF_CAN_FLY)) continue;
                    if (!monster_can_enter(y, x, r_ptr, 0)) continue;
                    if (distance(y, x, p_ptr->y, p_ptr->x) < 10) continue;
                    if (c_ptr->info & CAVE_ICKY) continue;
                    else break;
                }

                /* Failed to place */
                if (!l) return FALSE;

                /* Try to place the monster */
                if (place_monster_aux(0, y, x, quest[i].r_idx, mode))
                {
                    /* Success */
                    break;
                }
                else
                {
                    /* Failure - Try again */
                    continue;
                }
            }

            /* Failed to place */
            if (k == SAFE_MAX_ATTEMPTS) return FALSE;
        }
    }

    return TRUE;
}