int
Producer::svc (void)
{
    // Keep reading stdin, until we reach EOF.

    for (int n; ; )
    {
        // Allocate a new message (add one to avoid nasty boundary
        // conditions).

        ACE_Message_Block *mb = 0;

        ACE_NEW_RETURN (mb,
                        ACE_Message_Block (BUFSIZ + 1),
                        -1);

        n = ACE_OS::read (ACE_STDIN, mb->wr_ptr (), BUFSIZ);

        if (n <= 0)
        {
            // Send a shutdown message to the other thread and exit.
            mb->length (0);

            if (this->put_next (mb) == -1)
                ACE_ERROR ((LM_ERROR,
                            ACE_TEXT ("(%t) %p\n"),
                            ACE_TEXT ("put_next")));
            break;
        }

        // Send the message to the other thread.
        else
        {
            mb->wr_ptr (n);
            // NUL-terminate the string (since we use strlen() on it
            // later).
            mb->rd_ptr ()[n] = '\0';

            if (this->put_next (mb) == -1)
                ACE_ERROR ((LM_ERROR,
                            ACE_TEXT ("(%t) %p\n"),
                            ACE_TEXT ("put_next")));
        }
    }

    return 0;
}