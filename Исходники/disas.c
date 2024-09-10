char *get_fn_by_range(handle_t *h, uint64_t vaddr)
{
    char *buf = heapAlloc(512);

    for (int i = 0; i < h->lsc; i++) {
        if (vaddr >= h->lsyms[i].value && vaddr < h->lsyms[i].value + h->lsyms[i].size) {
            strncpy(buf, h->lsyms[i].name, sizeof(buf) - 3);
            strcat(buf, "()");
            return buf;
        }
    }
    return NULL;
}