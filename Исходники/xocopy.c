/*
 * Prints warning message for the bytes in the file that couldn't be recovered.
 * Uses 0/0 for offset/size to signal end of all lost data.
 */
static void
warn_lost_data (pid_t pid, Elf32_Ehdr *ehdr, Elf32_Phdr *phdr,
                unsigned int offset, unsigned int size)
{
    static unsigned int last_offset = 0;   /* for recording last offset */
    static unsigned int last_size = 0;     /* and size - initialised to zero */
    int p;

    if (offset != 0 && size != 0) {
        if ((last_offset + last_size) == offset) {
            /* join offsets */
            last_size += size;
            return;
        }
    }

    if (last_offset != 0 && last_size != 0) {
        fprintf(stderr, "could not recover data - %d bytes at file offset %d\n",
                last_size, last_offset);

        for (p = 0; p < ehdr->e_phnum; p++) {
            if (phdr[p].p_type != PT_NULL) {
                if (INTERSECTS(last_offset, last_size,
                               phdr[p].p_offset, phdr[p].p_filesz))
                {
                    fprintf(stderr, " ! data from phdr[%d] was not recovered\n", p);
                }
            }
        }

        if ((ehdr->e_shnum != 0) &&
                INTERSECTS(last_offset, last_size, ehdr->e_shoff,
                           ehdr->e_shnum * ehdr->e_shentsize))
        {
            fprintf(stderr, " ! section header table was not recovered\n");
        }
    }

    /* record this offset and size */
    last_offset = offset;
    last_size   = size;
}