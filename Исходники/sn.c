static int load_snm_info(n2n_sn_t *sss)
{
    int new_ones = 0;
    struct sn_info *p = NULL;

    /* load supernodes */
    struct sn_info *cmd_line_list  = sss->supernodes.list_head;
    sss->supernodes.list_head = NULL;

    sprintf(sss->supernodes.filename, "SN_SNM_%d", sss->sn_port);
    if (read_sn_list_from_file( sss->supernodes.filename,
                               &sss->supernodes.list_head))
    {
        traceEvent(TRACE_ERROR, "Failed to open supernodes file. %s", strerror(errno));
        return -1;
    }

    /* check if we had some new supernodes before reading from file */

    p = cmd_line_list;
    while (p)
    {
        new_ones += update_supernodes(&sss->supernodes, &p->sn);
        p = p->next;
    }
    clear_sn_list(&cmd_line_list);

    if (new_ones)
    {
        write_sn_list_to_file(sss->supernodes.filename,
                              sss->supernodes.list_head);
    }

    /* load communities */
    sprintf(sss->communities.filename, "SN_COMM_%d", sss->sn_port);
    if (read_comm_list_from_file( sss->communities.filename,
                                 &sss->communities.persist))
    {
        traceEvent(TRACE_ERROR, "Failed to open communities file. %s", strerror(errno));
        return -1;
    }

    if (sn_list_size(sss->supernodes.list_head) == 0)    /* first running supernode */
    {
        sss->snm_discovery_state = N2N_SNM_STATE_READY;
    }

    return 0;
}