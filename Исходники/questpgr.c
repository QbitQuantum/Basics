static struct qtmsg *
construct_qtlist(long hdr_offset)
{
    struct qtmsg *msg_list;
    int n_msgs;

    dlb_fseek(msg_file, hdr_offset, SEEK_SET);
    Fread(&n_msgs, sizeof (int), 1, msg_file);
    msg_list = malloc((unsigned)(n_msgs + 1) * sizeof (struct qtmsg));

    /*
     * Load up the list.
     */
    Fread(msg_list, n_msgs * sizeof (struct qtmsg), 1, msg_file);

    msg_list[n_msgs].msgnum = -1;
    return msg_list;
}