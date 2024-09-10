/**
 * write data to a xrdpvr client
 *
 * @param  channel  opaque handle returned by WTSVirtualChannelOpenEx
 * @param  s        structure containing data to write
 *
 * @return 0 on success, -1 on failure
 ******************************************************************************/
static int
xrdpvr_write_to_client(void *channel, STREAM *s)
{
    int bytes_to_send;
    int bytes_written;
    int index = 0;
    int rv;

    if ((channel == NULL) || (s == NULL))
    {
        return -1;
    }

    bytes_to_send = stream_length(s);

    while (1)
    {
        rv = WTSVirtualChannelWrite(channel, &s->data[index], bytes_to_send, &bytes_written);

        if (rv < 0)
        {
            return -1;
        }

        index += bytes_written;
        bytes_to_send -= bytes_written;

        if ((rv == 0) && (bytes_to_send == 0))
        {
            return 0;
        }

        usleep(1000 * 3);
    }
}