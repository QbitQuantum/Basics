zuuid_t *
zuuid_new (void)
{
    zuuid_t *self = (zuuid_t *) zmalloc (sizeof (zuuid_t));
    if (self) {
#if defined (HAVE_LIBUUID)
#   if defined (__WINDOWS__)
        UUID uuid;
        assert (sizeof (uuid) == ZUUID_LEN);
        UuidCreate (&uuid);
        zuuid_set (self, (byte *) &uuid);
#   else
        uuid_t uuid;
        assert (sizeof (uuid) == ZUUID_LEN);
        uuid_generate (uuid);
        zuuid_set (self, (byte *) uuid);
#   endif
#else
        //  No UUID system calls, so generate a random string
        byte uuid [ZUUID_LEN];
        int fd = open ("/dev/urandom", O_RDONLY);
        if (fd != -1) {
            ssize_t bytes_read = read (fd, uuid, ZUUID_LEN);
            assert (bytes_read == ZUUID_LEN);
            close (fd);
        }
        zuuid_set (self, uuid);
#endif
    }
    return self;
}