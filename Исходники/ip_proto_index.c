int
ip_proto_iterator(char **label)
{
    static char label_buf[20];
    struct protoent *p;
    if (NULL == label) {
        next_iter = 0;
        return largest + 1;
    }
    if (next_iter > largest)
        return -1;
    p = getprotobynumber(next_iter);
    if (p)
        *label = p->p_name;
    else
        snprintf(*label = label_buf, 20, "p%d", next_iter);
    return next_iter++;
}