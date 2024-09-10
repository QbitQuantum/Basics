int
read_llb(h2fmi_read_boot_page_t read_page, int offset, int size, unsigned char *buf)
{
    int rv = 0;
    int page = div(offset, LLB_PAGE_SIZE); /*offset / LLB_PAGE_SIZE*/
    int start = offset - page * LLB_PAGE_SIZE; /*offset % LLB_PAGE_SIZE*/
#if 0
    unsigned char *tmp = malloc_(4096);
    if (!tmp) {
        return -1;
    }

    for (page += 2; size > 0; page++) {
        int chunk = size;
        if (chunk > LLB_PAGE_SIZE - start) {
            chunk = LLB_PAGE_SIZE - start;
        }

        rv = read_page(0, page, tmp);
        if (rv) {
            break;
        }

        memcpy(buf, tmp + start, chunk);

        start = 0;
        buf += chunk;
        size -= chunk;
    }
#else  /* XXX more efficient, but should be used ONLY if read_page reads exactly LLB_PAGE_SIZE bytes */
    unsigned char *tmp = NULL;

    page += 2;
    if (start) {
        int chunk = LLB_PAGE_SIZE - start;
        if (!(tmp = malloc_(LLB_PAGE_SIZE))) return -1;
        rv = read_page(0, page, tmp);
        if (rv) {
            goto err;
        }
        memcpy(buf, tmp + start, chunk);
        buf += chunk;
        size -= chunk;
        page++;
    }

    for (; size >= LLB_PAGE_SIZE; page++) {
        rv = read_page(0, page, buf);
        if (rv) {
            goto err;
        }
        buf += LLB_PAGE_SIZE;
        size -= LLB_PAGE_SIZE;
    }

    if (size) {
        if (!tmp && !(tmp = malloc_(LLB_PAGE_SIZE))) return -1;
        rv = read_page(0, page, tmp);
        if (rv == 0) {
            memcpy(buf, tmp, size);
        }
    }

  err:
#endif

    free_(tmp);
    return rv;
}