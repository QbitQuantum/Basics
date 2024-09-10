void
print_rdr(struct pf_rdr *r)
{
    if (r->no)
        printf("no ");
    printf("rdr ");
    if (r->ifname[0]) {
        printf("on ");
        if (r->ifnot)
            printf("! ");
        printf("%s ", r->ifname);
    }
    if (r->proto) {
        struct protoent *p = getprotobynumber(r->proto);
        if (p != NULL)
            printf("proto %s ", p->p_name);
        else
            printf("proto %u ", r->proto);
    }
    printf("from ");
    if (!PF_AZERO(&r->saddr, r->af) || !PF_AZERO(&r->smask, r->af)) {
        if (r->snot)
            printf("! ");
        print_addr(&r->saddr, &r->smask, r->af);
        printf(" ");
    } else
        printf("any ");
    printf("to ");
    if (!PF_AZERO(&r->daddr, r->af) || !PF_AZERO(&r->dmask, r->af)) {
        if (r->dnot)
            printf("! ");
        print_addr(&r->daddr, &r->dmask, r->af);
        printf(" ");
    } else
        printf("any ");
    if (r->dport) {
        printf("port %u", ntohs(r->dport));
        if (r->opts & PF_DPORT_RANGE)
            printf(":%u", ntohs(r->dport2));
    }
    if (!r->no) {
        printf(" -> ");
        print_addr(&r->raddr, NULL, r->af);
        printf(" ");
        if (r->rport) {
            printf("port %u", ntohs(r->rport));
            if (r->opts & PF_RPORT_RANGE)
                printf(":*");
        }
    }
    printf("\n");
}