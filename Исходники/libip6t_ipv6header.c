static char *
proto_to_name(u_int8_t proto, int nolookup)
{
        unsigned int i;

        if (proto && !nolookup) {
                struct protoent *pent = getprotobynumber(proto);
                if (pent)
                        return pent->p_name;
        }

        for (i = 0; i < ARRAY_SIZE(chain_protos); ++i)
                if (chain_protos[i].num == proto)
                        return chain_protos[i].name;

        return NULL;
}