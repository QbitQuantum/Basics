static void
display_states(const struct pfioc_states *ps, int verbose __unused, FILE* f)
{
    struct pfsync_state *p = NULL;
    struct pfsync_state_peer *src, *dst;
    struct protoent *proto;
    int nb_states;
    int i;
    uint64_t id;

    p = ps->ps_states;
    nb_states = ps->ps_len / sizeof(struct pfsync_state);

    for (i = 0; i < nb_states; i++, p++) {
        fprintf(f, "state %s ", p->direction == PF_OUT ? "out" : "in");
        fprintf(f, "on %s ", p->ifname);

        if ((proto = getprotobynumber(p->proto)) != NULL)
            fprintf(f, "proto %s ", proto->p_name);
        else
            fprintf(f, "proto %u ", p->proto);


        if (PF_ANEQ(&p->lan.addr, &p->gwy.addr, p->af) ||
                (p->lan.port != p->gwy.port)) {

            char buf1[64], buf2[64], buf3[64];
            fprintf(f, "from %s to %s using %s",
                    print_host(&p->lan, p->af, buf1, sizeof(buf1)),
                    print_host(&p->ext, p->af, buf2, sizeof(buf2)),
                    print_host(&p->gwy, p->af, buf3, sizeof(buf3)));
        } else {
            char buf1[64], buf2[64];
            fprintf(f, "from %s to %s",
                    print_host(&p->lan, p->af, buf1, sizeof(buf1)),
                    print_host(&p->ext, p->af, buf2, sizeof(buf2)));
        }

        memcpy(&id, p->id, sizeof(p->id));
        fprintf(f, " id %" PRIu64 " cid %" PRIu32 " expire %" PRIu32 " timeout %" PRIu8,
                id , p->creatorid, p->expire, p->timeout);

        if (p->direction == PF_OUT) {
            src = &p->src;
            dst = &p->dst;
        } else {
            src = &p->dst;
            dst = &p->src;
        }

        fprintf(f, " src ");
        print_peer(src, p->proto, f);
        fprintf(f, " dst ");
        print_peer(dst, p->proto, f);

        fprintf(f, "\n");
    }
}