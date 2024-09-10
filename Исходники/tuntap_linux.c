/* Fill out the ip_addr value from the interface. Called to pick up dynamic
 * address changes. */
void tuntap_get_address(struct tuntap_dev *tuntap)
{
    FILE * fp=NULL;
    ssize_t nread=0;
    char buf[N2N_LINUX_SYSTEMCMD_SIZE];

    /* Would rather have a more direct way to get the inet address but a netlink
     * socket is overkill and probably less portable than ifconfig and sed. */

    /* If the interface has no address (0.0.0.0) there will be no inet addr
     * line and the returned string will be empty. */
    snprintf( buf, sizeof(buf), "/sbin/ifconfig %s | /bin/sed -e '/inet addr:/!d' -e 's/^.*inet addr://' -e 's/ .*$//'",
              tuntap->dev_name );
    fp=popen(buf, "r");
    if (fp )
    {
        memset(buf,0,N2N_LINUX_SYSTEMCMD_SIZE); /* make sure buf is NULL terminated. */
        nread=fread(buf, 1, 15, fp);
        fclose(fp);
        fp=NULL;

        traceEvent(TRACE_INFO, "ifconfig address = %s", buf);

        tuntap->ip_addr = inet_addr(buf);
    }
}