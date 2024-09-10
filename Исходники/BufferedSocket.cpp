/*virtual*/ int BufferedSocket::handle_output(ACE_HANDLE /*= ACE_INVALID_HANDLE*/)
{
    ACE_Message_Block* mb = 0;

    if (this->msg_queue()->is_empty())
    {
        // if no more data to send, then cancel notification
        this->reactor()->cancel_wakeup(this, ACE_Event_Handler::WRITE_MASK);
        return 0;
    }

    if (this->msg_queue()->dequeue_head(mb, (ACE_Time_Value*) &ACE_Time_Value::zero) == -1)
        return -1;

    ssize_t n = this->noblk_send(*mb);

    if (n < 0)
    {
        mb->release();
        return -1;
    }
    else if (n == mb->length())
    {
        mb->release();
        return 1;
    }
    else
    {
        mb->rd_ptr(n);

        if (this->msg_queue()->enqueue_head(mb, (ACE_Time_Value*) &ACE_Time_Value::zero) == -1)
        {
            mb->release();
            return -1;
        }

        return 0;
    }

    ACE_NOTREACHED(return -1);
}