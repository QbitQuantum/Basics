int
PConnection::initiate_write_stream (ACE_Message_Block &mb)
{
    size_t nbytes = mb.length();

    int rc = 0;

    if (nbytes == 0)
    {
        this->free_msg (&mb);
        this->cancel ();
        ACE_ERROR_RETURN((LM_ERROR,
                          ACE_TEXT ("(%t) %s PConnection: attempt write 0 bytes\n"),
                          this->get_name()),
                         -1);
    }

    if (this->get_ref_cnt_w() != 0)
    {
        ACE_Time_Value tv = ACE_Time_Value::zero;

        if (out_mq_.enqueue_tail (&mb, &tv) < 0)
        {
            this->free_msg (&mb);
            this->cancel ();
            ACE_ERROR_RETURN((LM_ERROR,
                              ACE_TEXT ("(%t) %s PConnection: attempt to queue failed\n"),
                              this->get_name()),
                             -1);
        }
        this->total_snd_ += nbytes;
        return 0;
    }


    if (do_initiate_write_stream (mb) != 0)
        return -1;

    this->total_snd_ += nbytes;
    return 0;
}