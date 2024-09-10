const Sample_entry* Note_map_get_entry(
        const Note_map* map,
        double cents,
        double force,
        Random* random)
{
    assert(map != NULL);
    assert(isfinite(cents));
    assert(isfinite(force) || (isinf(force) && force < 0));
    assert(random != NULL);

    Random_list* key =
        &(Random_list){ .force = force, .freq = NAN, .cents = cents };
    Random_list* estimate_low = AAiter_get_at_most(map->iter, key);
    Random_list* choice = NULL;
    double choice_d = INFINITY;

    if (estimate_low != NULL)
    {
        choice = estimate_low;
        choice_d = distance(choice, key);
        double min_tone = key->cents - choice_d;
        Random_list* candidate = AAiter_get_prev(map->iter);
        while (candidate != NULL && candidate->cents >= min_tone)
        {
            double d = distance(candidate, key);
            if (d < choice_d)
            {
                choice = candidate;
                choice_d = d;
                min_tone = key->cents - choice_d;
            }
            candidate = AAiter_get_prev(map->iter);
        }
    }

    Random_list* estimate_high = AAiter_get_at_least(map->iter, key);
    if (estimate_high != NULL)
    {
        double d = distance(estimate_high, key);
        if (choice == NULL || choice_d > d)
        {
            choice = estimate_high;
            choice_d = d;
        }

        double max_tone = key->cents + choice_d;
        Random_list* candidate = AAiter_get_next(map->iter);
        while (candidate != NULL && candidate->cents <= max_tone)
        {
            d = distance(candidate, key);
            if (d < choice_d)
            {
                choice = candidate;
                choice_d = d;
                max_tone = key->cents + choice_d;
            }
            candidate = AAiter_get_next(map->iter);
        }
    }

    if (choice == NULL)
    {
//        fprintf(stderr, "empty map\n");
        return NULL;
    }

    assert(choice->entry_count > 0);
    assert(choice->entry_count < NOTE_MAP_RANDOMS_MAX);
//    state->middle_tone = choice->freq;
    int index = Random_get_index(random, choice->entry_count);
    assert(index >= 0);
//    fprintf(stderr, "%d\n", index);

    return &choice->entries[index];
}