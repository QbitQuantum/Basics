int RealmSocket::handle_output(ACE_HANDLE)
{
    if (closing_)
        return -1;

    ACE_Message_Block* mb = 0;

    if (msg_queue()->is_empty())
    {
        reactor()->cancel_wakeup(this, ACE_Event_Handler::WRITE_MASK);
        return 0;
    }

    if (msg_queue()->dequeue_head(mb, (ACE_Time_Value *)(&ACE_Time_Value::zero)) == -1)
        return -1;

    ssize_t n = noblk_send(*mb);

    if (n < 0)
    {
        mb->release();
        return -1;
    }
    else if (size_t(n) == mb->length())
    {
        mb->release();
        return 1;
    }
    else
    {
        mb->rd_ptr(n);

        if (msg_queue()->enqueue_head(mb, (ACE_Time_Value *) &ACE_Time_Value::zero) == -1)
        {
            mb->release();
            return -1;
        }

        return 0;
    }

    ACE_NOTREACHED(return -1);
}