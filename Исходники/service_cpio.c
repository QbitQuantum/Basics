static unsigned int protocol_write(struct service_backend *backend, struct service_state *state, unsigned int id, unsigned int current, void *buffer, unsigned int count, unsigned int offset)
{

    struct cpio_header *header = mapheader(backend, state, id);

    if (!header)
        return 0;

    switch (header->mode & 0xF000)
    {

    case 0x8000:
        return writefile(backend, state, buffer, count, offset, id, header);

    }

    return 0;

}