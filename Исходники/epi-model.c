void
epi_init_agent(void)
{
    FILE		*g;
    FILE		*f;
    fpos_t		 pos;

    tw_memory	*b;
    tw_memory	*next;

    epi_agent	*a;

    int		*home_to_ct;
    int		 nagents = 0;
    int		 nlp = -1;
    int		 i;
    int		 j;
    int		 h;
    int		 o;
    int		 t;

    printf("\nEPI Agent Initialization: \n\n");

    home_to_ct = tw_calloc(TW_LOC, "home to ct", sizeof(*home_to_ct), 3363607);
    // create census tract table, hard-coded to 2214 (all CT) for Chicago
    g_epi_nregions = 2215;
    g_epi_regions = tw_calloc(TW_LOC, "", sizeof(unsigned int *), g_epi_nregions);

    // need to read in homes.dat to get CT ids
    if(NULL == (g = fopen("homes.dat", "r")))
        tw_error(TW_LOC, "Unable to open: homes.dat");

    i = 0;
    while(EOF != (fscanf(g, "%d", &home_to_ct[i++])))
        ;

    for(i = 0; i < g_epi_nregions; i++)
    {
        g_epi_regions[i] = tw_calloc(TW_LOC, "", sizeof(unsigned int *), g_epi_ndiseases);

        for(j = 0; j < g_epi_ndiseases; j++)
            g_epi_regions[i][j] = tw_calloc(TW_LOC, "", sizeof(unsigned int),
                                            g_epi_diseases[j].nstages);
    }

    if(NULL == (f = fopen("agents.dat", "r")))
        tw_error(TW_LOC, "Unable to open: agents.dat");

    i = 0;

    if(!g_epi_nagents)
    {
        fgetpos(f, &pos);
        while(EOF != fscanf(f, "%d %d %*d", &h, &o))
            g_epi_nagents++;
        fsetpos(f, &pos);
    }

    if(0 == g_epi_nagents)
        tw_error(TW_LOC, "No agents in agents.dat!");

    g_epi_agents = tw_calloc(TW_LOC, "", sizeof(tw_memoryq), 1);
    g_epi_agents->start_size = g_epi_nagents;
    g_epi_agents->d_size = sizeof(epi_agent);
    g_epi_agents->grow = 1;

    tw_memory_allocate(g_epi_agents);

    b = g_epi_agents->head;
    while(EOF != (fscanf(f, "%d %d %d", &h, &o, &t)))
    {
        // allocate the agent
        a = tw_memory_data(b);
        a->id = nagents++;

        if(h && h > nlp)
            nlp = h;

        if(o != -1 && o > nlp)
            nlp = o;

        // the CT id is stored on the h-th line of the homes.dat file
        a->region = home_to_ct[h];

        if(a->region > 2214)
            tw_error(TW_LOC, "Bad Home to CT Mapping!");

        a->pathogens = NULL;

#if 0
        // default disease stats
        a->stage = EPI_SUSCEPTIBLE;
        a->ts_stage_tran = DBL_MAX;
#endif

        a->curr = 0;
        //a->ts_last_tran = 0.0;

        // go to work at 9am on first day
        a->ts_next = a->ts_remove = (double) 32400.0;
        //a->n_infected = 0;

        if(-1 != o)
            a->nloc = 3;
        else
            a->nloc = 2;

        // only two locs =(
        a->loc[1] = o;
        a->loc[0] = a->loc[a->nloc-1] = h;

        a->dur[0] = 9 * 3600;
        a->dur[1] = 8 * 3600;
        a->dur[a->nloc-1] += 7 * 3600;

        a->behavior_flags = 0;
        a->ts_remove = a->ts_next = a->dur[a->curr];

        for(i = 0; i < g_epi_ndiseases; i++)
            g_epi_regions[a->region][i][0]++;

        if(g_epi_nagents == nagents)
            break;

        b = b->next;
    }

    if(nlp == 0)
        tw_error(TW_LOC, "No locations!");
    else
        printf("\t%-48s %11d\n", "Max Location", ++nlp);

    g_epi_pq = tw_calloc(TW_LOC, "", sizeof(void *), nlp);

    for(i = 0; i < nlp; i++)
        g_epi_pq[i] = pq_create();

    for(b = g_epi_agents->head; b; b = next)
    {
        a = tw_memory_data(b);
        next = b->next;
        pq_enqueue(g_epi_pq[a->loc[0]], b);
    }

    g_tw_nlp = nlp;

}